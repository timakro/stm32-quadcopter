#include <stdint.h>

void main ()
{
    // Enable I/O port A clock
    *(volatile uint32_t *)0x40021018 = 0x00000004;

    // Configure pin 11 as push-pull output
    *(volatile uint32_t *)0x40010804 &= 0xFFFF0FFF;
    *(volatile uint32_t *)0x40010804 |= 0x00002000;

    while (1) {
        *(volatile uint32_t *)0x40010810 = (1<<11); // Set pin 11
        for (int i = 0; i < 1000000; i++);
        *(volatile uint32_t *)0x40010814 = (1<<11); // Unset pin 11
        for (int i = 0; i < 1000000; i++);
    }
}
