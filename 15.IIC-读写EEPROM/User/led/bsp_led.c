# include "./led/bsp_led.h"

//初始化LED GPIO 函数
void LED_GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStruct;

    //第一步：打开外设的时钟函数
    RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);  //ENABLE 表示启用参数

    //第二步：配置外设初始化结构体
    GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;

    //配置模式：推挽输出
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    //配置速度：10MHz
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;

    //第三步：调用外设初始化函数，把配置好的结构体成员写到寄存器里
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

    //第二个LED 灯配置
    GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN;

    //配置模式：推挽输出
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    //配置速度：10MHz
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;

    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}
