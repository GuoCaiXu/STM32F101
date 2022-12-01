# include "stm32f10x.h"
# include "./led/bsp_led.h"

//软件延时函数
void delay(uint32_t count){

	while(count --);
}

int main(void){
	
	//在程序来到main 函数这里的时候，系统时钟已经配置成72M
	//初始化GPIO 函数
	LED_GPIO_Config();
	while(1){
	
		//设置一个位
		GPIO_SetBits(LED_GPIO_PORT, LED1_GPIO_PIN);
		delay(0xfffff);
		//复位一个位
		GPIO_ResetBits(LED_GPIO_PORT, LED1_GPIO_PIN);
		delay(0xfffff);

		//设置一个位
		GPIO_SetBits(LED_GPIO_PORT, LED2_GPIO_PIN);
		delay(0xfffff);
		//复位一个位
		GPIO_ResetBits(LED_GPIO_PORT, LED2_GPIO_PIN);
		delay(0xfffff);
	}
}