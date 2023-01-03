# include "stm32f10x.h"
# include "./lcd/bsp_ili9341_lcd.h"
# include "./uart/bsp_uart.h"
# include "./fonts/fonts.h"

int main(){

    char dispBuff[100];
    uint32_t i;

    DEBUG_UART_Config();
    printf("\r\nLCD 液晶显示实验\r\n");

    ILI9341_init();

    printf("读取到的ID = %x\r\n", ILI0341_Read_ID());

    ILI9341_DispString_EN_CH(LINE(0), "Hello World");
    LCD_SetFont(&Font16x24);
    ILI9341_DispString_EN_CH(LINE(1), "Hello World");
    LCD_SetFont(&Font24x32);
    ILI9341_DispString_EN_CH(LINE(2), "Hello World");
    LCD_Clear(LINE(2));
    LCD_Clear(LINE(3));
    LCD_SetFont(&Font8x16);
    ILI9341_DispString_EN_CH(LINE(3), "Hello World");
    ILI9341_DispString_EN_CH(LINE(5), "你好世界!");
    ILI9341_DispString_EN_CH(LINE(6), "徐国彩");
    Bresenhamline(50,170,210,230, RED);  
    Bresenhamline(50,200,210,240, RED);
    Bresenhamline(100,170,200,230, GREEN);
    Bresenhamline(200,200,220,240, GREEN);
    Bresenhamline(70,170,110,230, BLUE);
    Bresenhamline(130,200,220,240, BLUE);


    for(i = 0; i < 9999; i ++){
        sprintf(dispBuff, "Count: %d ", i);
        LCD_Clear(LINE(4));
        ILI9341_DispString_EN_CH(LINE(4), dispBuff);
        ILI9341_Delay(0xfffff);
    }

    while(1);
}
