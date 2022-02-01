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
#define ACQ_PRIORITY	( tskIDLE_PRIORITY + 3 )
#define PROC_PRIORITY	( tskIDLE_PRIORITY + 2 )
#define OUT_PRIORITY	( tskIDLE_PRIORITY + 1 )

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
        
        sampleADC();   
        
        if(sem1 != NULL){
            if(xSemaphoreGive(sem1) != pdTRUE){
                printf(" \n\r");
            } else{
                xSemaphoreGive(sem1);
            }
        }else{
            printf("There was insufficient FreeRTOS heap available for the semaphore to be created successfully\n\r");
        }
  
 
        // Wait for the next cycle
        vTaskDelayUntil(&pxPreviousWakeTime,ACQ_PERIOD_MS);     
        
      
    }
}

void procA3(void *pvParam)
{
    
    char arr[NUMBER_OF_STRING][MAX_STRING_SIZE] = 
    {
        "one",
        "two",
        "three",
        "four",
        "five",
    };
    
    float lastFiveSamples[5] = {0, 0, 0, 0, 0};
    int i = 0;
    int x;
    float sum = 0;
    int media;
    
    for(;;){
        

    xSemaphoreTake(sem1, PROC_PERIOD_MS);
        printf("xProc takes as input the output of task Acq\n\r");

//        if(i == 0){
//            printf("%d\n",i );
//            printf("%f\n",res);
//            lastFiveSamples[i] = res;
//        }
//        if(i == 1){
//            printf("%d\n",i );
//            printf("%f\n",res);
//            lastFiveSamples[i] = res;
//        }
//        if(i == 2){
//            printf("%d\n",i );
//            printf("%f\n",res);
//            lastFiveSamples[i] = res;
//        }  
//        if(i == 3){
//            printf("%d\n",i );
//            printf("%f\n",res);
//            lastFiveSamples[i] = res;
//        }
//        
//        if(i == 4){
//            printf("%d\n",i );
//            printf("%f\n",res);
//            lastFiveSamples[i] = res;
//        }
//        if(i > 4){
//            i = 0;
//            lastFiveSamples[i] = res;
//        }

//        for(i = 0; i <= 4; i++){
//           lastFiveSamples[i] = res;
//            
//        }
//        
//        for(i= 5; i>=5; i++){
//            i = 0;
//            lastFiveSamples[i] = res;
//            
//        }

        if(i >= 0 && i <= 4){
            printf("%d\n",i );
            printf("%f\n",res);
            lastFiveSamples[i] = res;
        } 
        else if(i > 4){
            printf("%d\n",i );
            printf("%f\n",res);
            i = 0;
            lastFiveSamples[i] = res;
        }
        else{

        }

        for(x = 0; x < 5; x++){
            sum = sum + lastFiveSamples[x];
            printf("%s   =    %f\n",arr[x], lastFiveSamples[x]);

        }

        // Calculate media 5 values
        media = sum / 5;
        outValue = media;
        sum = 0;
        i+= 1;


        xSemaphoreGive(sem2);

    } 
        
        
}
        
    


void outA3(void *pvParam)
{
    char string[MAX];
    
    for(;;){
        if(sem2 != NULL){
            if(xSemaphoreTake(sem2, (TickType_t) 0.1) == pdTRUE){
              
                //itoa(outValue, string, 10);

                printf("Media = %f\n", outValue);
            }
        }
    }

}

void adcModule(){
    // Disable JTAG interface as it uses a few ADC ports
    DDPCONbits.JTAGEN = 0;
    
    // Initialize ADC module
    // Polling mode, AN0 as input
    // Generic part
    AD1CON1bits.SSRC = 7; // Internal counter ends sampling and starts conversion
    AD1CON1bits.CLRASAM = 1; //Stop conversion when 1st A/D converter interrupt is generated and clears ASAM bit automatically
    AD1CON1bits.FORM = 0; // Integer 16 bit output format
    AD1CON2bits.VCFG = 0; // VR+=AVdd; VR-=AVss
    AD1CON2bits.SMPI = 0; // Number (+1) of consecutive conversions, stored in ADC1BUF0...ADCBUF{SMPI}
    AD1CON3bits.ADRC = 1; // ADC uses internal RC clock
    AD1CON3bits.SAMC = 16; // Sample time is 16TAD ( TAD = 100ns)
    // Set AN0 as input
    AD1CHSbits.CH0SA = 0; // Select AN0 as input for A/D converter
    TRISBbits.TRISB0 = 1; // Set AN0 to input mode
    AD1PCFGbits.PCFG0 = 0; // Set AN0 to analog mode
    // Enable module
    AD1CON1bits.ON = 1; // Enable A/D module (This must be the ***last instruction of configuration phase***)
}

void sampleADC(){
    // Get one sample
        IFS1bits.AD1IF = 0; // Reset interrupt flag
        AD1CON1bits.ASAM = 1; // Start conversion
        while (IFS1bits.AD1IF == 0); // Wait fo EOC

        // Convert to 0..3.3V 
        res = (ADC1BUF0 * 3.3) / 1023;

        // Output result
        printf("Voltage: %f\n\r",res);
        //printf("Temp:%f",(res-2.7315)/.01); // For a LM335 directly connected
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
	xTaskCreate( acqA3, ( const signed char * const ) "Acquisition", configMINIMAL_STACK_SIZE, NULL, ACQ_PRIORITY, NULL );
    xTaskCreate( procA3, ( const signed char * const ) "Processing", configMINIMAL_STACK_SIZE, NULL, PROC_PRIORITY, NULL );
    xTaskCreate( outA3, ( const signed char * const ) "Output", configMINIMAL_STACK_SIZE, NULL, OUT_PRIORITY, NULL );

        /* Finally start the scheduler. */
	vTaskStartScheduler();

    return (0);
    
    
}
