# include "stm32f10x.h"
# include "./uart/bsp_uart.h"
# include "./i2c/bsp_i2c_gpio.h"
# include "./i2c/bsp_i2c_ee.h"

/*1 ��ͨ�洢*/
/*0 �洢��������������*/

#if		0
int main(){

	uint16_t i;
	uint8_t r_temp[256] = {0}, w_temp[256] = {0};
	
	DEBUG_UART_Config();
	i2c_GPIO_Config();

	
	printf("\r\n��ӭʹ��\r\n");
	/*   EEPROM  ?    */
	/*1   ������EEPROM*/
	/*0   ����EEPROM*/
	if (ee_CHECK_DEVICE(EEPROM_ADDR | EEPROM_WRITE_DIR) == 0){
		printf("\r\n��⵽EEPROM\r\n");

		for (i = 0; i < 256; i ++){
			w_temp[i] = i;
		}
	}
	else {
		printf("\r\nδ��⵽EEPROM\r\n");
	}

	if (ee_WRITE_BYTES(0, w_temp, 256) == 1){
		printf("\r\nд��ɹ�\r\n");
	}
	else {
		printf("\r\nд��δ�ɹ�\r\n");
	}
	
		if (ee_READ_BYTES(0, r_temp, 256)){
			
			printf("��ȡ�ɹ�\r\n");
		}
		else {
			printf("��ȡʧ��\r\n");
		}
		
		for (i = 0; i < 256; i ++){
			printf("\r\ntemp%d \t=\t %d\r\n", i, r_temp[i]);
		}
	while(1);
}

#else

/*1 �������洢*/
/*0 �������洢*/

#if 0

int main(){

	/*������*/
	uint16_t w_temp = 520;
	uint8_t r_temp[sizeof(w_temp)] = {0};

	DEBUG_UART_Config();
	i2c_GPIO_Config();

	ee_WRITE_BYTES(0, (uint8_t *)&w_temp, sizeof(w_temp));
	ee_READ_BYTES(0, r_temp, sizeof(w_temp));

	printf("r_temp = %d\r\n", *(uint16_t *)r_temp);

	while(1);
}

#else

int main(){

	/*������*/
	double w_temp = 520.1314;
	uint8_t r_temp[sizeof(w_temp)] = {0};

	DEBUG_UART_Config();
	i2c_GPIO_Config();

	ee_WRITE_BYTES(0, (uint8_t *)&w_temp, sizeof(w_temp));
	ee_READ_BYTES(0, r_temp, sizeof(w_temp));

	printf("r_temp = %.4lf\r\n", *(double *)r_temp);

	while(1);
}

#endif

#endif
