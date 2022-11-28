# include "stm32f10x.h"
# include "stm32f10x_gpio.h"

void soft_delay(unsigned int z){
    while(z --);
}

int main(void){

    GPIO_InitTypeDef GPIO_InitStruct;

    //配置RCC 寄存器，使能GPIOC 口的时钟
    *(unsigned int *)0x40021018 |= (1 << 4);

    //配置CRL 寄存器引脚
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    //配置为推挽输出
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    //配置引脚速率
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;

    //把值写到寄存器里面 GPIO_Init();
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    while(1){

        GPIO_RetsetBits(GPIOC, GPIO_Pin_2);
        soft_delay(0xfffff);

        GPIO_SetBits(GPIOC, GPIO_Pin_2);
        soft_delay(0xfffff);
    }
}

void SystemInit(void){

    //防止编译器报错
}