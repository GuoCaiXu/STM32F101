# ifndef _BSP_SISTICK_H
# define _BSP_SISTICK_H

# include "stm32f10x.h"

/*定时器毫秒*/
void SysTick_Delay_ms(uint32_t ms);


/*用中断函数延时*/
void SysTick_Delay_ms_INT(uint32_t ms);

# endif
