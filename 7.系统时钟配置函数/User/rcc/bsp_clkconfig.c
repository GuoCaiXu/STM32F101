# include "./rcc/bsp_clkconfig.h"

/*配置系统时钟为72 M 函数*/
void HSE_SetSysClk(uint32_t RCC_PLLMul){
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /*复位RCC 寄存器到默认值*/
    RCC_DeInit();

    /*使能HSE*/
    RCC_HSEConfig(RCC_HSE_ON);

    /*等待HSE 是否稳定*/
    HSEStatus = RCC_WaitForHSEStartUp();

    /*如果HSEStatus 等于 SUCCESS 表示启动成功*/
    if (HSEStatus == SUCCESS){
/*--------------------------------------------------------*/
    /*使能预取指*/
     FLASH->ACR |= FLASH_ACR_PRFTBE;

     /*FLASH 的等待时间*/
			FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
			FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;
/*--------------------------------------------------------*/

    /*配置分频因子*/
        RCC_HCLKConfig(RCC_SYSCLK_Div1); //分一分频
        RCC_PCLK1Config(RCC_HCLK_Div2);
        RCC_PCLK2Config(RCC_HCLK_Div1);

    /*配置锁相环时钟：选择PLL 的时钟源，配置PLL 的倍频因子*/
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul);

    /*使能PLL*/
    RCC_PLLCmd(ENABLE);

    /*等PLL 稳定*/
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    /*选择PLLCLK 为系统时钟*/
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /*等待系统时钟切换完成*/
    while(RCC_GetSYSCLKSource() != 0x08);
    }
    else{
        /*HSE 启动失败 用户可以在这里添加错误处理的代码*/
    }
}

void MCO_GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

//HSI 配置系统时钟
void HSI_SetSysClk(uint32_t RCC_PLLMul){

    __IO uint32_t HSIStatus = 0;   

    /*复位RCC 寄存器到默认值*/
    RCC_DeInit();

    /*使能HSI*/
    RCC_HSICmd(ENABLE);

    /*等待HSI 是否稳定*/
    HSIStatus = RCC->CR & RCC_CR_HSIRDY;

    /*如果HSEStatus 等于 SUCCESS 表示启动成功*/
    if (HSEStatus == SUCCESS){
/*--------------------------------------------------------*/
    /*使能预取指*/
     FLASH->ACR |= FLASH_ACR_PRFTBE;

     /*FLASH 的等待时间*/
			FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
			FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;
/*--------------------------------------------------------*/

    /*配置分频因子*/
        RCC_HCLKConfig(RCC_SYSCLK_Div1); //分一分频
        RCC_PCLK1Config(RCC_HCLK_Div2);
        RCC_PCLK2Config(RCC_HCLK_Div1);

    /*配置锁相环时钟：选择PLL 的时钟源，配置PLL 的倍频因子*/
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul);

    /*使能PLL*/
    RCC_PLLCmd(ENABLE);

    /*等PLL 稳定*/
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    /*选择PLLCLK 为系统时钟*/
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /*等待系统时钟切换完成*/
    while(RCC_GetSYSCLKSource() != 0x08);
    }
    else{
        /*HSE 启动失败 用户可以在这里添加错误处理的代码*/
    }
}