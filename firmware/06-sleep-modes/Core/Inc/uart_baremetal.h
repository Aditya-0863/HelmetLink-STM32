#ifndef uart_baremetal_h
#define uart_baremetal_h

#include <stdint.h>
#include <stdio.h>

// Expose these so main.c can use them
#define gpioa_odr (*(volatile uint32_t *) 0x50000014)
void delay(volatile uint32_t count);

// UART functions
void uart_init(void);
void uart_send(char c);
void uart_send_string(const char *str);
int __io_putchar(int ch);

#endif
