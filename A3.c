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
#define OUT_PRIORITY	 tskIDLE_PRIORITY 

SemaphoreHandle_t semA;
SemaphoreHandle_t semB;
SemaphoreHandle_t semC;
SemaphoreHandle_t semD;
SemaphoreHandle_t semE;
SemaphoreHandle_t semF;

TaskHandle_t taskHandleA = NULL;
TaskHandle_t taskHandleB = NULL;
TaskHandle_t taskHandleC = NULL;
TaskHandle_t taskHandleD = NULL;
TaskHandle_t taskHandleE = NULL;
TaskHandle_t taskHandleF = NULL;


// code for task
void createTask(void *pvParam){
    int iTaskTicks = 0;
    uint8_t mesg[80];
    TickType_t pxPreviousWakeTime;
    TaskHandle_t xTaskGetCurrentHandle();
    int i, j, IMAXCOUNT, JMAXCOUNT;
    
    for(;;) {
        //TMAN_TaskWaitPeriod(); // add args if needed
        int l = periodicityTask() / 2; // GET TICKS
        char nameTask; // print "Task name " and " ticks"
        printf("onde estou? ");
        printf("%d\n", &l);
        printf("%s , %d", nameTask, l);
        
        for(i = 0; i < IMAXCOUNT; i++){
            for(j = 0; j < JMAXCOUNT; j++){
                //do some computation to consume time
            }
        }
        // other stuff (if needed))
        
        
        
        //printf(omega);
        vTaskDelayUntil(&pxPreviousWakeTime,ACQ_PERIOD_MS)
    }
    
    // PSEUDOCODE DO DELIVERABLE NAS TASKS CRIADAS????
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
    semA = xSemaphoreCreateBinary();
    semB = xSemaphoreCreateBinary();
    semC = xSemaphoreCreateBinary();
    semD = xSemaphoreCreateBinary();
    semE = xSemaphoreCreateBinary();
    semF = xSemaphoreCreateBinary();
    
    /* Create the tasks defined within this file. */
    
    xTaskCreate( createTask, ( const signed char * const ) "A", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, &taskHandleA );
    xTaskCreate( createTask, ( const signed char * const ) "B", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, &taskHandleB );
    //xTaskCreate( createTask, ( const signed char * const ) "C", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, &taskHandleC );
    //xTaskCreate( createTask, ( const signed char * const ) "D", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, &taskHandleD );
    //xTaskCreate( createTask, ( const signed char * const ) "E", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, &taskHandleE );
    //xTaskCreate( createTask, ( const signed char * const ) "F", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, &taskHandleF );
     
    //TMAN_TaskRegisterAtributes();
    
    //TMAN_TaskWaitPeriod();
        /* Finally start the scheduler. */
	vTaskStartScheduler();

    //int tickTasks = xTaskGetTickCount();
    //printf("%d ticks", tickTasks);
    
    return (0);
    
    
}
