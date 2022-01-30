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
#define ACQ_PERIOD_MS 	( 3000 / portTICK_RATE_MS ) //
#define B_PERIOD_MS 	( 2000 / portTICK_RATE_MS ) //


/* Priorities of the demo application tasks (high numb. -> high prio.) */

#define PRIO_TASK_PRIORITY (tskIDLE_PRIORITY +1 )
#define PRIO_A	 tskIDLE_PRIORITY
#define PRIO_B	 tskIDLE_PRIORITY
#define PRIO_C	 tskIDLE_PRIORITY
#define PRIO_D	 tskIDLE_PRIORITY
#define PRIO_E	 tskIDLE_PRIORITY
#define PRIO_F	 tskIDLE_PRIORITY

//SemaphoreHandle_t semA;
//SemaphoreHandle_t semB;
//SemaphoreHandle_t semC;
//SemaphoreHandle_t semD;
//SemaphoreHandle_t semE;
//SemaphoreHandle_t semF;

char task_name[16];
TaskHandle_t taskPriorityHandle = NULL;
TaskHandle_t taskHandleA = NULL;
TaskHandle_t taskHandleB = NULL;
TaskHandle_t taskHandleC = NULL;
TaskHandle_t taskHandleD = NULL;
TaskHandle_t taskHandleE = NULL;
TaskHandle_t taskHandleF = NULL;

TickType_t t_tick;

// code for task
void taskHighPriority(void *pvParam){
    int iTaskTicks = 0;
    uint8_t mesg[80];
    TickType_t pxPreviousWakeTime;
    TaskHandle_t xTaskGetCurrentHandle();
    //xTimerHandle timerHnd05;
    
    int i, j, IMAXCOUNT, JMAXCOUNT;
    
    for(;;) {
        xTaskNotifyGive(taskHandleB);
        xTaskNotifyGive(taskHandleC);
        xTaskNotifyGive(taskHandleD);
        xTaskNotifyGive(taskHandleE);
        xTaskNotifyGive(taskHandleF);
        
        vTaskDelay(5000);   // VAIR SER A TMAN_WAITPERIOD
        
        
        //TMAN_TaskWaitPeriod(); // add args if needed
        //int l = periodicityTask() / 2; // GET TICKS
        //char nameTask; // print "Task name " and " ticks"
        printf("onde estou? ");
        //printf("%d\n", &l);
        
        
        for(i = 0; i < IMAXCOUNT; i++){
            for(j = 0; j < JMAXCOUNT; j++){
                //do some computation to consume time
                /*timerHnd05 = xTimerCreate(
                        "timer05", 
                        pdMS_TO_TICKS(0.5),
                        pdTRUE,
                        (void*)0,
                        vTimerCallback05Expired); */
            }
        }
        // other stuff (if needed))
        
        
        
        //printf(omega);
        //vTaskDelayUntil(&pxPreviousWakeTime,ACQ_PERIOD_MS)
    }
    
}

/*static void vTimerCallback05Expired(xTimerHandle pxTimer){
    
}*/

//
//
//
        // https://mcuoneclipse.com/2018/05/27/tutorial-understanding-and-using-freertos-software-timers
//
//
//


void otherTasks(void *pvParam)
{
    int iTaskTicks = 0;
    uint8_t mesg[80];
    TickType_t pxPreviousWakeTime;
    
    // Initialize the pxPreviousWakeTime variable with the current time
    pxPreviousWakeTime = xTaskGetTickCount();
    TickType_t t;
    TickType_t tb;
    
    for(;;) {
        t = xTaskGetTickCount();
        sprintf(mesg,"A, %d\n\r",t);
        PrintStr(mesg);
        
        /*
        tb = xTaskGetTickCount();
        sprintf(mesg,"B, %d\n\r",tb);
        PrintStr(mesg);
        */
        
        /*
        if (taskHandleB == "B"){
            sprintf(mesg,"B, %d\n\r",);
            PrintStr(mesg);
        }
         * */
        
        TMAN_TaskWaitPeriod();
        
        /*
        //sprintf(mesg,"Task LedFlash (job %d)\n\r",iTaskTicks++);
        //PrintStr(mesg);
        int valueNotification;
        valueNotification = ulTaskNotifyTake(pdTRUE, (TickType_t) portMAX_DELAY);
        
        if(valueNotification > 0){
            printf(" notification received: %d\r\n", valueNotification);
        }
        
        // Wait for the next cycle
        //vTaskDelayUntil(&pxPreviousWakeTime,ACQ_PERIOD_MS);   
        */
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
    //semA = xSemaphoreCreateBinary();
    //semB = xSemaphoreCreateBinary();
    //semC = xSemaphoreCreateBinary();
    //semD = xSemaphoreCreateBinary();
    //semE = xSemaphosreCreateBinary();
    //semF = xSemaphoreCreateBinary();
    
    /* Create the tasks defined within this file. */
    
    
    
    //TMAN_TaskWaitPeriod();
    
    
    //TMAN_TaskAdd();
    
    xTaskCreate( otherTasks,  "A", configMINIMAL_STACK_SIZE, NULL, PRIO_A, NULL );
   
    xTaskCreate( otherTasks,  "B", configMINIMAL_STACK_SIZE, NULL, PRIO_B, NULL );
    /**
    xTaskCreate( otherTasks,  "C", configMINIMAL_STACK_SIZE, NULL, PRIO_C, &taskHandleC );
    xTaskCreate( otherTasks,  "D", configMINIMAL_STACK_SIZE, NULL, PRIO_D, &taskHandleD );
    xTaskCreate( otherTasks,  "E", configMINIMAL_STACK_SIZE, NULL, PRIO_E, &taskHandleE );
    xTaskCreate( otherTasks,  "F", configMINIMAL_STACK_SIZE, NULL, PRIO_F, &taskHandleF );
    */
    //TMAN_TaskRegisterAtributes();
    printf("TMAN_TaskInit\n\r");
    TMAN_Init(ACQ_PERIOD_MS);
    printf("TMAN_TaskAdd\n\r");
    TMAN_TaskAdd();
    
    /*
    printf("TMAN_TaskInit\n\r");
    TMAN_Init(B_PERIOD_MS);
    printf("TMAN_TaskAdd\n\r");
    TMAN_TaskAdd();
    
    */
    //TMAN_TaskWaitPeriod();
        /* Finally start the scheduler. */
	vTaskStartScheduler();

    //int tickTasks = xTaskGetTickCount();
    //printf("%d ticks", tickTasks);
    
    return (0);
    
    
}
