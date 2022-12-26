# include "stm32f10x.h"
# include "./lcd/bsp_ili9341_lcd.h"
# include "./uart/bsp_uart.h"

int main(){

    DEBUG_UART_Config();
    printf("\r\nLCD 液晶显示实验\r\n");

    ILI9341_init();

    printf("读取到的ID = %x\r\n", ILI0341_Read_ID());
	
    ILI9341_Draw_Rect(0, 0, 100, 100, WHITE);
    ILI9341_Draw_Rect(0, 100, 100, 100, RED);
    ILI9341_Draw_Rect(100, 100, 100, 100, BLUE);
    ILI9341_Draw_Rect(100, 200, 100, 100, YELLOW);
    
    while(1);
}
