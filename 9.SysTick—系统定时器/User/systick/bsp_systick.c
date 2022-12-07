# include "./systick/bsp_systick.h"

/*定时器毫秒*/
void SysTick_Delay_ms(uint32_t ms){

    uint32_t i;

    SysTick_Config(72000);

    for (i = 0; i < ms; i ++){
        while(!((SysTick->CTRL) & (1 << 16)));
    }

    /*失能systick*/
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

volatile uint32_t isr_ms;

/*用中断函数延时*/
void SysTick_Delay_ms_INT(uint32_t ms){

    isr_ms = ms;
    SysTick_Config(72000);

    while(isr_ms);

     /*失能systick*/
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
