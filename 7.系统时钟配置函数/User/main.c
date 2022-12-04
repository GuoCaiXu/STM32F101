# include "stm32f10x.h"
# include "./rcc/bsp_clkconfig.h"
# include "./led/bsp_led.h"

void delay(uint32_t z){
	while(z --);
}

int main(){
	
	//HSE_SetSysClk(RCC_PLLMul_9);
	//HSI 配置系统时钟
	HSI_SetSysClk(RCC_PLLMul_16);
	LED_GPIO_Config();
	
	/*MCO 时钟输出配置*/
	MCO_GPIO_Config();
	RCC_MCOConfig(RCC_MCO_SYSCLK);

	while(1){

		LED1_TOGGLE;
		delay(0xfffff);
		LED2_TOGGLE;
		delay(0xfffff);
	}
}