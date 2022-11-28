# ifndef _STM32F10X_GPIO_H
# define _STM32F10X_GPIO_H

# include "stm32f10x.h"

# define GPIO_Pin_0     ((uint16_t)(1 << 0))
# define GPIO_Pin_1     ((uint16_t)(1 << 1))
# define GPIO_Pin_2     ((uint16_t)(1 << 2))
# define GPIO_Pin_3     ((uint16_t)(1 << 3))
# define GPIO_Pin_4     ((uint16_t)(1 << 4))
# define GPIO_Pin_5     ((uint16_t)(1 << 5))
# define GPIO_Pin_6     ((uint16_t)(1 << 6))
# define GPIO_Pin_7     ((uint16_t)(1 << 7))
# define GPIO_Pin_8     ((uint16_t)(1 << 8))
# define GPIO_Pin_9     ((uint16_t)(1 << 9))
# define GPIO_Pin_10    ((uint16_t)(1 << 10))
# define GPIO_Pin_11    ((uint16_t)(1 << 11))
# define GPIO_Pin_12    ((uint16_t)(1 << 12))
# define GPIO_Pin_13    ((uint16_t)(1 << 13))
# define GPIO_Pin_14    ((uint16_t)(1 << 14))
# define GPIO_Pin_15    ((uint16_t)(1 << 15))
# define GPIO_Pin_all   ((uint16_t)(1 << 0xffff))

//GPIO 输出速率枚举定义
typedef enum{

    GPIO_Speed_10MHz = 1,
    GPIO_Speed_20MHz,
    GPIO_Speed_50MHz,
}GPIOSpeed_TypeDef;

//GPIO 工作模式枚举定义
typedef enum{ 

    GPIO_Mode_AIN = 0x00,           //模拟输入      (0000 0000)b
    GPIO_Mode_IN_FLOATING = 0x04,   //浮空输入      (0000 0100)b
    GPIO_Mode_IPD = 0x28,           //下拉输入      (0010 1000)b
    GPIO_Mode_IPU = 0x48,           //上拉输入      (0100 1000)b

    GPIO_Mode_Out_OD = 0x14,        //开漏输出      (0001 0100)b
    GPIO_Mode_Out_PP = 0x10,        //推挽输出      (0001 0000)b
    GPIO_Mode_AF_OD = 0x1c,         //复用开漏输出  (0001 1100)b
    GPIO_Mode_AF_PP = 0x18,         //复用推挽输出  (0001 1000)b
}GPIOMode_TypeDef;

//初始化引脚
typedef struct{

    uint16_t GPIO_Pin;  //选择要配置的引脚
    GPIOSpeed_TypeDef GPIO_Speed;  //选择引脚的速率
    GPIOMode_TypeDef GPIO_Mode;  //选择引脚的工作模式
} GPIO_InitTypeDef;

//设置/清除寄存器  设置寄存器位为1
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

//清除寄存器 位为0
void GPIO_RetsetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

//GPIO 初始化函数
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);

# endif