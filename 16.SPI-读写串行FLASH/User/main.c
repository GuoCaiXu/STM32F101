# include "stm32f10x.h"
# include "./flash/bsp_spi_flash.h"
# include "./uart/bsp_uart.h"

/*1 普通存储*/
/*0 长整数，浮点数存储*/

#if 0
uint8_t write_temp[4096] = {0};
uint8_t read_temp[4096] = {0};

int main(){

	uint32_t read_id = 0;
	uint32_t i;

	/*调试串口配置*/
	DEBUG_UART_Config();

	/*调试串口配置*/
	SPI_GPIO_Config();

	printf("\r\n欢迎使用野火开发板\r\n");

	read_id = SPI_FLASH_Read_JEDEC_ID();

	printf("\r\nread_id = %x\r\n", read_id);
	
	SPI_FLASH_Erase_Sector(0);
	
	printf("\r\n擦除完毕\r\n");

	for (i = 0; i < 4096; i ++){
		write_temp[i] = i;
	}

	/*写入操作*/
	SPI_FLASH_Page_Write(0, write_temp, 4096);
	printf("\r\n写入完毕\r\n");

	SPI_FLASH_Read_Buffer(0, read_temp, 4096);

	printf("\r\n读取到的数据:\r\n");
	for (i = 0; i < 4096; i ++){
		printf("%x ", read_temp[i]);
	}
	printf("\r\n");

	for (i = 0; i < 4096; i ++){
		if (write_temp[i] != read_temp[i]){
			printf("\r\n读写不一致\r\n");
			break;
		}
	}
	printf("\r\n校验结束\r\n");
	
	while(1);
}

#else 

/*1 长整数存储*/
/*0 浮点数存储*/

#if 0

int main(){

	uint16_t write_temp = 520;
	uint8_t read_temp[sizeof(write_temp)] = {0};

	uint32_t read_id = 0;

	/*调试串口配置*/
	DEBUG_UART_Config();

	/*调试串口配置*/
	SPI_GPIO_Config();

	printf("\r\n欢迎使用野火开发板\r\n");

	read_id = SPI_FLASH_Read_JEDEC_ID();

	printf("\r\nread_id = %x\r\n", read_id);
	
	/*擦除操作*/
	SPI_FLASH_Erase_Sector(0);
	
	printf("\r\n擦除完毕\r\n");

	/*写入操作*/
	SPI_FLASH_Page_Write(0, (uint8_t*)&write_temp, sizeof(write_temp));
	printf("\r\n写入完毕\r\n");

	SPI_FLASH_Read_Buffer(0, read_temp, sizeof(write_temp));

	printf("\r\n读取到的数据:\r\n");
	printf("read_temp = %d", *(uint16_t *)read_temp);
	
	while(1);
}

#else

/*1 浮点数存储*/
/*0 字符串存储*/

#if 0
int main(){

	double write_temp = 13.14;
	uint8_t read_temp[sizeof(write_temp)] = {0};

	uint32_t read_id = 0;

	/*调试串口配置*/
	DEBUG_UART_Config();

	/*调试串口配置*/
	SPI_GPIO_Config();

	printf("\r\n欢迎使用野火开发板\r\n");

	read_id = SPI_FLASH_Read_JEDEC_ID();

	printf("\r\nread_id = %x\r\n", read_id);
	
	/*擦除操作*/
	SPI_FLASH_Erase_Sector(0);
	
	printf("\r\n擦除完毕\r\n");

	/*写入操作*/
	SPI_FLASH_Page_Write(0, (uint8_t*)&write_temp, sizeof(write_temp));
	printf("\r\n写入完毕\r\n");

	SPI_FLASH_Read_Buffer(0, read_temp, sizeof(write_temp));

	printf("\r\n读取到的数据:\r\n");
	printf("read_temp = %.2lf", *(double *)read_temp);
	
	while(1);
}

#else

int main(){

	char write_temp[] = "你好世界";
	uint8_t read_temp[sizeof(write_temp)] = {0};

	uint32_t read_id = 0;

	/*调试串口配置*/
	DEBUG_UART_Config();

	/*调试串口配置*/
	SPI_GPIO_Config();

	printf("\r\n欢迎使用野火开发板\r\n");

	read_id = SPI_FLASH_Read_JEDEC_ID();

	printf("\r\nread_id = %x\r\n", read_id);
	
	/*擦除操作*/
	SPI_FLASH_Erase_Sector(0);
	
	printf("\r\n擦除完毕\r\n");

	/*写入操作*/
	SPI_FLASH_Page_Write(0, (uint8_t*)&write_temp, sizeof(write_temp));
	printf("\r\n写入完毕\r\n");

	SPI_FLASH_Read_Buffer(0, read_temp, sizeof(write_temp));

	printf("\r\n读取到的数据:\r\n");
	printf("read_temp = %s", (char *)read_temp);
	
	while(1);
}

#endif

#endif

#endif
