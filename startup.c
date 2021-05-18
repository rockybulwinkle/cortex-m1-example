#include <stdint.h>

/* Initialize segments */
extern uint32_t _stext;
extern uint32_t _etext;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sstack;
extern uint32_t _estack;

/** \cond DOXYGEN_SHOULD_SKIP_THIS */
int main(void);
/** \endcond */

void __libc_init_array(void);

void Reset_Handler(void);

void NMI_Handler(void){
    while(1){}
}

void HardFault_Handler(void){
    while(1){}
}
void SVC_Handler(void){
    while(1){}
}
void PendSV_Handler(void){
    while(1){}
}
void SysTick_Handler(void){
    while(1){}
}

typedef struct _DeviceVectors
{
    /* Stack pointer */
    void* pvStack;

    /* Cortex-M handlers */
    void* pfnReset_Handler;
    void* pfnNMI_Handler;
    void* pfnHardFault_Handler;
    void* pfnReservedM12;
    void* pfnReservedM11;
    void* pfnReservedM10;
    void* pfnReservedM9;
    void* pfnReservedM8;
    void* pfnReservedM7;
    void* pfnReservedM6;
    void* pfnSVC_Handler;
    void* pfnReservedM4;
    void* pfnReservedM3;
    void* pfnPendSV_Handler;
    void* pfnSysTick_Handler;
} DeviceVectors;


/* Exception Table */
__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {

    /* Configure Initial Stack Pointer, using linker-generated symbols */
    .pvStack                = (void*) (&_estack),

    .pfnReset_Handler       = (void*) Reset_Handler,
    .pfnNMI_Handler         = (void*) NMI_Handler,
    .pfnHardFault_Handler   = (void*) HardFault_Handler,
    .pfnReservedM12          = (void*) (0UL), /* Reserved */
    .pfnReservedM11          = (void*) (0UL), /* Reserved */
    .pfnReservedM10          = (void*) (0UL), /* Reserved */
    .pfnReservedM9           = (void*) (0UL), /* Reserved */
    .pfnReservedM8           = (void*) (0UL), /* Reserved */
    .pfnReservedM7           = (void*) (0UL), /* Reserved */
    .pfnReservedM6           = (void*) (0UL), /* Reserved */
    .pfnSVC_Handler         = (void*) SVC_Handler,
    .pfnReservedM4           = (void*) (0UL), /* Reserved */
    .pfnReservedM3           = (void*) (0UL), /* Reserved */
    .pfnPendSV_Handler      = (void*) PendSV_Handler,
    .pfnSysTick_Handler     = (void*) SysTick_Handler,
};

/*
 *  This is the code that gets called on processor reset.
 *  To initialize the device, and call the main() routine.
 */
void Reset_Handler(void)
{
    /* Initialize the data segment */
    uint32_t *pSrc = &_etext;
    uint32_t *pDest = &_sdata;

    if (pSrc != pDest) {
        for (; pDest < &_edata;) {
            *pDest++ = *pSrc++;
        }
    }

    /* Clear the zero segment */
    for (pDest = &_sbss; pDest < &_ebss;) {
        *pDest++ = 0;
    }

    /* Run constructors / initializers */
    __libc_init_array();

    /* Branch to main function */
    main();

    /* Infinite loop */
    while (1);
}

