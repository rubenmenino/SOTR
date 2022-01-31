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
#define PRIO_D	 tskIDLE_PRIORITY + 1
#define PRIO_E	 tskIDLE_PRIORITY + 1
#define PRIO_F	 tskIDLE_PRIORITY + 1

int idA = 0;
int idB = 1;
int idC = 2;
int idD = 3;
int idE = 4;
int idF = 5;
int tman_ticks = 1000;


void simpleA(void *pvParam)
{
    TickType_t t;
    
    for(;;) {
        //printf("entra aqui???????????\n");
        
        TMAN_TaskWaitPeriod(idA);
        t = xTaskGetTickCount() / tman_ticks;
        printf("A, %d \n", t);
 

    }
}

void simpleB(void *pvParam)
{
    TickType_t t;
    
    for(;;) {
        //printf("entra aqui???????????\n");
        
        TMAN_TaskWaitPeriod(idB);
        t = xTaskGetTickCount() / tman_ticks;
        printf("B, %d \n", t);

        
        
    }
}

void simpleC(void *pvParam)
{
    TickType_t t;
    
    for(;;) {
        //printf("entra aqui???????????\n");
        
        TMAN_TaskWaitPeriod(idC);
        t = xTaskGetTickCount() / tman_ticks;
        printf("C, %d \n", t);

        
        
    }
}

void simpleD(void *pvParam)
{
    TickType_t t;
    
    for(;;) {
        //printf("entra aqui???????????\n");
        
        TMAN_TaskWaitPeriod(idD);
        t = xTaskGetTickCount() / tman_ticks;
        printf("D, %d \n", t);

        
        
    }
}

void simpleE(void *pvParam)
{
    TickType_t t;
    
    for(;;) {
        //printf("entra aqui???????????\n");
        
        TMAN_TaskWaitPeriod(idE);
        t = xTaskGetTickCount() / tman_ticks;
        printf("E, %d \n", t);

        
        
    }
}

void simpleF(void *pvParam)
{
    TickType_t t;
    
    for(;;) {
        //printf("entra aqui???????????\n");
        
        TMAN_TaskWaitPeriod(idF);
        t = xTaskGetTickCount() / tman_ticks;
        printf("F, %d \n", t);
    
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
    
    TMAN_Init(tman_ticks);

    
    TMAN_TaskAdd();
    TMAN_TaskRegisterAtributes(idA, 8, 8, 4, -1); // id, period, deadline, phase, precedence
    xTaskCreate( simpleA, "A", configMINIMAL_STACK_SIZE, NULL, PRIO_A, NULL );

    TMAN_TaskAdd();
    TMAN_TaskRegisterAtributes(idB, 4, 4, 0, 0);
    xTaskCreate( simpleB, "B", configMINIMAL_STACK_SIZE, NULL, PRIO_B, NULL );
/*
    TMAN_TaskAdd();
    TMAN_TaskRegisterAtributes(idC, 3, 1, 50, -1);
    xTaskCreate( simpleC, "C", configMINIMAL_STACK_SIZE, NULL, PRIO_C, NULL );
/*
    TMAN_TaskAdd();
    TMAN_TaskRegisterAtributes(idD, 4, 1, 50, -1);
    xTaskCreate( simpleD, "D", configMINIMAL_STACK_SIZE, NULL, PRIO_D, NULL );
    
    TMAN_TaskAdd();
    TMAN_TaskRegisterAtributes(idE, 5, 1, 50, -1);
    xTaskCreate( simpleE, "E", configMINIMAL_STACK_SIZE, NULL, PRIO_E, NULL );
    
    TMAN_TaskAdd();
    TMAN_TaskRegisterAtributes(idF, 6, 1, 50, -1);
    xTaskCreate( simpleF, "F", configMINIMAL_STACK_SIZE, NULL, PRIO_F, NULL );
     */
    //printf("%d number of Activations\n", TMAN_TaskStats(idF));

    
    
    
	vTaskStartScheduler();
    TMAN_Close();
    return (0);
    
    
}
