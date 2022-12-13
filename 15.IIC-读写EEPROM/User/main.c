# include "stm32f10x.h"
# include "./uart/bsp_uart.h"
# include "./led/bsp_led.h" 
# include "./i2c/bsp_i2c_gpio.h"
# include "./i2c/bsp_i2c_ee.h"

int main(){

	
	uint8_t temp[10] = {0};
	
	DEBUG_UART_Config();
	i2c_GPIO_Config();

	
	printf("\r\n��ӭʹ��\r\n");
	/*   EEPROM  ?    */
	/*1   ??    ?EEPROM*/
	/*0   ?  ?  EEPROM*/
	if (ee_CHECK_DEVICE(EEPROM_ADDR | EEPROM_WRITE_DIR) == 0){
		printf("\r\n��⵽EEPROM\r\n");
	}
	else {
		printf("\r\nδ��⵽EEPROM\r\n");
	}

	if (ee_WRITE_BYTE(2, 13) == 1){
		printf("\r\nд��ɹ�\r\n");
	}
	else {
		printf("\r\nд��ʧ��\r\n");
	}
	
		if (ee_READ_BYTES(1, temp, 2)){
			
			printf("��ȡ�ɹ�\r\n");
		}
		else {
			printf("��ȡʧ��\r\n");
		}
		
		printf("temp = %d, %d\r\n", temp[0], temp[1]);
	
	while(1);
}
