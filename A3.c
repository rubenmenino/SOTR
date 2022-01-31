/* 
 * 
 * Author: Paulo Pedreiras
 * Ruben Menino 89185   
 * Joao G�nio 88771
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

#define PRIO_A	 tskIDLE_PRIORITY + 1
#define PRIO_B	 tskIDLE_PRIORITY + 1
#define PRIO_C	 tskIDLE_PRIORITY + 1
#define PRIO_D	 tskIDLE_PRIORITY
#define PRIO_E	 tskIDLE_PRIORITY
#define PRIO_F	 tskIDLE_PRIORITY

int idA = 0;
int idB = 1;
int idC = 2;
TaskHandle_t hA;
TaskHandle_t hB;
TaskHandle_t hC;

void simpleA(void *pvParam)
{
    int iTaskTicks = 0;
    uint8_t mesg[80];
    // Initialize the pxPreviousWakeTime variable with the current time
    TickType_t pxPreviousWakeTime = xTaskGetTickCount();

    TickType_t t;
    
    for(;;) {
        //printf("entra aqui???????????\n");
        
        TMAN_TaskWaitPeriod(idA);
        t = xTaskGetTickCount();
        printf("A %d \n", t);
        
        
    }
}

void simpleB(void *pvParam)
{
    int iTaskTicks = 0;
    uint8_t mesg[80];
    // Initialize the pxPreviousWakeTime variable with the current time
    TickType_t pxPreviousWakeTime = xTaskGetTickCount();

    TickType_t t;
    
    for(;;) {
        //printf("entra aqui???????????\n");
        
        TMAN_TaskWaitPeriod(idB);
        t = xTaskGetTickCount();
        printf("B %d \n", t);
        
        
    }
}

void simpleC(void *pvParam)
{
    int iTaskTicks = 0;
    uint8_t mesg[80];
    // Initialize the pxPreviousWakeTime variable with the current time
    TickType_t pxPreviousWakeTime = xTaskGetTickCount();

    TickType_t t;
    
    for(;;) {
        //printf("entra aqui???????????\n");
        
        TMAN_TaskWaitPeriod(idC);
        t = xTaskGetTickCount();
        printf("C %d \n", t);
        
        
    }
}



int mainSetrLedBlinkA3(int argc, char** argv) {
    // Init UART and redirect tdin/stdot/stderr to UART
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
        while(1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
    
    
    // Welcome message
    printf("TMAN TESTING\n");
    
    TMAN_Init(1000);

    TMAN_TaskAdd(&hA);
    TMAN_TaskRegisterAtributes(idA, 10, 5, 1, -1);
    xTaskCreate( simpleA, "A", configMINIMAL_STACK_SIZE, NULL, PRIO_A, &hA );

    
    TMAN_TaskAdd(&hB);
    TMAN_TaskRegisterAtributes(idB, 10, 5, 1, -1);
    xTaskCreate( simpleB, "B", configMINIMAL_STACK_SIZE, NULL, PRIO_B, &hB );

    TMAN_TaskAdd(&hC);
    TMAN_TaskRegisterAtributes(idC, 10, 5, 1, -1);
    xTaskCreate( simpleC, "C", configMINIMAL_STACK_SIZE, NULL, PRIO_C, &hC );

	vTaskStartScheduler();
    
    return (0);
    
    
}
