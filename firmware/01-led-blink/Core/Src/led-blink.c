#include <stdint.h>

void delay(volatile uint32_t count){
	while(count--);
}
#define rcc (*(volatile uint32_t*) 0x40021034)
#define moder (*(volatile uint32_t*) 0x50000000)
#define odr (*(volatile uint32_t*) 0x50000014)

int main(void){
	rcc |= 0x1U<<0;
	moder &= ~(0x3U<<10);
	moder |= 0x1U<<10;

	while(1)
	    {
	        odr |= 0x1U<<5;

	        delay(500000);

	        odr &=~(0x1U<<5);

	        delay(500000);
	    }
	}
