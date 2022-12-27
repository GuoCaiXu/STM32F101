# include "./lcd/bsp_ili9341_lcd.h"

/*
1.初始化跟液晶控制相关的引脚
  初始化时要确认配置GPIOB 使用的PB3/PB4引脚
2.模拟8080时序
  写命令
  写数据
  读数据
3.通过读取ILI9341的ID测试函数
4.初始化液晶屏及配置扫描方向
5.往LCD坐标x，y写一个特定颜色像素点
*/

//根据液晶扫描方向而变化的XY像素宽度
//调用ILI9341_GramScan函数设置方向时会自动更改
uint16_t LCD_X_LENGTH = ILI9341_LESS_PIXEL;
uint16_t LCD_Y_LENGTH = ILI9341_MORE_PIXEL; 

//液晶屏扫描模式
//参数可选值为0-7
uint8_t LCD_SCAN_MODE = 6;

/*默认背景色*/
static uint16_t CurrentBackColor = BLACK;

static void ILI9341_Delay(uint32_t nCount){
	for (; nCount != 0; nCount --);
}

/*调试串口配置*/
void ILI9341_GPIO_init(void){

    GPIO_InitTypeDef    GPIO_InitStructure;
	/*使能复用时钟AFIO*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	/*把PB3 PB4 引脚用做普通GPIO*/
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    /*使能引脚相关的时钟*/
    RCC_APB2PeriphClockCmd(ILI9341_BK_CLK | ILI9341_CS_CLK | ILI9341_RD_CLK 
	| ILI9341_WE_CLK | ILI9341_DC_CLK | ILI9341_DATA_CLK, ENABLE);

    /*默认全配置成输出模式*/
	/*BK*/
    GPIO_InitStructure.GPIO_Pin = ILI9341_BK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ILI9341_BK_PORT, &GPIO_InitStructure);

	/*CS*/
	GPIO_InitStructure.GPIO_Pin = ILI9341_CS_PIN;
	GPIO_Init(ILI9341_CS_PORT, &GPIO_InitStructure);

	/*RD*/
	GPIO_InitStructure.GPIO_Pin = ILI9341_RD_PIN;
	GPIO_Init(ILI9341_RD_PORT, &GPIO_InitStructure);

	/*WE*/
	GPIO_InitStructure.GPIO_Pin = ILI9341_WE_PIN;
	GPIO_Init(ILI9341_WE_PORT, &GPIO_InitStructure);

	/*DC*/
	GPIO_InitStructure.GPIO_Pin = ILI9341_DC_PIN;
	GPIO_Init(ILI9341_DC_PORT, &GPIO_InitStructure);

	/*D0-D15*/
	GPIO_InitStructure.GPIO_Pin = ILI9341_DATA_PIN;
	GPIO_Init(ILI9341_DATA_PORT, &GPIO_InitStructure);

	LCD_BK_ON();
}

/*写命令*/
void ILI9341_Write_CMD(uint16_t cmd){

	LCD_CS_LOW();
	LCD_DC_LOW();
	LCD_RD_HIGH();

	LCD_DATA_OUT(cmd);

	LCD_WE_LOW();
	LCD_WE_HIGH();
	LCD_CS_HIGH();
}

/*写数据*/
void ILI9341_Write_Data(uint16_t data){

	LCD_CS_LOW();
	LCD_DC_HIGH();
	LCD_RD_HIGH();

	LCD_DATA_OUT(data);

	LCD_WE_LOW();
	LCD_WE_HIGH();
	LCD_CS_HIGH();
}

/*读数据*/
uint16_t ILI9341_Read_Data(void){

	uint16_t data;

	GPIO_InitTypeDef    GPIO_InitStructure;

	/*切换data端口为输入模式*/
	GPIO_InitStructure.GPIO_Pin = ILI9341_DATA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(ILI9341_DATA_PORT, &GPIO_InitStructure);

	LCD_CS_LOW();
	LCD_DC_HIGH();
	LCD_WE_HIGH();
	LCD_RD_LOW();

	data = LCD_DATA_IN();
	
	LCD_RD_HIGH();
	LCD_CS_HIGH();

	/*切换data端口为输出模式*/
	GPIO_InitStructure.GPIO_Pin = ILI9341_DATA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(ILI9341_DATA_PORT, &GPIO_InitStructure);

	return data;
}

/*读取ID*/
uint16_t ILI0341_Read_ID(void){

	uint16_t temp = 0;

	ILI9341_Write_CMD(0xD3);

	ILI9341_Read_Data();
	ILI9341_Read_Data();
	temp = ILI9341_Read_Data();
	temp <<= 8;
	temp |= ILI9341_Read_Data();

	return temp;
}

/*寄存器初始化函数*/
static void ILI9341_REG_Config ( void )
{
    /*  Power control B (CFh)  */
    DEBUG_DELAY  ();
    ILI9341_Write_CMD ( 0xCF  );
    ILI9341_Write_Data ( 0x00  );
    ILI9341_Write_Data ( 0x81  );
    ILI9341_Write_Data ( 0x30  );
    
    /*  Power on sequence control (EDh) */
    DEBUG_DELAY ();
    ILI9341_Write_CMD ( 0xED );
    ILI9341_Write_Data ( 0x64 );
    ILI9341_Write_Data ( 0x03 );
    ILI9341_Write_Data ( 0x12 );
    ILI9341_Write_Data ( 0x81 );
    
    /*  Driver timing control A (E8h) */
    DEBUG_DELAY ();
    ILI9341_Write_CMD ( 0xE8 );
    ILI9341_Write_Data ( 0x85 );
    ILI9341_Write_Data ( 0x10 );
    ILI9341_Write_Data ( 0x78 );
    
    /*  Power control A (CBh) */
    DEBUG_DELAY ();
    ILI9341_Write_CMD ( 0xCB );
    ILI9341_Write_Data ( 0x39 );
    ILI9341_Write_Data ( 0x2C );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x34 );
    //ILI9341_Write_Data ( 0x02 );
    ILI9341_Write_Data ( 0x06 ); //原来是0x02改为0x06可防止液晶显示白屏时有条纹的情况
    
    /* Pump ratio control (F7h) */
    DEBUG_DELAY ();
    ILI9341_Write_CMD ( 0xF7 );
    ILI9341_Write_Data ( 0x20 );
    
    /* Driver timing control B */
    DEBUG_DELAY ();
    ILI9341_Write_CMD ( 0xEA );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x00 );
    
    /* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    DEBUG_DELAY ();
    ILI9341_Write_CMD ( 0xB1 );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x1B );
    
    /*  Display Function Control (B6h) */
    DEBUG_DELAY ();
    ILI9341_Write_CMD ( 0xB6 );
    ILI9341_Write_Data ( 0x0A );
    ILI9341_Write_Data ( 0xA2 );
    
    /* Power Control 1 (C0h) */
    DEBUG_DELAY ();
    ILI9341_Write_CMD ( 0xC0 );
    ILI9341_Write_Data ( 0x35 );
    
    /* Power Control 2 (C1h) */
    DEBUG_DELAY ();
    ILI9341_Write_CMD ( 0xC1 );
    ILI9341_Write_Data ( 0x11 );
    
    /* VCOM Control 1 (C5h) */
    ILI9341_Write_CMD ( 0xC5 );
    ILI9341_Write_Data ( 0x45 );
    ILI9341_Write_Data ( 0x45 );
    
    /*  VCOM Control 2 (C7h)  */
    ILI9341_Write_CMD ( 0xC7 );
    ILI9341_Write_Data ( 0xA2 );
    
    /* Enable 3G (F2h) */
    ILI9341_Write_CMD ( 0xF2 );
    ILI9341_Write_Data ( 0x00 );
    
    /* Gamma Set (26h) */
    ILI9341_Write_CMD ( 0x26 );
    ILI9341_Write_Data ( 0x01 );
    DEBUG_DELAY ();
    
    /* Positive Gamma Correction */
    ILI9341_Write_CMD ( 0xE0 ); //Set Gamma
    ILI9341_Write_Data ( 0x0F );
    ILI9341_Write_Data ( 0x26 );
    ILI9341_Write_Data ( 0x24 );
    ILI9341_Write_Data ( 0x0B );
    ILI9341_Write_Data ( 0x0E );
    ILI9341_Write_Data ( 0x09 );
    ILI9341_Write_Data ( 0x54 );
    ILI9341_Write_Data ( 0xA8 );
    ILI9341_Write_Data ( 0x46 );
    ILI9341_Write_Data ( 0x0C );
    ILI9341_Write_Data ( 0x17 );
    ILI9341_Write_Data ( 0x09 );
    ILI9341_Write_Data ( 0x0F );
    ILI9341_Write_Data ( 0x07 );
    ILI9341_Write_Data ( 0x00 );
    
    /* Negative Gamma Correction (E1h) */
    ILI9341_Write_CMD ( 0XE1 ); //Set Gamma
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x19 );
    ILI9341_Write_Data ( 0x1B );
    ILI9341_Write_Data ( 0x04 );
    ILI9341_Write_Data ( 0x10 );
    ILI9341_Write_Data ( 0x07 );
    ILI9341_Write_Data ( 0x2A );
    ILI9341_Write_Data ( 0x47 );
    ILI9341_Write_Data ( 0x39 );
    ILI9341_Write_Data ( 0x03 );
    ILI9341_Write_Data ( 0x06 );
    ILI9341_Write_Data ( 0x06 );
    ILI9341_Write_Data ( 0x30 );
    ILI9341_Write_Data ( 0x38 );
    ILI9341_Write_Data ( 0x0F );
    
    /* memory access control set */
    DEBUG_DELAY ();
    ILI9341_Write_CMD ( 0x36 ); 	
    ILI9341_Write_Data ( 0xC8 );    /*竖屏  左上角到 (起点)到右下角 (终点)扫描方式*/
    DEBUG_DELAY ();
    
    /* column address control set */
    ILI9341_Write_CMD ( CMD_SetCoordinateX ); 
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0xEF );
    
    /* page address control set */
    DEBUG_DELAY ();
    ILI9341_Write_CMD ( CMD_SetCoordinateY ); 
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x01 );
    ILI9341_Write_Data ( 0x3F );
    
    /*  Pixel Format Set (3Ah)  */
    DEBUG_DELAY ();
    ILI9341_Write_CMD ( 0x3a ); 
    ILI9341_Write_Data ( 0x55 );
    
    /* Sleep Out (11h)  */
    ILI9341_Write_CMD ( 0x11 );	
    ILI9341_Delay ( 0xAFFf<<2 );
    DEBUG_DELAY ();
    
    /* Display ON (29h) */
    ILI9341_Write_CMD ( 0x29 ); 
}

/*扫描函数*/
void ILI9341_GramScan ( uint8_t ucOption )
{	
	//参数检查，只可输入0-7
	if(ucOption >7 )
		return;
	
	//根据模式更新LCD_SCAN_MODE的值，主要用于触摸屏选择计算参数
	LCD_SCAN_MODE = ucOption;
	
	//根据模式更新XY方向的像素宽度
	if(ucOption%2 == 0)	
	{
		//0 2 4 6模式下X方向像素宽度为240，Y方向为320
		LCD_X_LENGTH = ILI9341_LESS_PIXEL;
		LCD_Y_LENGTH =	ILI9341_MORE_PIXEL;
	}
	else				
	{
		//1 3 5 7模式下X方向像素宽度为320，Y方向为240
		LCD_X_LENGTH = ILI9341_MORE_PIXEL;
		LCD_Y_LENGTH =	ILI9341_LESS_PIXEL; 
	}

	//0x36命令参数的高3位可用于设置GRAM扫描方向	
	ILI9341_Write_CMD ( 0x36 ); 
	ILI9341_Write_Data ( 0x08 |(ucOption<<5));//根据ucOption的值设置LCD参数，共0-7种模式
	/*初始化背景为黑色*/
  ILI9341_Write_CMD ( CMD_SetCoordinateX ); 
	ILI9341_Write_Data ( 0x00 );		/* x 起始坐标高8位 */
	ILI9341_Write_Data ( 0x00 );		/* x 起始坐标低8位 */
	ILI9341_Write_Data ( ((LCD_X_LENGTH-1)>>8)&0xFF ); /* x 结束坐标高8位 */	
	ILI9341_Write_Data ( (LCD_X_LENGTH-1)&0xFF );				/* x 结束坐标低8位 */

	ILI9341_Write_CMD ( CMD_SetCoordinateY ); 
	ILI9341_Write_Data ( 0x00 );		/* y 起始坐标高8位 */
	ILI9341_Write_Data ( 0x00 );		/* y 起始坐标低8位 */
	ILI9341_Write_Data ( ((LCD_Y_LENGTH-1)>>8)&0xFF );	/* y 结束坐标高8位 */	 
	ILI9341_Write_Data ( (LCD_Y_LENGTH-1)&0xFF );				/* y 结束坐标低8位 */

	/* 设置屏幕初始化背景颜色 */
	ILI9341_Write_CMD ( CMD_SetPixel );
  {
    uint32_t i;
    for (i = 0; i < LCD_X_LENGTH*LCD_Y_LENGTH; i ++){
    ILI9341_Write_Data(CurrentBackColor);
    }
  }
}

/*设置显示的矩形区域*/
void ILI9341_open_Window(uint16_t x, uint16_t y, uint16_t width, uint16_t heigh){

  ILI9341_Write_CMD(CMD_SetCoordinateX);
  ILI9341_Write_Data((x & 0xFF00) >> 8); //sc 高八位
  ILI9341_Write_Data((x & 0xFF));        //sc 低八位
  ILI9341_Write_Data(((x + width - 1) & 0xFF00) >> 8); //ec 高八位
  ILI9341_Write_Data((x + width - 1) & 0xFF);        //ec 低八位

  ILI9341_Write_CMD(CMD_SetCoordinateY);
  ILI9341_Write_Data((y & 0xFF00) >> 8); //sc 高八位
  ILI9341_Write_Data((y & 0xFF));        //sc 低八位
  ILI9341_Write_Data(((y + heigh - 1) & 0xFF00) >> 8); //ec 高八位
  ILI9341_Write_Data((y + heigh - 1) & 0xFF);        //ec 低八位
}

/*画矩形*/
void ILI9341_Draw_Rect(uint16_t x, uint16_t y, uint16_t width, uint16_t heigh, uint16_t color){
    
  uint32_t i;
  ILI9341_open_Window(x, y, width, heigh);
  ILI9341_Write_CMD(CMD_SetPixel);
  for (i = 0; i < width*heigh; i ++){
    ILI9341_Write_Data(color);
  }
}

/*画点*/
void ILI9341_Draw_Point(uint16_t x, uint16_t y, uint16_t color){

  ILI9341_open_Window(x, y, 1, 1);

  ILI9341_Write_CMD(CMD_SetPixel);
  ILI9341_Write_Data(color);
}

/*显示字模*/
void ILI9341_Draw_Character_16(uint16_t x, uint16_t y, uint16_t color, uint8_t a[]){

  uint32_t i, j;
  uint8_t ch;
  ILI9341_open_Window(x, y, 16, 16);
  ILI9341_Write_CMD(CMD_SetPixel);
  for (i = 0; i < 16; i ++){
    for (j = 0; j < 8; j ++){
      ch = (a[i*2] << j);
      if ((ch & 0x80) == 0){
        ILI9341_Write_Data(CurrentBackColor);
      }
      else{
        ILI9341_Write_Data(color);
      }
    }
    for (j = 0; j < 8; j ++){
      ch = (a[i*2+1] << j);
      if ((ch & 0x80) == 0){
        ILI9341_Write_Data(CurrentBackColor);
      }
      else{
        ILI9341_Write_Data(color);
      }
    }
  }
}

/*ILI9341 液晶初始化*/
void ILI9341_init(){

	ILI9341_GPIO_init();
	ILI9341_REG_Config();
  ILI9341_GramScan(6);
}


