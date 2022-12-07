# include "stm32f10x.h"
# include "./systick/bsp_systick.h"
# include "./led/bsp_led.h"

int main(){
	
	LED_GPIO_Config();
	while(1){
		
		LED1_TOGGLE;
		/*150ms*/
		//SysTick_Delay_ms(150);
		 SysTick_Delay_ms_INT(500);
		LED2_TOGGLE;
		//SysTick_Delay_ms(150);
		 SysTick_Delay_ms_INT(500);

	}
}
