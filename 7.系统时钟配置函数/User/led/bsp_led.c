# include "./led/bsp_led.h"

//初始化LED GPIO函数
void LED_GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);

    GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;

    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;

    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

}