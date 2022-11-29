# ifndef __STM32F10X_H
# define __STM32F10X_H
//寄存器的映射代码

//peripheral 外设

//所有的外设的基地址
# define PERIPH_BASE    ((unsigned int)0x40000000)

//总基地址
# define APB1PERIPH_BASE    PERIPH_BASE
# define APB2PERIPH_BASE    (PERIPH_BASE + 0x00010000)
# define AHBPERIPH_BASE     (PERIPH_BASE + 0x00018000)

# define GPIOA_BASE     (APB2PERIPH_BASE + 0x0800)
# define GPIOB_BASE     (APB2PERIPH_BASE + 0x0c00)
# define GPIOC_BASE     (APB2PERIPH_BASE + 0x1000)
# define GPIOD_BASE     (APB2PERIPH_BASE + 0x1400)

//端口c
//# define GPIOC_CRL      (*(unsigned int * ) (GPIOC_BASE + 0x00))  //配置低位寄存器
//# define GPIOC_CRH      (*(unsigned int * ) (GPIOC_BASE + 0x04))  //配置高位寄存器
//# define GPIOC_IDR      (*(unsigned int * ) (GPIOC_BASE + 0x08))  //输入数据寄存器
//# define GPIOC_ODR      (*(unsigned int * ) (GPIOC_BASE + 0x0c))  //输出数据寄存器
//# define GPIOC_BSRR     (*(unsigned int * ) (GPIOC_BASE + 0x10))  //设置/清除寄存器
//# define GPIOC_BRR      (*(unsigned int * ) (GPIOC_BASE + 0x14))  //清除寄存器
//# define GPIOC_LCKR     (*(unsigned int * ) (GPIOC_BASE + 0x18))  //配置锁定寄存器

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

//定义结构体利用结构体的内存对齐
typedef struct {

    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
    uint32_t LCKR;
} GPIO_TypeDef;

# define GPIOA      ((GPIO_TypeDef *) GPIOA_BASE)
# define GPIOB      ((GPIO_TypeDef *) GPIOB_BASE)
# define GPIOC      ((GPIO_TypeDef *) GPIOC_BASE)
# define GPIOD      ((GPIO_TypeDef *) GPIOD_BASE)

# endif