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

    GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
    GPIOA->CRL |= GPIO_CRL_MODE0_1;

    GPIOA->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1);
    GPIOA->CRL |= GPIO_CRL_MODE1_1;

    GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
    GPIOA->CRL |= GPIO_CRL_MODE2_1;

    GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);
    GPIOA->CRL |= GPIO_CRL_MODE3_1;

    for (int i = 0; i < 10; i++) {
        GPIOA->BSRR = (1<<11);
        Delay(500);
        GPIOA->BRR = (1<<11);
        Delay(500);
    }

    GPIOA->BSRR = (1<<0);
    GPIOA->BSRR = (1<<1);
    GPIOA->BSRR = (1<<2);
    GPIOA->BSRR = (1<<3);

    Delay(20000);

    GPIOA->BRR = (1<<0);
    GPIOA->BRR = (1<<1);
    GPIOA->BRR = (1<<2);
    GPIOA->BRR = (1<<3);
}
