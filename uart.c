#include "uart.h"

volatile unsigned int * const RBR = (unsigned int *)0xA0001000;
volatile char * const THR = (char *)0xA0001000;
volatile unsigned int * const IER = (unsigned int *)0xA0001004;
volatile unsigned int * const IIR = (unsigned int *)0xA0001008;
volatile unsigned int * const FCR = (unsigned int *)0xA0001008;
volatile unsigned int * const LCR = (unsigned int *)0xA000100c;
volatile unsigned int * const MCR = (unsigned int *)0xA0001010;
volatile unsigned int * const LSR = (unsigned int *)0xA0001014;
volatile unsigned int * const MSR = (unsigned int *)0xA0001018;
volatile unsigned int * const SCR = (unsigned int *)0xA000101c;

volatile unsigned int * const DLL = (unsigned int *)0xA0001000;
volatile unsigned int * const DLM = (unsigned int *)0xA0001004;

#define UARTCLK 100000000
#define UARTBAUD 115200
#define UARTDIV (UARTCLK/(16*UARTBAUD))

void config_uart0(){
    //zero out registers
    *LCR=0; //set LCR first to access others
    *IER=0;
    *IIR=0;
    *FCR=0;
    *MCR=0;
    *SCR=0;
    //set baud
    *LCR = 0x80;
    *DLL = UARTDIV;
    *DLM = 0x00;

    //word length 8 bits, 1 stop, no parity
    *LCR=0x03;
    //Disable interrupts
    *IER=0x0;

}

inline void putchar_uart0(char character){
    while (!(*LSR & (1<<5))){} //wait for it to finish
    *THR= character; /* Transmit char */
}

void print_uart0(const char *s) {
    while(*s != '\0') { /* Loop until end of string */
        while (!(*LSR & (1<<5))){} //wait for it to finish
        *THR= (unsigned int)(*s++); /* Transmit char */
    }
}
