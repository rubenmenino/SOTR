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




typedef struct {
    char* name;
    double number;
    double period;
    double phase;
    double deadline;
    //TaskHandle_t xHandle;
} taskInfo;
 

taskInfo* task_info;

int periodicityTask(){
    int freeRTOS_ticks = xTaskGetTickCount(); // default to 1 ms in pIC32
    int tman_ticks = freeRTOS_ticks * 2;
    return tman_ticks;
}

// Initialization of the framework
void TMAN_Init(){
    task_info = (taskInfo*) pvPortMalloc (sizeof(taskInfo));
}

// Terminate the framework
void TMAN_Close(){
    //vPortFree();  
}

// Add a task to the framework
void TMAN_TaskAdd(char* name){
    BaseType_t xReturned;
    //xReturned = xTaskCreate( createTask, ( const signed char * const ) task_info->name, configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, task_info->xHandle );
}

// Register attributes (ex: period, phase, deadline, precedence contraints) for a task already added to the framework
void TMAN_TaskRegisterAtributes(){
    for(;;){
        int periodValue = periodicityTask();
        printf("periodicity value = %d ",periodValue);
    }
}

// Called by a task to signal the termination of an instance and wait for the next activation
void TMAN_TaskWaitPeriod(){
      
}

// Returns statisticals information about a task. Provided information must include at least the number of activations, but additional
// (ex: number of deadline misses) will be valued.
void TMAN_TaskStats(){
    
}