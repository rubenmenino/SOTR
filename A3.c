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



// code for task
void createTask(void *pvParam){
    int iTaskTicks = 0;
    uint8_t mesg[80];
    TickType_t pxPreviousWakeTime;
    
    for(;;) {
        vTaskDelayUntil(&pxPreviousWakeTime,ACQ_PERIOD_MS)
    }
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
    
    
    // Welcome message
    printf("Welcome Message1\n\r");

    // Create semaphore before starting tasks

    /* Create the tasks defined within this file. */
    
    xTaskCreate( createTask, ( const signed char * const ) "A", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, NULL );
    xTaskCreate( createTask, ( const signed char * const ) "B", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, NULL );
    xTaskCreate( createTask, ( const signed char * const ) "C", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, NULL );
    xTaskCreate( createTask, ( const signed char * const ) "D", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, NULL );
    xTaskCreate( createTask, ( const signed char * const ) "E", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, NULL );
    xTaskCreate( createTask, ( const signed char * const ) "F", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, NULL );
     
    //TMAN_TaskRegisterAtributes();
    
    //TMAN_TaskWaitPeriod();
        /* Finally start the scheduler. */
	vTaskStartScheduler();

    //int tickTasks = xTaskGetTickCount();
    //printf("%d ticks", tickTasks);
    
    return (0);
    
    
}
