#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include "uart.h"

volatile uint32_t* const ISER = (uint32_t*)0xE000E100;
volatile uint32_t* const ICER = (uint32_t*)0xE000E180;

void main(){
    //disable interrupts
    *ICER = 0xFFFFFFFF;
    config_uart0();
    while (1){
        printf("Hello world!\n\r");
    }
}
