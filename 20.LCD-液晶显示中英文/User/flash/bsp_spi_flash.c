# include "./flash/bsp_spi_flash.h"

/*等待时间*/
uint32_t time_out = SPI_FLASH_WAIT_TIMEOUT;

/*调试串口配置*/
void SPI_FLASH_Config(void){

    GPIO_InitTypeDef    GPIO_InitStructure;
    SPI_InitTypeDef    SPI_InitStructure;

    /*第一步：初始化GPIO*/
    /*打开GPIO 端口的时钟*/
    SPI_FLASH_GPIO_APBxClkCmd(SPI_FLASH_GPIO_CLK, ENABLE);

    /*将SPI SCK 的GPIO 配置为推挽复用模式*/
    GPIO_InitStructure.GPIO_Pin = SPI_FLASH_SCK_GPIO_PIN;
    /*复用模式 推挽输出*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_FLASH_SCK_GPIO_PORT, &GPIO_InitStructure);

		/*将SPI MOSI 的GPIO 配置为推挽复用模式*/
		GPIO_InitStructure.GPIO_Pin = SPI_FLASH_MOSI_GPIO_PIN;
		GPIO_Init(SPI_FLASH_MOSI_GPIO_PORT, &GPIO_InitStructure);

	
    /*将SPI MISO的GPIO 配置为浮空输入模式*/
    GPIO_InitStructure.GPIO_Pin = SPI_FLASH_MISO_GPIO_PIN;
    /*浮空输入模式*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(SPI_FLASH_MISO_GPIO_PORT, &GPIO_InitStructure);
		
		/*CS 软件控制*/
		GPIO_InitStructure.GPIO_Pin = SPI_FLASH_CS_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(SPI_FLASH_CS_GPIO_PORT, &GPIO_InitStructure);

    /*第二步：配置串口的初始化结构体*/
    /*打开SPI 外设时钟*/
    SPI_FLASH_GPIO_APBxClkCmd(SPI_FLASH_CLK, ENABLE);
    
		/*配置 SPI 结构体工作模式*/
		/*波特率*/
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
		/* 模式0*/
		/*采样沿奇数*/
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
		/*空闲低电平*/
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
		/*没用到随便写*/
		SPI_InitStructure.SPI_CRCPolynomial = 0;
		/*选择一次传送几位*/
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		/*双线全双工*/
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		/*MSB高位前导，LSB低位前导*/
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		/*做主机*/
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		/*选择片选信号控制方式*/
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		
		SPI_Init(SPI_FLASHx, &SPI_InitStructure);
		SPI_Cmd(SPI_FLASHx, ENABLE);
}

/*确认是否正常*/
uint8_t SPI_Timeout_CallBack(uint8_t data){

	printf("SPI 检测超时，错误代码：%d\r\n", data);

	return 0;
}

/*发送一个字节*/
uint8_t SPI_FLASH_Send_Data(uint8_t data){

	uint8_t read_temp;

	time_out = SPI_FLASH_WAIT_TIMEOUT;

	/*检测TXE SET(1) 发送缓冲区为空 RESET(0) 发送缓冲区不为空*/
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){
		if (time_out-- == 0){
			return SPI_Timeout_CallBack(1);
		}
	}
	
	/*非空就发送*/
	SPI_I2S_SendData(SPI1, data);

	time_out = SPI_FLASH_WAIT_TIMEOUT;
	/*检测RXNE SET(1) 接收缓冲区非空 RESET(0) 接收缓冲区为空*/
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){
		if (time_out-- == 0){
			return SPI_Timeout_CallBack(2);
		}
	}

	/*接收一个字节*/
	read_temp = SPI_I2S_ReceiveData(SPI1);

	return read_temp;
}

/*接收一个字节*/
uint8_t SPI_FLASH_Receive_Data(void){

	return SPI_FLASH_Send_Data(0xFF);
}

/*读取JEDEC_ID*/
uint32_t SPI_FLASH_Read_JEDEC_ID(void){

	uint32_t id;

	/*软件扩展CS*/
	/*CS 低电平开始一次通讯*/
	SPI_FLASH_CS_LOW();

	/*发送指令代码*/
	SPI_FLASH_Send_Data(W25X_JedecDeviceID);

	/*读三个字节*/
	id = SPI_FLASH_Receive_Data();

	id <<= 8;
	id |= SPI_FLASH_Receive_Data();

	id <<= 8;
	id |= SPI_FLASH_Receive_Data();

	/*CS 高电平结束通讯*/
	SPI_FLASH_CS_HIGH();

	return id;
}

/*写使能*/
void SPI_FLASH_Write_Enable(void){

	/*软件扩展CS*/
	/*CS 低电平开始一次通讯*/
	SPI_FLASH_CS_LOW();

	/*发送指令代码*/
	/*允许写命令*/
	SPI_FLASH_Send_Data(W25X_WriteEnable);

	/*CS 高电平结束通讯*/
	SPI_FLASH_CS_HIGH();
}

/*读取状态寄存器*/
void SPI_FLASH_WaitForWriteEnd(void){

	uint8_t status;
	
	SPI_FLASH_CS_LOW();

	SPI_FLASH_Send_Data(W25X_ReadStatusReg);

	do{
		status = SPI_FLASH_Receive_Data();//检测BUSY标志
	}while(status & 0x01);

	SPI_FLASH_CS_HIGH();
}

/*擦除操作*/
void SPI_FLASH_Erase_Sector(uint32_t addr){

	/*读取状态寄存器*/
	SPI_FLASH_WaitForWriteEnd();

	/*擦除前必须写使能*/
	SPI_FLASH_Write_Enable();

	SPI_FLASH_CS_LOW();

	/*擦除4KB命令*/
	SPI_FLASH_Send_Data(W25X_SectorErase);

	/*发送三个字节 也就是地址*/
	SPI_FLASH_Send_Data((addr & 0xFF0000) >> 16);
	SPI_FLASH_Send_Data((addr & 0x00FF00) >> 8);
	SPI_FLASH_Send_Data(addr & 0xFF);

	SPI_FLASH_CS_HIGH();

	/*读取状态寄存器*/
	SPI_FLASH_WaitForWriteEnd();
}

/*读取操作*/
void SPI_FLASH_Read_Buffer(uint32_t addr, uint8_t *data, uint32_t size){

	uint32_t i;

	SPI_FLASH_CS_LOW();

	/*读取命令*/
	SPI_FLASH_Send_Data(W25X_ReadData);

	/*发送三个字节 也就是地址*/
	SPI_FLASH_Send_Data((addr & 0xFF0000) >> 16);
	SPI_FLASH_Send_Data((addr & 0x00FF00) >> 8);
	SPI_FLASH_Send_Data(addr & 0xFF);

	for (i = 0; i < size; i ++){

		*data = SPI_FLASH_Receive_Data();
		data ++;
	}

	SPI_FLASH_CS_HIGH();
}

/*写入操作*/
void SPI_FLASH_Page_Write(uint32_t addr, uint8_t *data, uint32_t size){

	uint32_t i;

	for (i = 0; i < size; i++){

		if (i == 0 || (addr % 256 == 0)){

			SPI_FLASH_CS_HIGH();
			
			/*读取状态寄存器*/
			SPI_FLASH_WaitForWriteEnd();

			/*读取状态寄存器*/
			SPI_FLASH_WaitForWriteEnd();

			/*擦除前必须写使能*/
			SPI_FLASH_Write_Enable();

			SPI_FLASH_CS_LOW();

			/*写命令*/
			SPI_FLASH_Send_Data(W25X_PageProgram);

			/*发送三个字节 也就是地址*/
			SPI_FLASH_Send_Data((addr & 0xFF0000) >> 16);
			SPI_FLASH_Send_Data((addr & 0x00FF00) >> 8);
			SPI_FLASH_Send_Data(addr & 0xFF);
		}

		SPI_FLASH_Send_Data(*data); //发送要写入的数据
		data ++;
		addr ++;
	}

	SPI_FLASH_CS_HIGH();

	/*读取状态寄存器*/
	SPI_FLASH_WaitForWriteEnd();
}
