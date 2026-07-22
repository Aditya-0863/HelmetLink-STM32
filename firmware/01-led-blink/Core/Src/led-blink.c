#include <stdint.h>

void delay(volatile uint32_t count)
{
	while(count--);
}

#define rcc_iopenr (*(volatile uint32_t*) 0x40021034)
#define gpioa_moder (*(volatile uint32_t*) 0x50000000)
#define gpioa_odr (*(volatile uint32_t*) 0x50000014)

int main(void){
	rcc_iopenr |= 0x1U<<0;
	gpioa_moder &= ~(0x3U<<10);
	gpioa_moder |= 0x1U<<10;

	while(1)
	    {
	        gpioa_odr |= 0x1U<<5;

	        delay(500000);

	        gpioa_odr &=~(0x1U<<5);

	        delay(500000);
	    }
	}
