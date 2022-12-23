# include "stm32f10x.h"
# include "./flash/bsp_spi_flash.h"
# include "./uart/bsp_uart.h"

/*1 ��ͨ�洢*/
/*0 ���������������洢*/

#if 0
uint8_t write_temp[4096] = {0};
uint8_t read_temp[4096] = {0};

int main(){

	uint32_t read_id = 0;
	uint32_t i;

	/*���Դ�������*/
	DEBUG_UART_Config();

	/*���Դ�������*/
	SPI_GPIO_Config();

	printf("\r\n��ӭʹ��Ұ�𿪷���\r\n");

	read_id = SPI_FLASH_Read_JEDEC_ID();

	printf("\r\nread_id = %x\r\n", read_id);
	
	SPI_FLASH_Erase_Sector(0);
	
	printf("\r\n�������\r\n");

	for (i = 0; i < 4096; i ++){
		write_temp[i] = i;
	}

	/*д�����*/
	SPI_FLASH_Page_Write(0, write_temp, 4096);
	printf("\r\nд�����\r\n");

	SPI_FLASH_Read_Buffer(0, read_temp, 4096);

	printf("\r\n��ȡ��������:\r\n");
	for (i = 0; i < 4096; i ++){
		printf("%x ", read_temp[i]);
	}
	printf("\r\n");

	for (i = 0; i < 4096; i ++){
		if (write_temp[i] != read_temp[i]){
			printf("\r\n��д��һ��\r\n");
			break;
		}
	}
	printf("\r\nУ�����\r\n");
	
	while(1);
}

#else 

/*1 �������洢*/
/*0 �������洢*/

#if 0

int main(){

	uint16_t write_temp = 520;
	uint8_t read_temp[sizeof(write_temp)] = {0};

	uint32_t read_id = 0;

	/*���Դ�������*/
	DEBUG_UART_Config();

	/*���Դ�������*/
	SPI_GPIO_Config();

	printf("\r\n��ӭʹ��Ұ�𿪷���\r\n");

	read_id = SPI_FLASH_Read_JEDEC_ID();

	printf("\r\nread_id = %x\r\n", read_id);
	
	/*��������*/
	SPI_FLASH_Erase_Sector(0);
	
	printf("\r\n�������\r\n");

	/*д�����*/
	SPI_FLASH_Page_Write(0, (uint8_t*)&write_temp, sizeof(write_temp));
	printf("\r\nд�����\r\n");

	SPI_FLASH_Read_Buffer(0, read_temp, sizeof(write_temp));

	printf("\r\n��ȡ��������:\r\n");
	printf("read_temp = %d", *(uint16_t *)read_temp);
	
	while(1);
}

#else

/*1 �������洢*/
/*0 �ַ����洢*/

#if 0
int main(){

	double write_temp = 13.14;
	uint8_t read_temp[sizeof(write_temp)] = {0};

	uint32_t read_id = 0;

	/*���Դ�������*/
	DEBUG_UART_Config();

	/*���Դ�������*/
	SPI_GPIO_Config();

	printf("\r\n��ӭʹ��Ұ�𿪷���\r\n");

	read_id = SPI_FLASH_Read_JEDEC_ID();

	printf("\r\nread_id = %x\r\n", read_id);
	
	/*��������*/
	SPI_FLASH_Erase_Sector(0);
	
	printf("\r\n�������\r\n");

	/*д�����*/
	SPI_FLASH_Page_Write(0, (uint8_t*)&write_temp, sizeof(write_temp));
	printf("\r\nд�����\r\n");

	SPI_FLASH_Read_Buffer(0, read_temp, sizeof(write_temp));

	printf("\r\n��ȡ��������:\r\n");
	printf("read_temp = %.2lf", *(double *)read_temp);
	
	while(1);
}

#else

int main(){

	char write_temp[] = "�������";
	uint8_t read_temp[sizeof(write_temp)] = {0};

	uint32_t read_id = 0;

	/*���Դ�������*/
	DEBUG_UART_Config();

	/*���Դ�������*/
	SPI_GPIO_Config();

	printf("\r\n��ӭʹ��Ұ�𿪷���\r\n");

	read_id = SPI_FLASH_Read_JEDEC_ID();

	printf("\r\nread_id = %x\r\n", read_id);
	
	/*��������*/
	SPI_FLASH_Erase_Sector(0);
	
	printf("\r\n�������\r\n");

	/*д�����*/
	SPI_FLASH_Page_Write(0, (uint8_t*)&write_temp, sizeof(write_temp));
	printf("\r\nд�����\r\n");

	SPI_FLASH_Read_Buffer(0, read_temp, sizeof(write_temp));

	printf("\r\n��ȡ��������:\r\n");
	printf("read_temp = %s", (char *)read_temp);
	
	while(1);
}

#endif

#endif

#endif
