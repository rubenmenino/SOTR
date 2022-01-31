/* 
 * 
 * Authors: Paulo Pedreiras
 * Ruben Menino 89185   
 * Joao Genio 88771
 *

 * 
 */
#define _SVID_SOURCE
/* Standard includes. */
#include <stdio.h>
#include <string.h>

#include <xc.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "TaskManager.h"

#include <sys/attribs.h>
#include <stdlib.h>
#include "../UART/uart.h" 
#include "semphr.h"
#include <string.h>

#define PRIO_TASK_PRIORITY (tskIDLE_PRIORITY + 4)

typedef struct {        // struct das tasks
    char* name;
    int id;
    int period;
    int phase;
    int deadline;
    int precedence;
    int nActivations;
    int nCompletions;
    SemaphoreHandle_t sem;
} taskInfo;



taskInfo task_list[6];
taskInfo teste;
TickType_t tick_TMAN;
TaskHandle_t updateHandle = NULL;

int tick_now = 0;
int task_counter = 0;
int x;

void tick_updater(void *pvParam)
{
    //printf("entrou\n");
    int iTaskTicks = 0;
    
    //printf("antes for\n");
    TickType_t pxPreviousWakeTime = xTaskGetTickCount();
    //TickType_t pxPreviousWakeTime = xTaskGetTickCount();
    for(;;) {
        //printf("TICK %d\n", pxPreviousWakeTime);
        // Initialize the pxPreviousWakeTime variable with the current time
        
        //printf("TICK %d\n", pxPreviousWakeTime);
        //printf("\nTMAN %d\n", tick_now);
        
        
        for(int i = 0; i < task_counter; i++) {
            
            //printf("resume %d\n", i);
            
            //xSemaphoreGive(task_list[i].sem);
            //printf("\ntick_now %d --> phase %d\n", tick_now, task_list[i].phase);
            //printf("\ntick_now %d\n", tick_now);
            int x = 0;
            
            if(task_list[i].precedence != -1 && task_list[i].precedence < task_counter){  // 
                //printf("ola\n");
                int precedent = task_list[i].precedence;
                //printf("%d, %d\n", task_list[i].nCompletions, task_list[precedent].nCompletions);
                if(task_list[i].nCompletions < task_list[precedent].nCompletions){
                    x = 1; // esta task tem um anterior que já terminou mais vezes que ela. Pode executar.  (a anterior tem completar mais vezes que eu para executar))
                }
            }
            if(task_list[i].precedence == -1 || x == 1){
                if(tick_now == task_list[i].phase){
                    //printf("first %d\n", i);

                    xSemaphoreGive(task_list[i].sem);
                    task_list[i].nActivations++;
                    //printf("%d nActivations\n", task_list[i].nActivations);
                } 
                else if((tick_now - task_list[i].phase) % task_list[i].period == 0){
                    //printf("resume %d\n", i);
                    xSemaphoreGive(task_list[i].sem);
                    task_list[i].nActivations++;
                    //printf("%d nActivations\n", task_list[i].nActivations);
                }
           }

            //printf("dá give\n");
            //vTaskResume(task_list[i].handler);
            
        }
        
        //printf("tman value %d\n", tick_TMAN);
        // Wait for the next cycle
        
        tick_now++;
        vTaskDelayUntil(&pxPreviousWakeTime,tick_TMAN);
    }
    
    
}

// Called by a task to signal the termination of an instance and wait for the next activation
void TMAN_TaskWaitPeriod(int task_id){
    //printf("ENTRA NA TASK WAIT??\n");
    xSemaphoreTake(task_list[task_id].sem, portMAX_DELAY);
    //printf("sleep %d\n", task_id);
    
    task_list[task_id].nCompletions++;
    
    if(task_list[task_id].nActivations == 3 ){
        TMAN_TaskStats(task_id);
    }
    //vTaskSuspend(task_list[task_id].handler);

}

// Initialization of the framework
void TMAN_Init(int tick){
    tick_TMAN = (TickType_t) tick;

    //printf("entrou init\n");
    xTaskCreate( tick_updater,  (const signed char * const) "highPriorityTask", configMINIMAL_STACK_SIZE, NULL, PRIO_TASK_PRIORITY, &updateHandle );
    //printf("criou tick handler\n");
}

// Terminate the framework
void TMAN_Close(){
    //vPortFree();  
    if(updateHandle != NULL){
        vTaskDelete(updateHandle);
    }
}

// Add a task to the framework
void TMAN_TaskAdd(){
    task_list[task_counter].nActivations = 0;
    task_list[task_counter].nCompletions = -1;
    task_list[task_counter].sem =  xSemaphoreCreateBinary();
    task_list[task_counter].id = task_counter;
    //task_list[task_counter].handler = handler;
    
    //printf("task add %d\n", task_counter);
    
    task_counter++;
}

// Register attributes (ex: period, phase, deadline, precedence contraints) for a task already added to the framework
void TMAN_TaskRegisterAtributes(int task_id, int period, int deadline, int phase, int precedence){
    
    task_list[task_id].period = period;
    task_list[task_id].deadline = deadline;
    task_list[task_id].phase = phase;
    task_list[task_id].precedence = precedence;
    
    //printf("task register %d\n", task_id);
}


// Returns statisticals information about a task. Provided information must include at least the number of activations, but additional
// (ex: number of deadline misses) will be valued.
void TMAN_TaskStats(int task_id){
    //printf("Task %d number of Activations %d \n", task_id, task_list[task_id].nActivations);
    //printf("Task %d number of Completions %d \n", task_id, task_list[task_id].nCompletions);

}