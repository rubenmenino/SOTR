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

#define PRIO_TASK_PRIORITY (tskIDLE_PRIORITY + 3)

typedef struct {
    char* name;
    int id;
    int period;
    int nextActivation;
    int phase;
    int deadline;
    TaskHandle_t handler;
    SemaphoreHandle_t sem;
} taskInfo;



taskInfo task_list[6];
taskInfo teste;
TickType_t tick_TMAN;

int tick_now = 0;
int task_counter = 0;


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
        
        
        printf("TICK %d\n", pxPreviousWakeTime);
        printf("TMAN %d\n", tick_now);
        
        
        for(int i = 0; i < task_counter; i++) {
            printf("resume %d\n", i);
            
            xSemaphoreGive(task_list[i].sem);
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
    printf("sleep %d\n", task_id);
    //vTaskSuspend(task_list[task_id].handler);

}

// Initialization of the framework
void TMAN_Init(int tick){
    tick_TMAN = (TickType_t) tick;

    //printf("entrou init\n");
    xTaskCreate( tick_updater,  (const signed char * const) "highPriorityTask", configMINIMAL_STACK_SIZE, NULL, PRIO_TASK_PRIORITY, NULL );
    //printf("criou tick handler\n");
}

// Terminate the framework
void TMAN_Close(){
    //vPortFree();  
}

// Add a task to the framework
void TMAN_TaskAdd(TaskHandle_t handler){
    
    task_list[task_counter].sem =  xSemaphoreCreateBinary();
    task_list[task_counter].id = task_counter;
    task_list[task_counter].handler = handler;
    
    printf("task add %d\n", task_counter);
    
    task_counter++;
}

// Register attributes (ex: period, phase, deadline, precedence contraints) for a task already added to the framework
void TMAN_TaskRegisterAtributes(int task_id, int period, int deadline, int phase, int precedence){
    
    task_list[task_id].period = period;
    task_list[task_id].nextActivation = period + phase;
    task_list[task_id].deadline = deadline;
    task_list[task_id].phase = phase;
    
    printf("task register %d\n", task_id);
}


// Returns statisticals information about a task. Provided information must include at least the number of activations, but additional
// (ex: number of deadline misses) will be valued.
void TMAN_TaskStats(){
    
}