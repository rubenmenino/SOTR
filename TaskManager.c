/* 
 * 
 * Author: Paulo Pedreiras
 * Ruben Menino 89185   
 * Joao Génio 88771
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

#define PRIO_TASK_PRIORITY (tskIDLE_PRIORITY +1 )

typedef struct {
    char* name;
    int number;
    int period;
    int phase;
    int deadline;
    SemaphoreHandle_t x;
} taskInfo;
 
taskInfo tI[1];
taskInfo *task_info;
TickType_t tick_TMAN;
int tick_now;

void acqA3(void *pvParam)
{
    printf("entrou\n");
    int iTaskTicks = 0;
    uint8_t mesg[80];
    TickType_t pxPreviousWakeTime;
    tI[1].x = xSemaphoreCreateBinary();
    // Initialize the pxPreviousWakeTime variable with the current time
    pxPreviousWakeTime = xTaskGetTickCount();
    printf("antes for\n");
    for(;;) {
        
        sprintf(mesg,"[], %d\n\r",tick_now);
        PrintStr(mesg);
        
         // Wait for the next cycle
        vTaskDelayUntil(&pxPreviousWakeTime,tick_TMAN); 
        
        
        xSemaphoreGive(tI[1].x);
        //xSemaphoreGive(tI[2].x);
        //printf("deu GIVE\n");
        tick_now++;
    }
}


// Initialization of the framework
void TMAN_Init(int tick){
    tick_TMAN = (TickType_t) tick;
    task_info = (taskInfo*) pvPortMalloc (sizeof(taskInfo));
    task_info -> number = 0;
    tick_now = 0;
    
    printf("entrou init\n");
    xTaskCreate( acqA3,  (const signed char * const) "highPriorityTask", configMINIMAL_STACK_SIZE, NULL, PRIO_TASK_PRIORITY, NULL );
    printf("criou tick hanfdler\n");
    //TMAN_TaskAdd();
}

// Terminate the framework
void TMAN_Close(){
    //vPortFree();  
}

// Add a task to the framework
void TMAN_TaskAdd(){
    task_info = (taskInfo*) pvPortMalloc (sizeof(taskInfo));
    task_info -> number++;
    printf("number %d", task_info->number);
    //xReturned = xTaskCreate( createTask, ( const signed char * const ) task_info->name, configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, task_info->xHandle );
}

// Register attributes (ex: period, phase, deadline, precedence contraints) for a task already added to the framework
void TMAN_TaskRegisterAtributes(){
    for(;;){
        //int periodValue = periodicityTask();
        //printf("periodicity value = %d ",periodValue);
    }
}

// Called by a task to signal the termination of an instance and wait for the next activation
void TMAN_TaskWaitPeriod(){
    xSemaphoreTake(tI[1].x, portMAX_DELAY);
    //xSemaphoreTake(tI[2].x, portMAX_DELAY);
      // xTaskAbortDelay() instead delayUnitl ???)
}

// Returns statisticals information about a task. Provided information must include at least the number of activations, but additional
// (ex: number of deadline misses) will be valued.
void TMAN_TaskStats(){
    
}