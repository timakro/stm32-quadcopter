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

    // Configure pin 11 as push-pull output
    GPIOA->CRH &= ~(GPIO_CRH_MODE11 | GPIO_CRH_CNF11);
    GPIOA->CRH |= GPIO_CRH_MODE11_1;

    while (1) {
        GPIOA->BSRR = (1<<11); // Set pin 11
        Delay(500);
        GPIOA->BRR = (1<<11);  // Unset pin 11
        Delay(500);
    }
}
