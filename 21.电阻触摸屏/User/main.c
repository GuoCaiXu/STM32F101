# include "stm32f10x.h"
# include "./lcd/bsp_ili9341_lcd.h"
# include "./uart/bsp_uart.h"
# include "./fonts/fonts.h"
# include "./lcd/bsp_xpt2046_lcd.h"

int main(){

    DEBUG_UART_Config();
    printf("\r\nLCD 液晶显示实验\r\n");

    ILI9341_init();
    XPT2046_GPIO_Init();

    printf("读取到的ID = %x\r\n", ILI0341_Read_ID());

    while( 1 ){

        if (SPI_XPT2046_INT() == 0){

            uint16_t adc_x, adc_y;
            printf("\r\n检测到触摸\r\n");
            adc_x = XPT2046_Read_adc(XPT2046_CHANEL_Y);
            adc_y = XPT2046_Read_adc(XPT2046_CHANEL_X);

            printf("\r\nadc_x = %d, adc_y = %d\r\n", adc_x, adc_y);
        }
    }
}
