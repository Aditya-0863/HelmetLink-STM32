#include "bt1026x.h"
#include <stdint.h>

#define RCC_APBENR2 (*(volatile uint32_t *) 0x40021040)
#define GPIOA_MODER (*(volatile uint32_t *) 0x50000000)
#define GPIOA_AFRH  (*(volatile uint32_t *) 0x50000024)
#define GPIOA_ODR   (*(volatile uint32_t *) 0x50000014)

#define USART1_CR1  (*(volatile uint32_t *) 0x40013800)
#define USART1_BRR  (*(volatile uint32_t *) 0x4001380C)
#define USART1_ISR  (*(volatile uint32_t *) 0x4001381C)
#define USART1_TDR  (*(volatile uint32_t *) 0x40013828)
#define USART1_RDR  (*(volatile uint32_t *) 0x40013824)


void bt1026x_init(void)
{
    // 1. Enable GPIOA clock (bit 0 of RCC_IOPENR — already done by uart_init, but safe to repeat)
    (*(volatile uint32_t *) 0x40021034) |= (1U << 0);

    // 2. Enable USART1 clock (RCC_APBENR2, bit 14)
    RCC_APBENR2 |= (1U << 14);

    // 3. PA9, PA10 → AF mode (MODER = 10)
    GPIOA_MODER &= ~((0x3U << 18) | (0x3U << 20));
    GPIOA_MODER |=  ((0x2U << 18) | (0x2U << 20));

    // 4. PA9, PA10 → AF1 (AFRH)
    GPIOA_AFRH &= ~((0xFU << 4) | (0xFU << 8));
    GPIOA_AFRH |=  ((0x1U << 4) | (0x1U << 8));

    // 5. PA8 → output (SYS_CTRL)
    GPIOA_MODER &= ~(0x3U << 16);
    GPIOA_MODER |=  (0x1U << 16);

    // 6. Baud rate
    USART1_BRR = 139;

    // 7. Enable TX, RX, USART (TE=bit3, RE=bit2, UE=bit0)
    USART1_CR1 |= ((1U << 3) | (1U << 2) | (1U << 0));
}

void bt1026x_power_on(void)
{
    // PA8 LOW ≥100ms
    GPIOA_ODR &= ~(1U << 8);
    delay(100000);

    // PA8 HIGH ≥100ms
    GPIOA_ODR |= (1U << 8);
    delay(100000);
}

void bt1026x_send_cmd(const char *cmd)
{
    while(*cmd)
    {
        while(!(USART1_ISR & (1U << 7)));  // Wait for TXE
        USART1_TDR = *cmd;
        cmd++;
    }
}

char bt1026x_read(void)
{
    while(!(USART1_ISR & (1U << 5)));  // Wait for RXNE
    return (char)(USART1_RDR & 0xFF);
}
