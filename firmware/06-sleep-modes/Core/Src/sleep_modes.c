#include "sleep_modes.h"
#include <stdint.h>

#define RCC_APBENR1 (*(volatile uint32_t *) 0x4002103C)
#define PWR_CR1     (*(volatile uint32_t *) 0x40007000)
#define SCB_SCR     (*(volatile uint32_t *) 0xE000ED10)

void enter_stop_mode(void)
{
    // Enable PWR clock
    RCC_APBENR1 |= (1U << 28);

    // Select STOP0
    PWR_CR1 &= ~(0x3U << 0);

    // Set SLEEPDEEP
    SCB_SCR |= (1U << 2);

    // Disable SysTick interrupt so it doesn't wake us immediately
    (*(volatile uint32_t *)0xE000E010) &= ~(1U << 1);

    // Sleep
    __asm volatile ("wfi");

    // Re-enable SysTick after wake
    (*(volatile uint32_t *)0xE000E010) |= (1U << 1);

    // Clear SLEEPDEEP
    SCB_SCR &= ~(1U << 2);
}

/* void exti_init(void)
{
    // TODO: Look up EXTI registers in RM0454
    // 1. Map PC13 to EXTI line 13 (which EXTICR register?)
    // 2. Enable falling edge trigger for line 13
    // 3. Unmask line 13 in IMR
    // 4. Enable NVIC IRQ for EXTI4_15
} */
