# include "stm32f10x.h"
# include "./flash/bsp_spi_flash.h"
# include "./uart/bsp_uart.h"
# include "ff.h"

FATFS fs;
FRESULT res;
FIL file_p;
char write_buf[] = "这是一个文件系统";
UINT bw;
UINT br;

char read_buf[1024] = {0};

int main(){

	/*调试串口配置*/
	DEBUG_UART_Config();
	printf("\r\n文件系统移植实验\r\n");

	/*挂载文件系统*/
	/*"1:" 设备1, 1 立马挂载*/
	res = f_mount(&fs, "1:", 1);

	if (res == FR_NO_FILESYSTEM){

		printf("\r\nbefore fmkfs\r\n");
		res = f_mkfs("1:", 0, 0);
		
		if (res != FR_OK){
			printf("\r\nf_mkfs res = %d\r\n", res);
		}
	}
	else if (res == FR_OK){
		printf("\r\nf_mount res = %d\r\n", res);

		/*打开设备1 test.txt 文件 读模式， 写模式， 如果没文件就创建文件*/
		res = f_open(&file_p, "1:test.txt", FA_READ | FA_WRITE | FA_CREATE_ALWAYS);

		printf("\r\nf_open res = %d\r\n", res);

		/*写入内容*/
		res = f_write(&file_p, write_buf, sizeof(write_buf), &bw);

		printf("\r\nf_write res = %d\r\n", res);

		res = f_close(&file_p);

		/*打开设备1 test.txt 文件 读模式， 写模式， 如果没文件就创建文件*/
		res = f_open(&file_p, "1:test.txt", FA_READ | FA_OPEN_EXISTING);

		printf("\r\nf_close res = %d\r\n", res);

		res = f_read(&file_p, read_buf, 1024, &br);

		printf("\r\nf_read res = %d, br = %d\r\n", res, br);

		printf("\r\nreadbuf = %s\r\n", read_buf);

		res = f_close(&file_p);
	}
	while(1);
}
