# include "./key/bsp_exti_key.h"

/*配置NVIC*/
void NVIC_Config(void){

  NVIC_InitTypeDef  NVIC_InitTStruct;
  /*第一步：配置中断优先级的分组*/
  /*中断源*/
	NVIC_InitTStruct.NVIC_IRQChannel = KEY1_EXTI_IRQ;

  /*第二步：配置NVIC 的初始化结构体*/
  /*抢占优先级*/
  NVIC_InitTStruct.NVIC_IRQChannelPreemptionPriority = 1;
  /*子优先级*/
	 NVIC_InitTStruct.NVIC_IRQChannelSubPriority = 0;
   /*使能*/
	 NVIC_InitTStruct.NVIC_IRQChannelCmd = ENABLE;

   /*第三步：调用NVIC 初始化函数把配置好的结构体成员写到寄存器里面*/
   NVIC_Init(&NVIC_InitTStruct);

   /*配置KEY2*/
   NVIC_InitTStruct.NVIC_IRQChannel = KEY2_EXTI_IRQ;
   NVIC_InitTStruct.NVIC_IRQChannelPreemptionPriority = 1;
  /*子优先级*/
	 NVIC_InitTStruct.NVIC_IRQChannelSubPriority = 1;
   /*使能*/
	 NVIC_InitTStruct.NVIC_IRQChannelCmd = ENABLE;

   /*第三步：调用NVIC 初始化函数把配置好的结构体成员写到寄存器里面*/
   NVIC_Init(&NVIC_InitTStruct);
}

/*配置按键*/
void EXTI_KEY_Config(void){

    GPIO_InitTypeDef    GPIO_InitStruct;
    /*EXTI 的结构体指针*/
    EXTI_InitTypeDef    EXTI_InitStruct;
    /*配置NVIC*/
    NVIC_Config();

    /*1. 初始化要连接到EXTI 的GPIO*/
    /*第一步：打开外设的时钟*/
    RCC_APB2PeriphClockCmd(KEY1_EXTI_GPIO_CLK | KEY2_EXTI_GPIO_CLK, ENABLE);

    /*第二步：配置外设初始化结构体*/
		GPIO_InitStruct.GPIO_Pin = KEY1_EXTI_GPIO_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    /*第三步：调用外设初始化函数，把配置好的结构体成员写到寄存器里面*/
		GPIO_Init(KEY1_EXTI_GPIO_PORT, &GPIO_InitStruct);


    /*初始化key2 的GPIO*/
		GPIO_InitStruct.GPIO_Pin = KEY2_EXTI_GPIO_PIN;

		GPIO_Init(KEY2_EXTI_GPIO_PORT, &GPIO_InitStruct);

        /*2. 初始化EXTI 用于产生中断/事件*/
        /*打开时钟*/
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        /*选择输入线*/
        GPIO_EXTILineConfig(KEY1_EXTI_GPIO_PORTSOURCE, KEY1_EXTI_GPIO_PINSOURCE);
        EXTI_InitStruct.EXTI_Line = KEY1_EXTI_LINE;
				EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
        /*上伸延触发*/
				EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
        /*使能*/
        EXTI_InitStruct.EXTI_LineCmd = ENABLE;

        /*初始化结构体*/
        EXTI_Init(&EXTI_InitStruct);

        /*配置按键2 的*/
        /*选择输入线*/
        GPIO_EXTILineConfig(KEY2_EXTI_GPIO_PORTSOURCE, KEY2_EXTI_GPIO_PINSOURCE);
        EXTI_InitStruct.EXTI_Line = KEY2_EXTI_LINE;
				EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
        /*下降延触发*/
				EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
        /*使能*/
        EXTI_InitStruct.EXTI_LineCmd = ENABLE;
        EXTI_Init(&EXTI_InitStruct);
}