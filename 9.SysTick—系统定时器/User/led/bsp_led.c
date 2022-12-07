# include "./led/bsp_led.h"

/*led GPIO 初始化*/
void LED_GPIO_Config(void){

    GPIO_InitTypeDef    GPIO_InitStruct;

    /*打开外设的时钟*/
    RCC_APB2PeriphClockCmd(LED1_GPIO_CLK, ENABLE);
	
    /*配置外设初始化结构体*/
		GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;
        /*配置模式*/
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        /*配置速度*/
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);

        GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN;
	
		GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
}
