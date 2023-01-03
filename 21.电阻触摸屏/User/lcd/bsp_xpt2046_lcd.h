# ifndef _BSP_XPT2046_LCD_H
# define _BSP_XPT2046_LCD_H

# include "stm32f10x.h"

/***********************xpt2046 GPIO 引脚宏定义***********************/

/*SCK 引脚*/   
# define XPT2046_SPI_SCK_CLK        RCC_APB2Periph_GPIOC
# define  XPT2046_SPI_SCK_PORT      GPIOC  
# define  xpt2046_SCK_PIN           GPIO_Pin_8

/*CS 引脚*/
# define XPT2046_SPI_CS_CLK         RCC_APB2Periph_GPIOC
# define  XPT2046_SPI_CS_PORT       GPIOC
# define  XPT2046_SPI_CS_PIN        GPIO_Pin_9

/*MOSI 引脚*/
# define XPT2046_SPI_MOSI_CLK       RCC_APB2Periph_GPIOC
# define  XPT2046_SPI_MOSI_PORT     GPIOC
# define  XPT2046_SPI_MOSI_PIN      GPIO_Pin_10

/*MISO 引脚*/
# define XPT2046_SPI_MISO_CLK       RCC_APB2Periph_GPIOC
# define  XPT2046_SPI_MISO_PORT     GPIOC
# define  XPT2046_SPI_MISO_PIN      GPIO_Pin_11

/*INT 引脚*/
# define XPT2046_SPI_INT_CLK        RCC_APB2Periph_GPIOC
# define  XPT2046_SPI_INT_PORT      GPIOC
# define  XPT2046_SPI_INT_PIN       GPIO_Pin_12

/***********************引脚高低电平控制***********************/

/*SCK*/
# define SPI_XPT2046_SCK_LOW()         GPIO_ResetBits(XPT2046_SPI_SCK_PORT, xpt2046_SCK_PIN)
# define SPI_XPT2046_SCK_HIGH()        GPIO_SetBits(XPT2046_SPI_SCK_PORT, xpt2046_SCK_PIN)

/*CS*/
# define SPI_XPT2046_CS_LOW()          GPIO_ResetBits(XPT2046_SPI_CS_PORT, XPT2046_SPI_CS_PIN)
# define SPI_XPT2046_CS_HIGH()         GPIO_SetBits(XPT2046_SPI_CS_PORT, XPT2046_SPI_CS_PIN)

/*MOSI*/
# define SPI_XPT2046_MOSI_LOW()        GPIO_ResetBits(XPT2046_SPI_MOSI_PORT, XPT2046_SPI_MOSI_PIN)
# define SPI_XPT2046_MOSI_HIGH()       GPIO_SetBits(XPT2046_SPI_MOSI_PORT, XPT2046_SPI_MOSI_PIN)

/***********************信息输出***********************/

/*MISO*/
# define SPI_XPT2046_MISO()            GPIO_ReadInputDataBit(XPT2046_SPI_MISO_PORT, XPT2046_SPI_MISO_PIN)

/*INT*/
# define SPI_XPT2046_INT()             GPIO_ReadInputDataBit(XPT2046_SPI_INT_PORT, XPT2046_SPI_INT_PIN)

/***********************延时函数***********************/

/*5us*/
# define Delay()     XPT2046_Delay(5);

/***********************控制字***********************/
# define XPT2046_CHANEL_X   0x90    //通道Y+的选择控制字	
# define XPT2046_CHANEL_Y   0xd0    //通道X+的选择控制字

/***********************XPT2046 函数定义***********************/

/*XPT2046引脚初始化*/
void XPT2046_GPIO_Init(void);
/*XPT2046 写一个字节*/
void XPT2046_Write_Byte(uint8_t data);
/*XPT2046 读取数据*/
uint16_t XPT2046_Read_data(void);
/*XPT2046 发送命令读取返回值*/
uint16_t XPT2046_Read_adc(uint8_t cmd);

# endif
