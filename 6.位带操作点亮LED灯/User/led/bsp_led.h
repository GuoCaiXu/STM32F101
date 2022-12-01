# ifndef _BSP_LED_H
# define _BSP_LED_H

# include "stm32f10x.h"

//c 端口时钟线
# define LED_GPIO_CLK   RCC_APB2Periph_GPIOC
//端口C
# define LED_GPIO_PORT  GPIOC

//LED1 引脚
# define LED1_GPIO_PIN  GPIO_Pin_2
//LED2 引脚
# define LED2_GPIO_PIN  GPIO_Pin_3

//点亮LED宏定义
# define digitalTOGGLE(p, i)    {p->ODR ^= i;}
# define LED1_TOGGLE            digitalTOGGLE(LED_GPIO_PORT, LED1_GPIO_PIN)
# define LED1_TOGGLE            digitalTOGGLE(LED_GPIO_PORT, LED2_GPIO_PIN)

//初始化LED GPIO函数
void LED_GPIO_Config();

# endif