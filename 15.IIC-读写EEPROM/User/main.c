# include "stm32f10x.h"
# include "./uart/bsp_uart.h"
# include "./led/bsp_led.h" 
# include "./i2c/bsp_i2c_gpio.h"
# include "./i2c/bsp_i2c_ee.h"

int main(){

	
	uint8_t temp[10] = {0};
	
	DEBUG_UART_Config();
	i2c_GPIO_Config();

	
	printf("\r\n欢迎使用\r\n");
	/*   EEPROM  ?    */
	/*1   ??    ?EEPROM*/
	/*0   ?  ?  EEPROM*/
	if (ee_CHECK_DEVICE(EEPROM_ADDR | EEPROM_WRITE_DIR) == 0){
		printf("\r\n检测到EEPROM\r\n");
	}
	else {
		printf("\r\n未检测到EEPROM\r\n");
	}

	if (ee_WRITE_BYTE(2, 13) == 1){
		printf("\r\n写入成功\r\n");
	}
	else {
		printf("\r\n写入失败\r\n");
	}
	
		if (ee_READ_BYTES(1, temp, 2)){
			
			printf("读取成功\r\n");
		}
		else {
			printf("读取失败\r\n");
		}
		
		printf("temp = %d, %d\r\n", temp[0], temp[1]);
	
	while(1);
}
