# ifndef _BSP_CLKCONFIG_H
# define _BSP_CLKCONFIG_H

# include "stm32f10x.h"

//配置系统时钟为72 M 函数
void HSE_SetSysClk(uint32_t RCC_PLLMul);

void MCO_GPIO_Config(void);

//HSI 配置系统时钟
void HSI_SetSysClk(uint32_t RCC_PLLMul);

# endif