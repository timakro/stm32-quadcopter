#include "stm32f10x.h"

volatile uint32_t msTicks;

void SysTick_Handler (void) {
    msTicks++;
}

__INLINE static void Delay (uint32_t dlyTicks) {
    uint32_t curTicks = msTicks;

    while ((msTicks - curTicks) < dlyTicks);
}

void main (void)
{
    // Configure 1 ms interrupts
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);
    }

    // Enable I/O port A clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    // Enable I/O port B clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    // Enable alternate function I/O clock (required for alternate function remapping)
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // Remap JTAG ports to alternate function (frees PA15, PB3, PB4)
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

    GPIOA->CRH &= ~(GPIO_CRH_MODE11 | GPIO_CRH_CNF11);
    GPIOA->CRH |= GPIO_CRH_MODE11_1;

    GPIOA->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);
    GPIOA->CRH |= GPIO_CRH_MODE8_1;

    GPIOB->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1);
    GPIOB->CRL |= GPIO_CRL_MODE1_1;

    GPIOB->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);
    GPIOB->CRL |= GPIO_CRL_MODE3_1;

    while (1) {
        GPIOA->BSRR = (1<<11);
        GPIOB->BRR = (1<<3);
        Delay(100);
        GPIOA->BSRR = (1<<8);
        GPIOA->BRR = (1<<11);
        Delay(100);
        GPIOB->BSRR = (1<<1);
        GPIOA->BRR = (1<<8);
        Delay(100);
        GPIOB->BSRR = (1<<3);
        GPIOB->BRR = (1<<1);
        Delay(100);
    }
}
