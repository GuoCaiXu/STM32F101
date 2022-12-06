# ifndef _BSP_EXTI_KEY_H
# define _BSP_EXTI_KEY_H

# include "stm32f10x.h"

/*按键1*/
# define KEY1_EXTI_GPIO_CLK      RCC_APB2Periph_GPIOA
# define KEY1_EXTI_GPIO_PORT     GPIOA
# define KEY1_EXTI_GPIO_PIN       GPIO_Pin_0

# define KEY1_EXTI_GPIO_PORTSOURCE  GPIO_PortSourceGPIOA
# define KEY1_EXTI_GPIO_PINSOURCE   GPIO_PinSource0
# define KEY1_EXTI_LINE             EXTI_Line0

# define KEY1_EXTI_IRQ              EXTI0_IRQn

# define KEY1_EXTI_IRQHANDLER       EXTI0_IRQHandler

/*按键2*/
# define KEY2_EXTI_GPIO_CLK      RCC_APB2Periph_GPIOC
# define KEY2_EXTI_GPIO_PORT     GPIOC
# define KEY2_EXTI_GPIO_PIN       GPIO_Pin_13

# define KEY2_EXTI_GPIO_PORTSOURCE  GPIO_PortSourceGPIOC
# define KEY2_EXTI_GPIO_PINSOURCE   GPIO_PinSource13
# define KEY2_EXTI_LINE             EXTI_Line13

# define KEY2_EXTI_IRQ               EXTI15_10_IRQn

# define KEY2_EXTI_IRQHANDLER        EXTI15_10_IRQHandler


//配置按键
void EXTI_KEY_Config(void);

# endif

/*1. 初始化要连接到EXTI 的GPIO*/
/*2. 初始化EXTI 用于产生中断/事件*/
/*3.初始化NVIC，用于处理中断*/
/*4.编写中断函数*/