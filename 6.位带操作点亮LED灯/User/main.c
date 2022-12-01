# include "stm32f10x.h"
# include "./led/bsp_led.h"

# define PCout(n)	(*(unsigned int*)(((GPIOC_BASE + 0x0c) & 0xF0000000) + 0x02000000 + (((GPIOC_BASE + 0x0c) & 0x000FFFFF) << 5) + (n << 2)))

//延时函数
void delay(uint32_t z){

	while(z --);
}

int main(void){
	
	//LED GPIO 初始化
	LED_GPIO_Config();
	while(1){

		PCout(2) = 1;
		delay(0xfffff);
		PCout(2) = 0;

		PCout(3) = 1;
		delay(0xfffff);
		PCout(3) = 0;
	}
}