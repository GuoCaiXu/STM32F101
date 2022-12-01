# include "stm32f10x.h"
# include "./key/bsp-key.h"
# include "./led/bsp_led.h"

void delay(uint32_t z){
	while(z --);
}

int main(void){
	
	//初始化LED GPIO 函数
	LED_GPIO_Config();
	KEY_GPIO_Config();
	LED1_TOGGLE;
	LED2_TOGGLE;
	while(1){

		if (KEY_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_ON){
			//让LED1 闪烁一次
			LED1_TOGGLE;
			delay(0xfffff);
			LED1_TOGGLE;
		}
		if (KEY_Scan(KEY2_GPIO_PORT, KEY2_GPIO_PIN) == KEY_ON){
			//让LED2 闪烁一次
			LED2_TOGGLE;
			delay(0xfffff);
			LED2_TOGGLE;
		}
	}
}