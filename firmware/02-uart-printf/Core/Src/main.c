#include <stdint.h>

#define rcc_iopenr (*(volatile uint32_t*) 0x40021034)
#define rcc_apbenr1 (*(volatile uint32_t*)0x4002103C)
#define gpioa_moder (*(volatile uint32_t*) 0x50000000)
#define gpioa_afrl (*(volatile uint32_t*) 0x50000020)
#define usart2_brr (*(volatile uint32_t*) 0x4000440C)
#define usart2_cr1 (*(volatile uint32_t*) 0x40004400)
#define usart2_tdr (*(volatile uint32_t*) 0x40004428)
#define usart2_isr (*(volatile uint32_t*) 0x4000441C)
#define usart2_base (*(volatile uint32_t*) 0x40004400)


#define gpioa_odr    (*(volatile uint32_t *) 0x50000014)

void delay(volatile uint32_t count)
{
    while(count--);
}

void uart_send(char c){
    while(!(usart2_isr & (1U << 7))){
    	 }
    usart2_tdr=c;
	}

void uart_send_string(const char *str)
{
    while(*str)
    {
        uart_send(*str);
        str++;
    }
}

int __io_putchar(int ch)
{
    uart_send((char)ch);
    return ch;
}

int main(void){
	rcc_iopenr |= 0x1U<<0;
	rcc_apbenr1 |= 0x1U<<17;

	gpioa_moder &= ~(0x3U << 10);
	gpioa_moder |=  (0x1U << 10);

	gpioa_moder &= ~((0x3U<<4)|(0x3U<<6));
	gpioa_moder |= (0x2U<<4)|(0x2U<<6);

	gpioa_afrl &= ~((0xFU<<8)|(0xFU<<12));
	gpioa_afrl |=  (0x1U<<8)|(0x1U<<12);

	usart2_brr = 139;

    usart2_cr1 |= (0x1U<<0) | (0x1U<<3);



    printf("HelmetLink UART OK\r\n");

    while(1)
        {
            gpioa_odr ^= (1U << 5);   // Toggle LED
            delay(500000);
        }
}

