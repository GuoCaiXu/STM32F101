# ifndef _BSP_SPI_SLASH_H
# define _BSP_SPI_FLASH_H

# include "stm32f10x.h"
# include "stdio.h"

#define  sFLASH_ID              0XEF4017    //W25Q64

// 串口1-USART1
#define  SPI_FLASHx                     SPI1
#define  SPI_FLASH_CLK                  RCC_APB2Periph_SPI1
#define  SPI_FLASH_APBxClkCmd           RCC_APB2PeriphClockCmd

// SPI GPIO 引脚宏定义
#define  SPI_FLASH_GPIO_CLK             RCC_APB2Periph_GPIOA
#define  SPI_FLASH_GPIO_APBxClkCmd      RCC_APB2PeriphClockCmd
    
#define  SPI_FLASH_SCK_GPIO_PORT        GPIOA   
#define  SPI_FLASH_SCK_GPIO_PIN         GPIO_Pin_5

#define  SPI_FLASH_MOSI_GPIO_PORT       GPIOA
#define  SPI_FLASH_MOSI_GPIO_PIN        GPIO_Pin_7

#define  SPI_FLASH_MISO_GPIO_PORT       GPIOA
#define  SPI_FLASH_MISO_GPIO_PIN        GPIO_Pin_6

#define  SPI_FLASH_CS_GPIO_PORT         GPIOA
#define  SPI_FLASH_CS_GPIO_PIN          GPIO_Pin_4

# define SPI_FLASH_CS_LOW()             GPIO_ResetBits(SPI_FLASH_CS_GPIO_PORT, GPIO_Pin_4);
# define SPI_FLASH_CS_HIGH()             GPIO_SetBits(SPI_FLASH_CS_GPIO_PORT, GPIO_Pin_4);

# define SPI_FLASH_WAIT_TIMEOUT         10000

/*命令定义-开头*******************************/
#define W25X_WriteEnable		        0x06 //允许写使能
#define W25X_WriteDisable		        0x04 //禁止写使能
#define W25X_ReadStatusReg		        0x05 //读取状态寄存器S0 - S7
#define W25X_WriteStatusReg		        0x01 
#define W25X_ReadData			        0x03 //读资料
#define W25X_FastReadData		        0x0B //读资料(比较快)
#define W25X_FastReadDual		        0x3B 
#define W25X_PageProgram		        0x02 //写入数据
#define W25X_BlockErase			        0xD8 
#define W25X_SectorErase		        0x20 //擦除4KB
#define W25X_ChipErase			        0xC7 
#define W25X_PowerDown			        0xB9 //进入一个低功耗模式
#define W25X_ReleasePowerDown	        0xAB //退出低功耗模式
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   	    0x90 
#define W25X_JedecDeviceID		        0x9F

/*flash 初始化*/
void SPI_FLASH_Config(void);

/*发送一个字节*/
uint8_t SPI_FLASH_Send_Data(uint8_t data);

/*接收一个字节*/
uint8_t SPI_FLASH_Receive_Data(void);

/*读取JEDEC_ID*/
uint32_t SPI_FLASH_Read_JEDEC_ID(void);

/*擦除操作*/
void SPI_FLASH_Erase_Sector(uint32_t addr);

/*读取操作*/
void SPI_FLASH_Read_Buffer(uint32_t addr, uint8_t *data, uint32_t size);

/*写入操作*/
void SPI_FLASH_Page_Write(uint32_t addr, uint8_t *data, uint32_t size);

# endif
