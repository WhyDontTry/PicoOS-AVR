/*
 * PicoOS_Test.c
 *
 * Created: 29.04.2024 21:07:19
 * Author : Jack
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "picoos.h"
#include "printf.h"
#include "usart0.h"


static void initialTask(void* arg);
static void pollTask(void *arg);

/* the initial values for the 2 tasks */
static uint8_t t1 = (1 << PORTB5);
static uint8_t t2 = 0x00;

/* The start task for the initialization of the 2 other tasks.
 * This task will be destroyed, when the program runs out of the
 * block
 */
static void initialTask(void *arg) {

    posTaskCreate(pollTask, &t1, 1);
    //posTaskCreate(pollTask, &t2, 1);
}


static void pollTask(void *arg) {
    uint8_t *valuePtr = (uint8_t*) arg;
    uint8_t value = *valuePtr;

    while(1) {
        PORTB ^= value;
		printf("Val: %u\n", value);
		posTaskSleep(MS(500));
    }
}

int main(void)
{
	usart0_init();
	init_printf(NULL, usart0_char);
    DDRB = 1 << PORTB5;
    
    posInit(initialTask, NULL, 1);
    
    return 0;
}

