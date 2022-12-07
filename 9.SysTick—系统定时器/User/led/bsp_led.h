# ifndef _BSP_LED_H
# define _BSP_LED_H

# include "stm32f10x.h"

/*配置led1*/
# define LED1_GPIO_CLK  RCC_APB2Periph_GPIOC
# define LED1_GPIO_PORT GPIOC
# define LED1_GPIO_PIN  GPIO_Pin_2

/*配置led2*/
# define LED2_GPIO_CLK  RCC_APB2Periph_GPIOC
# define LED2_GPIO_PORT GPIOC
# define LED2_GPIO_PIN  GPIO_Pin_3

/*点亮led 宏定义*/
# define digitalTOGGLE(p, i)    {p->ODR ^= i;}
# define LED1_TOGGLE            digitalTOGGLE(LED1_GPIO_PORT, LED1_GPIO_PIN)
# define LED2_TOGGLE            digitalTOGGLE(LED2_GPIO_PORT, LED2_GPIO_PIN)

/*led GPIO 初始化*/
void LED_GPIO_Config(void);

# endif
