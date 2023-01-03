# ifndef _BSP_ILI9341_LCD_H
# define _BSP_ILI9341_LCD_H

# include "stm32f10x.h"
# include "./fonts/fonts.h"

#define  sFLASH_ID              0X9341    //ILI9341

// ILI9341 GPIO ���ź궨��

/*BK(����) ����*/
#define  ILI9341_BK_CLK             RCC_APB2Periph_GPIOD
#define  ILI9341_BK_PORT            GPIOD
#define  ILI9341_BK_PIN             GPIO_Pin_2
    
/*CS ����*/
#define  ILI9341_CS_CLK             RCC_APB2Periph_GPIOC
#define  ILI9341_CS_PORT            GPIOC
#define  ILI9341_CS_PIN             GPIO_Pin_4

/*RD ����*/
#define  ILI9341_RD_CLK             RCC_APB2Periph_GPIOC
#define  ILI9341_RD_PORT            GPIOC
#define  ILI9341_RD_PIN             GPIO_Pin_5

/*WE����*/
#define  ILI9341_WE_CLK             RCC_APB2Periph_GPIOC
#define  ILI9341_WE_PORT            GPIOC
#define  ILI9341_WE_PIN             GPIO_Pin_6

/*DC(����/����) ����*/
#define  ILI9341_DC_CLK             RCC_APB2Periph_GPIOC
#define  ILI9341_DC_PORT            GPIOC
#define  ILI9341_DC_PIN             GPIO_Pin_7

/*D0-D15 ����*/
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

# define CMD_SetCoordinateX         0x2A    //����x����
# define CMD_SetCoordinateY         0x2B    //����y����
# define CMD_SetPixel               0x2C    //�������

# define ILI9341_LESS_PIXEL	  		240			//Һ�����϶̷�������ؿ��
# define ILI9341_MORE_PIXEL	 		320			//Һ�����ϳ���������ؿ��

# define ILI9341_DispWindow_X_Star  0
# define ILI9341_DispWindow_Y_Star  0

/******************************* ���� ILI934 ��ʾ��������ɫ ********************************/
#define      BACKGROUND		                BLACK   //Ĭ�ϱ�����ɫ

# define      WHITE		 		            0xFFFF	   //��ɫ
# define      BLACK                         0x0000	   //��ɫ 
# define      GREY                          0xF7DE	   //��ɫ 
# define      BLUE                          0x001F	   //��ɫ 
# define      BLUE2                         0x051F	   //ǳ��ɫ 
# define      RED                           0xF800	   //��ɫ 
# define      MAGENTA                       0xF81F	   //����ɫ�����ɫ 
# define      GREEN                         0x07E0	   //��ɫ 
# define      CYAN                          0x7FFF	   //����ɫ����ɫ 
# define      YELLOW                        0xFFE0	   //��ɫ 
# define      BRED                          0xF81F
# define      GRED                          0xFFE0
# define      GBLUE                         0x07FF

/*��ʱ����*/
void ILI9341_Delay(uint32_t nCount);
/*д����*/
void ILI9341_Write_CMD(uint16_t cmd);
/*д����*/
void ILI9341_Write_Data(uint16_t data);
/*������*/
uint16_t ILI9341_Read_Data(void);
/*��ȡID*/
uint16_t ILI0341_Read_ID(void);
/*ɨ�躯��*/
void ILI9341_GramScan ( uint8_t ucOption );
/*������ʾ�ľ�������*/
void ILI9341_open_Window(uint16_t x, uint16_t y, uint16_t width, uint16_t heigh);
/*������*/
void ILI9341_Draw_Rect(uint16_t x, uint16_t y, uint16_t width, uint16_t heigh, uint16_t color);
/*����*/
void ILI9341_Draw_Point(uint16_t x, uint16_t y, uint16_t color);
/*ILI9341 Һ����ʼ��*/
void ILI9341_init(void);
/*��ʾ��ģ*/
void ILI9341_Draw_Character_16(uint16_t x, uint16_t y, uint16_t color, uint8_t a[]);
/*��ʾ�����ַ�*/
void ILI9341_DispChar_EN(uint16_t usX, uint16_t usY, const char cChar);
/*��ʾ���������ַ�*/
void ILI9341_DispChar_CH(uint16_t usX, uint16_t usY, uint16_t usChar);
/*��ʾ����ֽ�*/
void ILI9341_DispString_EN_CH(uint16_t line, const char *pStr);
/*bresenham �㷨���߶�*/
void Bresenhamline(int x0, int y0, int x1, int y1, uint16_t color);
/*������ʾ�����С*/
void LCD_SetFont(sFONT *fonts);
/*���ñ�����ɫ��������ɫ*/
void LCD_SetColors(uint16_t BackColor, uint16_t TextColor);
/*�������������С�Ŀ��*/
sFONT *LCD_GetFont(void);
/*�����������*/
void LCD_Clear(uint16_t line);
# endif
