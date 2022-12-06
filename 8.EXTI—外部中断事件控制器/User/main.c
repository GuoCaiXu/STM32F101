# include "stm32f10x.h"
# include "./led/bsp_led.h"
# include "./key/bsp_exti_key.h"

int main(void){

	/*初始化LED GPIO 函数*/
	LED_GPIO_Config();
	
	/*等待外部中断的到来，然后去中断服务函数里面执行程序*/
	EXTI_KEY_Config();
	while(1){
		
	}
}