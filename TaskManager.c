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
    double period;
    double phase;
    double deadline;
} taskInfo;
 

taskInfo *task_info;
TickType_t tick1;


void acqA3(void *pvParam)
{
    int iTaskTicks = 0;
    uint8_t mesg[80];
    TickType_t pxPreviousWakeTime;
    
    // Initialize the pxPreviousWakeTime variable with the current time
    pxPreviousWakeTime = xTaskGetTickCount();
    
    for(;;) {
        
        sprintf(mesg,"Task LedFlash (job %d)\n\r",iTaskTicks++);
        PrintStr(mesg);
        
         // Wait for the next cycle
        vTaskDelayUntil(&pxPreviousWakeTime,tick1); 

    }
}


// Initialization of the framework
void TMAN_Init(int tick){
    tick1 = (TickType_t) tick;
    task_info = (taskInfo*) pvPortMalloc (sizeof(taskInfo));
    task_info -> number = 1;
    xTaskCreate( acqA3,  "highPriorityTask", configMINIMAL_STACK_SIZE, NULL, PRIO_TASK_PRIORITY, NULL );
    
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
      // xTaskAbortDelay() instead delayUnitl ???)
}

// Returns statisticals information about a task. Provided information must include at least the number of activations, but additional
// (ex: number of deadline misses) will be valued.
void TMAN_TaskStats(){
    
}