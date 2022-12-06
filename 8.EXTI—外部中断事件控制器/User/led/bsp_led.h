# ifndef _BSP_LED_H
# define _BSP_LED_H

# include "stm32f10x.h"

# define    LED_GPIO_CLK    RCC_APB2Periph_GPIOC
# define    LED_GPIO_PORT   GPIOC

# define    LED1_GPIO_PIN   GPIO_Pin_2
# define    LED2_GPIO_PIN   GPIO_Pin_3

# define digitalTOGGLE(p, i)    {p->ODR ^= i;}
# define LED1_TOGGLE            digitalTOGGLE(LED_GPIO_PORT, LED1_GPIO_PIN)
# define LED2_TOGGLE            digitalTOGGLE(LED_GPIO_PORT, LED2_GPIO_PIN)

/*初始化LED GPIO 函数*/
void LED_GPIO_Config(void);

# endif