# ifndef _BSP_XPT2046_LCD_H
# define _BSP_XPT2046_LCD_H

# include "stm32f10x.h"

typedef	struct          //Һ������ṹ�� 
{		
	/*����ֵ��ʾ��������*/
   int16_t x;			//��¼���µĴ�������ֵ
   int16_t y; 
	
} strType_XPT2046_Coordinate;   

typedef struct         //У׼ϵ���ṹ�壨����ʹ�ã�
{
    float dX_X,  			 
          dX_Y,     
          dX,   
          dY_X,    
          dY_Y,    
          dY;

} strType_XPT2046_TouchPara;


/***********************xpt2046 GPIO ���ź궨��***********************/

/*SCK ����*/   
# define XPT2046_SPI_SCK_CLK        RCC_APB2Periph_GPIOC
# define  XPT2046_SPI_SCK_PORT      GPIOC  
# define  xpt2046_SCK_PIN           GPIO_Pin_8

/*CS ����*/
# define XPT2046_SPI_CS_CLK         RCC_APB2Periph_GPIOC
# define  XPT2046_SPI_CS_PORT       GPIOC
# define  XPT2046_SPI_CS_PIN        GPIO_Pin_9

/*MOSI ����*/
# define XPT2046_SPI_MOSI_CLK       RCC_APB2Periph_GPIOC
# define  XPT2046_SPI_MOSI_PORT     GPIOC
# define  XPT2046_SPI_MOSI_PIN      GPIO_Pin_10

/*MISO ����*/
# define XPT2046_SPI_MISO_CLK       RCC_APB2Periph_GPIOC
# define  XPT2046_SPI_MISO_PORT     GPIOC
# define  XPT2046_SPI_MISO_PIN      GPIO_Pin_11

/*INT ����*/
# define XPT2046_SPI_INT_CLK        RCC_APB2Periph_GPIOC
# define  XPT2046_SPI_INT_PORT      GPIOC
# define  XPT2046_SPI_INT_PIN       GPIO_Pin_12

/***********************���Ÿߵ͵�ƽ����***********************/

/*SCK*/
# define SPI_XPT2046_SCK_LOW()         GPIO_ResetBits(XPT2046_SPI_SCK_PORT, xpt2046_SCK_PIN)
# define SPI_XPT2046_SCK_HIGH()        GPIO_SetBits(XPT2046_SPI_SCK_PORT, xpt2046_SCK_PIN)

/*CS*/
# define SPI_XPT2046_CS_LOW()          GPIO_ResetBits(XPT2046_SPI_CS_PORT, XPT2046_SPI_CS_PIN)
# define SPI_XPT2046_CS_HIGH()         GPIO_SetBits(XPT2046_SPI_CS_PORT, XPT2046_SPI_CS_PIN)

/*MOSI*/
# define SPI_XPT2046_MOSI_LOW()        GPIO_ResetBits(XPT2046_SPI_MOSI_PORT, XPT2046_SPI_MOSI_PIN)
# define SPI_XPT2046_MOSI_HIGH()       GPIO_SetBits(XPT2046_SPI_MOSI_PORT, XPT2046_SPI_MOSI_PIN)

/***********************��Ϣ���***********************/

/*MISO*/
# define SPI_XPT2046_MISO()            GPIO_ReadInputDataBit(XPT2046_SPI_MISO_PORT, XPT2046_SPI_MISO_PIN)

/*INT*/
# define SPI_XPT2046_INT()             GPIO_ReadInputDataBit(XPT2046_SPI_INT_PORT, XPT2046_SPI_INT_PIN)

/***********************��ʱ����***********************/

/*5us*/
# define Delay()     XPT2046_Delay(5);

/***********************������***********************/
# define XPT2046_CHANEL_X   0x90    //ͨ��Y+��ѡ�������	
# define XPT2046_CHANEL_Y   0xd0    //ͨ��X+��ѡ�������

/***********************XPT2046 ��������***********************/

/*XPT2046���ų�ʼ��*/
void XPT2046_GPIO_Init(void);
/*XPT2046 дһ���ֽ�*/
void XPT2046_Write_Byte(uint8_t data);
/*XPT2046 ��ȡ����*/
uint16_t XPT2046_Read_data(void);
/*XPT2046 ���������ȡ����ֵ*/
uint16_t XPT2046_Read_adc(uint8_t cmd);
void test(uint16_t test[]);

# endif
