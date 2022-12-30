# include "stm32f10x.h"
# include "./lcd/bsp_ili9341_lcd.h"
# include "./uart/bsp_uart.h"

int main(){

    DEBUG_UART_Config();
    printf("\r\nLCD 液晶显示实验\r\n");

    ILI9341_init();

    printf("读取到的ID = %x\r\n", ILI0341_Read_ID());

    ILI9341_DispString_EN(LINE(0), "Hello World");
    LCD_SetFont(&Font16x24);
    ILI9341_DispString_EN(LINE(1), "Hello World");
    LCD_SetFont(&Font24x32);
    ILI9341_DispString_EN(LINE(2), "Hello World");
    
    while(1);
}
