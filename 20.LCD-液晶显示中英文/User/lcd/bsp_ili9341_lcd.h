# ifndef _BSP_ILI9341_LCD_H
# define _BSP_ILI9341_LCD_H

# include "stm32f10x.h"

#define  sFLASH_ID              0X9341    //ILI9341

// ILI9341 GPIO 引脚宏定义

/*BK(背光) 引脚*/
#define  ILI9341_BK_CLK             RCC_APB2Periph_GPIOD
#define  ILI9341_BK_PORT            GPIOD
#define  ILI9341_BK_PIN             GPIO_Pin_2
    
/*CS 引脚*/
#define  ILI9341_CS_CLK             RCC_APB2Periph_GPIOC
#define  ILI9341_CS_PORT            GPIOC
#define  ILI9341_CS_PIN             GPIO_Pin_4

/*RD 引脚*/
#define  ILI9341_RD_CLK             RCC_APB2Periph_GPIOC
#define  ILI9341_RD_PORT            GPIOC
#define  ILI9341_RD_PIN             GPIO_Pin_5

/*WE引脚*/
#define  ILI9341_WE_CLK             RCC_APB2Periph_GPIOC
#define  ILI9341_WE_PORT            GPIOC
#define  ILI9341_WE_PIN             GPIO_Pin_6

/*DC(数据/命令) 引脚*/
#define  ILI9341_DC_CLK             RCC_APB2Periph_GPIOC
#define  ILI9341_DC_PORT            GPIOC
#define  ILI9341_DC_PIN             GPIO_Pin_7

/*D0-D15 引脚*/
#define  ILI9341_DATA_CLK           RCC_APB2Periph_GPIOB
#define  ILI9341_DATA_PORT          GPIOB
#define  ILI9341_DATA_PIN           GPIO_Pin_All

# define LCD_BK_ON()                GPIO_ResetBits(ILI9341_BK_PORT, ILI9341_BK_PIN)
# define LCD_BK_OFF()               GPIO_SetBits(ILI9341_BK_PORT, ILI9341_BK_PIN)

# define LCD_CS_LOW()               GPIO_ResetBits(ILI9341_CS_PORT, ILI9341_CS_PIN)
# define LCD_CS_HIGH()              GPIO_SetBits(ILI9341_CS_PORT, ILI9341_CS_PIN)

# define LCD_RD_LOW()               GPIO_ResetBits(ILI9341_RD_PORT, ILI9341_RD_PIN)
# define LCD_RD_HIGH()              GPIO_SetBits(ILI9341_RD_PORT, ILI9341_RD_PIN)

# define LCD_WE_LOW()               GPIO_ResetBits(ILI9341_WE_PORT, ILI9341_WE_PIN)
# define LCD_WE_HIGH()              GPIO_SetBits(ILI9341_WE_PORT, ILI9341_WE_PIN)

# define LCD_DC_LOW()               GPIO_ResetBits(ILI9341_DC_PORT, ILI9341_DC_PIN)
# define LCD_DC_HIGH()              GPIO_SetBits(ILI9341_DC_PORT, ILI9341_DC_PIN)

# define LCD_DATA_OUT(data)         ILI9341_DATA_PORT->ODR = data
# define LCD_DATA_IN()              GPIO_ReadInputData(ILI9341_DATA_PORT)

# define DEBUG_DELAY()              ILI9341_Delay(0xFFFF)

# define CMD_SetCoordinateX         0x2A    //设置x坐标
# define CMD_SetCoordinateY         0x2B    //设置y坐标
# define CMD_SetPixel               0x2C    //填充像素

# define ILI9341_LESS_PIXEL	  		240			//液晶屏较短方向的像素宽度
# define ILI9341_MORE_PIXEL	 		320			//液晶屏较长方向的像素宽度

/******************************* 定义 ILI934 显示屏常用颜色 ********************************/
#define      BACKGROUND		                BLACK   //默认背景颜色

# define      WHITE		 		            0xFFFF	   //白色
# define      BLACK                         0x0000	   //黑色 
# define      GREY                          0xF7DE	   //灰色 
# define      BLUE                          0x001F	   //蓝色 
# define      BLUE2                         0x051F	   //浅蓝色 
# define      RED                           0xF800	   //红色 
# define      MAGENTA                       0xF81F	   //红紫色，洋红色 
# define      GREEN                         0x07E0	   //绿色 
# define      CYAN                          0x7FFF	   //蓝绿色，青色 
# define      YELLOW                        0xFFE0	   //黄色 
# define      BRED                          0xF81F
# define      GRED                          0xFFE0
# define      GBLUE                         0x07FF

/*写命令*/
void ILI9341_Write_CMD(uint16_t cmd);
/*写数据*/
void ILI9341_Write_Data(uint16_t data);
/*读数据*/
uint16_t ILI9341_Read_Data(void);
/*读取ID*/
uint16_t ILI0341_Read_ID(void);
/*扫描函数*/
void ILI9341_GramScan ( uint8_t ucOption );
/*设置显示的矩形区域*/
void ILI9341_open_Window(uint16_t x, uint16_t y, uint16_t width, uint16_t heigh);
/*画矩形*/
void ILI9341_Draw_Rect(uint16_t x, uint16_t y, uint16_t width, uint16_t heigh, uint16_t color);
/*画点*/
void ILI9341_Draw_Point(uint16_t x, uint16_t y, uint16_t color);
/*ILI9341 液晶初始化*/
void ILI9341_init(void);
/*显示字模*/
void ILI9341_Draw_Character_16(uint16_t x, uint16_t y, uint16_t color, uint8_t a[]);
# endif
