# ifndef _FONTS_H
# define _FONTS_H

# include "stm32f10x.h"

/*英文字模高度*/
#define LINE(x) ((x) * (((sFONT *)LCD_GetFont())->Height))

/*中文字模高度*/
#define LINEY(x) ((x) * (WIDTH_CH_CHAR))

/*英文显示*/
typedef struct _tFont
{    
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;
  
} sFONT;

extern sFONT Font8x16;
extern sFONT Font16x24;
extern sFONT Font24x32;

/*中文显示*/
# define WIDTH_CH_CHAR 16
# define HEIGHT_CH_CHAR 16

/*中文读取地址*/
# define GBKCODE_START_ADDRESS   406*4096

/*取字模数据*/
void GetGBKCode(uint8_t * pBuffer, uint16_t c);

# endif
