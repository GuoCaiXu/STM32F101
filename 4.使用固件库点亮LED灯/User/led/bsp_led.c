//bsp   board support package   板级支持包

# include "./led/bsp_led.h"     //如果不在魔法棒里添加头文件可以这样操作

//初始化GPIO 函数
void LED_GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStruct;

    //第一步：打开外设的时钟
    RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);   //ENABLE 表示启用参数

    //第二步：配置外设初始化结构体
    GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;
    //配置模式：推挽输出
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    //配置速度：10MHz
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;

    //第三步：调用外设初始化函数，把配置好的结构体成员写到寄存器里面
    GPIO_Init(GPIOC, &GPIO_InitStruct);


    //第二个led 灯
     GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN;
    //配置模式：推挽输出
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    //配置速度：10MHz
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;

    GPIO_Init(GPIOC, &GPIO_InitStruct);
}