# include "./key/bsp-key.h"

//GPIO 按键初始化
void KEY_GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStruct;

    //第一步：打开时钟
    RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK | KEY2_GPIO_CLK, ENABLE);  //ENABLE 表示启用参数

    //第二步：配置外设相关的结构体
   GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN;   //配置管脚
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
	
	//初始化另外一个按键
	GPIO_InitStruct.GPIO_Pin = KEY2_GPIO_PIN;
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStruct);
}

//按键扫描函数
uint8_t KEY_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){

    if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON){ //读取外部引脚函数

        //while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON);
        return KEY_ON;
    }
    else return KEY_OFF;
}