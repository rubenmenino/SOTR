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

#include <sys/attribs.h>
#include <stdlib.h>
#include "../UART/uart.h" 
#include "semphr.h"
#include <string.h>

#define PBCLOCK 40000000UL // Peripheral Bus Clock frequency, in Hz

/* Set the tasks' period (in system ticks) */
#define ACQ_PERIOD_MS 	( 100 / portTICK_RATE_MS ) //
#define PROC_PERIOD_MS 	( 100 / portTICK_RATE_MS ) //
#define OUT_PERIOD_MS 	( 100 / portTICK_RATE_MS ) //

/* Priorities of the demo application tasks (high numb. -> high prio.) */
#define ACQ_PRIORITY	 tskIDLE_PRIORITY 
#define PROC_PRIORITY	 tskIDLE_PRIORITY 
#define OUT_PRIORITY	 tskIDLE_PRIORITY 

#define NUMBER_OF_STRING 5
#define MAX_STRING_SIZE 40

#define MAX 20
/*
 * 
 */

//Globals
float res; // sampled voltage


SemaphoreHandle_t sem1; // https://www.freertos.org/xSemaphoreCreateBinary.html
SemaphoreHandle_t sem2;
float outValue;


void TMAN_Init(){
    
}

void TMAN_Close(){
    //vPortFree();  
}


void TMAN_TaskAdd(){
    BaseType_t taskA;
    TaskHandle_t a_task = NULL;
    taskA = xTaskCreate( TMAN_TaskAdd, ( const signed char * const ) "A", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, &a_task );
    
}

void TMAN_TaskWaitPeriod(){
    
    int iTaskTicks = 0;
    uint8_t mesg[80];
    TickType_t pxPreviousWakeTime;
    
    for(;;) {
        vTaskDelayUntil(&pxPreviousWakeTime,ACQ_PERIOD_MS)
    }
    
}

void TMAN_TaskStats(){
    
}


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
        vTaskDelayUntil(&pxPreviousWakeTime,ACQ_PERIOD_MS);     
        
      
    }
}


int mainSetrLedBlinkA3(int argc, char** argv) {
    
    
    
    // Init UART and redirect tdin/stdot/stderr to UART
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
        while(1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
    
    adcModule();
    // Welcome message
    printf("Welcome Message1\n\r");

    // Create semaphore before starting tasks
    sem1 = xSemaphoreCreateBinary();
    sem2 = xSemaphoreCreateBinary();

    /* Create the tasks defined within this file. */
    
    
    
  
    
        /* Finally start the scheduler. */
	vTaskStartScheduler();

    return (0);
    
    
}
