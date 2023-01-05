# include "stm32f10x.h"
# include "./lcd/bsp_ili9341_lcd.h"
# include "./uart/bsp_uart.h"
# include "./fonts/fonts.h"
# include "./lcd/bsp_xpt2046_lcd.h"

int main(){
	
    uint16_t test_read[2] = {0};
    DEBUG_UART_Config();
    printf("\r\nLCD 液晶显示实验\r\n");

    ILI9341_init();
    XPT2046_GPIO_Init();

    printf("读取到的ID = %x\r\n", ILI0341_Read_ID());

    ILI9341_DispString_EN_CH(LINE(1), "           开始!");

    while( 1 ){

        if (SPI_XPT2046_INT() == 0){

            printf("\r\n检测到触摸\r\n");

            test(test_read);

            printf("adc_x = %d, adc_y = %d", test_read[0], test_read[1]);

            //ILI9341_Draw_Point(test_read[0], test_read[1], WHITE);
            if (test_read[1] == LINE(1)){
                LCD_Clear(LINE(1));
                ILI9341_DispString_EN_CH(LINE(1), "          欢迎使用!");
            }
        }
    }
}
