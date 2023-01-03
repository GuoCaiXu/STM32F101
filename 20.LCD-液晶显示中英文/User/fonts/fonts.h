# ifndef _FONTS_H
# define _FONTS_H

# include "stm32f10x.h"

/*Ӣ����ģ�߶�*/
#define LINE(x) ((x) * (((sFONT *)LCD_GetFont())->Height))

/*������ģ�߶�*/
#define LINEY(x) ((x) * (WIDTH_CH_CHAR))

/*Ӣ����ʾ*/
typedef struct _tFont
{    
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;
  
} sFONT;

extern sFONT Font8x16;
extern sFONT Font16x24;
extern sFONT Font24x32;

/*������ʾ*/
# define WIDTH_CH_CHAR 16
# define HEIGHT_CH_CHAR 16

/*���Ķ�ȡ��ַ*/
# define GBKCODE_START_ADDRESS   406*4096

/*ȡ��ģ����*/
void GetGBKCode(uint8_t * pBuffer, uint16_t c);

# endif
