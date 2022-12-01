# include "./led/bsp_led.h"

//初始化LED GPIO函数
void LED_GPIO_Config(){

    GPIO_InitTypeDef GPIO_InitStruct;

    //第一步：开始外设的时钟
    RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);

    //第二步：配置外设初始化结构体
    GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;

    //配置模式：推挽输出
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;

    //配置速度
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;

    //第三步：调用外设初始化函数，把配置好的结构体成员写到寄存器里
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

    //配置LED2 小灯
    GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN;

    //配置模式：推挽输出
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;

    //配置速度
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;

    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

}