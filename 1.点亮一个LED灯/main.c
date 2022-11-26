# include "stm32f10x.h"

//  &= ~用来清0
//  |=  用来写1

void soft_delay(unsigned int count){

    while(count --);
}

int main(void){

    //配置RCC 寄存器，使能GPIOC 口的时钟
    *(unsigned int *)0x40021018 |= (1 << 4);

    GPIOC_CRL |= (1 << (4 * 2));

    GPIOC_ODR &= ~(1 << 2);

    while(1){

        GPIOC_CRL <<= 4;
        soft_delay(0xfffff);
        GPIOC_ODR <<= 1;
        soft_delay(0xfffff);
        GPIOC_CRL >>= 4;
        soft_delay(0xfffff);
        GPIOC_ODR >>= 1;
    }

}

void SystemInit(void){
	
	//函数体为空，目的是为了骗过编译器不报错
}