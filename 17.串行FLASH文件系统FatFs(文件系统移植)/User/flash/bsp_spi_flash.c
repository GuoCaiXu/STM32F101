# include "./flash/bsp_spi_flash.h"

/*�ȴ�ʱ��*/
uint32_t time_out = SPI_FLASH_WAIT_TIMEOUT;

/*���Դ�������*/
void SPI_FLASH_Config(void){

    GPIO_InitTypeDef    GPIO_InitStructure;
    SPI_InitTypeDef    SPI_InitStructure;

    /*��һ������ʼ��GPIO*/
    /*��GPIO �˿ڵ�ʱ��*/
    SPI_FLASH_GPIO_APBxClkCmd(SPI_FLASH_GPIO_CLK, ENABLE);

    /*��SPI SCK ��GPIO ����Ϊ���츴��ģʽ*/
    GPIO_InitStructure.GPIO_Pin = SPI_FLASH_SCK_GPIO_PIN;
    /*����ģʽ �������*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_FLASH_SCK_GPIO_PORT, &GPIO_InitStructure);

		/*��SPI MOSI ��GPIO ����Ϊ���츴��ģʽ*/
		GPIO_InitStructure.GPIO_Pin = SPI_FLASH_MOSI_GPIO_PIN;
		GPIO_Init(SPI_FLASH_MOSI_GPIO_PORT, &GPIO_InitStructure);

	
    /*��SPI MISO��GPIO ����Ϊ��������ģʽ*/
    GPIO_InitStructure.GPIO_Pin = SPI_FLASH_MISO_GPIO_PIN;
    /*��������ģʽ*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(SPI_FLASH_MISO_GPIO_PORT, &GPIO_InitStructure);
		
		/*CS �������*/
		GPIO_InitStructure.GPIO_Pin = SPI_FLASH_CS_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(SPI_FLASH_CS_GPIO_PORT, &GPIO_InitStructure);

    /*�ڶ��������ô��ڵĳ�ʼ���ṹ��*/
    /*��SPI ����ʱ��*/
    SPI_FLASH_GPIO_APBxClkCmd(SPI_FLASH_CLK, ENABLE);
    
		/*���� SPI �ṹ�幤��ģʽ*/
		/*������*/
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
		/* ģʽ0*/
		/*����������*/
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
		/*���е͵�ƽ*/
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
		/*û�õ����д*/
		SPI_InitStructure.SPI_CRCPolynomial = 0;
		/*ѡ��һ�δ��ͼ�λ*/
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		/*˫��ȫ˫��*/
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		/*MSB��λǰ����LSB��λǰ��*/
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		/*������*/
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		/*ѡ��Ƭѡ�źſ��Ʒ�ʽ*/
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		
		SPI_Init(SPI_FLASHx, &SPI_InitStructure);
		SPI_Cmd(SPI_FLASHx, ENABLE);
}

/*ȷ���Ƿ�����*/
uint8_t SPI_Timeout_CallBack(uint8_t data){

	printf("SPI ��ⳬʱ��������룺%d\r\n", data);

	return 0;
}

/*����һ���ֽ�*/
uint8_t SPI_FLASH_Send_Data(uint8_t data){

	uint8_t read_temp;

	time_out = SPI_FLASH_WAIT_TIMEOUT;

	/*���TXE SET(1) ���ͻ�����Ϊ�� RESET(0) ���ͻ�������Ϊ��*/
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){
		if (time_out-- == 0){
			return SPI_Timeout_CallBack(1);
		}
	}
	
	/*�ǿվͷ���*/
	SPI_I2S_SendData(SPI1, data);

	time_out = SPI_FLASH_WAIT_TIMEOUT;
	/*���RXNE SET(1) ���ջ������ǿ� RESET(0) ���ջ�����Ϊ��*/
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){
		if (time_out-- == 0){
			return SPI_Timeout_CallBack(2);
		}
	}

	/*����һ���ֽ�*/
	read_temp = SPI_I2S_ReceiveData(SPI1);

	return read_temp;
}

/*����һ���ֽ�*/
uint8_t SPI_FLASH_Receive_Data(void){

	return SPI_FLASH_Send_Data(0xFF);
}

/*��ȡJEDEC_ID*/
uint32_t SPI_FLASH_Read_JEDEC_ID(void){

	uint32_t id;

	/*�����չCS*/
	/*CS �͵�ƽ��ʼһ��ͨѶ*/
	SPI_FLASH_CS_LOW();

	/*����ָ�����*/
	SPI_FLASH_Send_Data(W25X_JedecDeviceID);

	/*�������ֽ�*/
	id = SPI_FLASH_Receive_Data();

	id <<= 8;
	id |= SPI_FLASH_Receive_Data();

	id <<= 8;
	id |= SPI_FLASH_Receive_Data();

	/*CS �ߵ�ƽ����ͨѶ*/
	SPI_FLASH_CS_HIGH();

	return id;
}

/*дʹ��*/
void SPI_FLASH_Write_Enable(void){

	/*�����չCS*/
	/*CS �͵�ƽ��ʼһ��ͨѶ*/
	SPI_FLASH_CS_LOW();

	/*����ָ�����*/
	/*����д����*/
	SPI_FLASH_Send_Data(W25X_WriteEnable);

	/*CS �ߵ�ƽ����ͨѶ*/
	SPI_FLASH_CS_HIGH();
}

/*��ȡ״̬�Ĵ���*/
void SPI_FLASH_WaitForWriteEnd(void){

	uint8_t status;
	
	SPI_FLASH_CS_LOW();

	SPI_FLASH_Send_Data(W25X_ReadStatusReg);

	do{
		status = SPI_FLASH_Receive_Data();//���BUSY��־
	}while(status & 0x01);

	SPI_FLASH_CS_HIGH();
}

/*��������*/
void SPI_FLASH_Erase_Sector(uint32_t addr){

	/*��ȡ״̬�Ĵ���*/
	SPI_FLASH_WaitForWriteEnd();

	/*����ǰ����дʹ��*/
	SPI_FLASH_Write_Enable();

	SPI_FLASH_CS_LOW();

	/*����4KB����*/
	SPI_FLASH_Send_Data(W25X_SectorErase);

	/*���������ֽ� Ҳ���ǵ�ַ*/
	SPI_FLASH_Send_Data((addr & 0xFF0000) >> 16);
	SPI_FLASH_Send_Data((addr & 0x00FF00) >> 8);
	SPI_FLASH_Send_Data(addr & 0xFF);

	SPI_FLASH_CS_HIGH();

	/*��ȡ״̬�Ĵ���*/
	SPI_FLASH_WaitForWriteEnd();
}

/*��ȡ����*/
void SPI_FLASH_Read_Buffer(uint32_t addr, uint8_t *data, uint32_t size){

	uint32_t i;

	SPI_FLASH_CS_LOW();

	/*��ȡ����*/
	SPI_FLASH_Send_Data(W25X_ReadData);

	/*���������ֽ� Ҳ���ǵ�ַ*/
	SPI_FLASH_Send_Data((addr & 0xFF0000) >> 16);
	SPI_FLASH_Send_Data((addr & 0x00FF00) >> 8);
	SPI_FLASH_Send_Data(addr & 0xFF);

	for (i = 0; i < size; i ++){

		*data = SPI_FLASH_Receive_Data();
		data ++;
	}

	SPI_FLASH_CS_HIGH();
}

/*д�����*/
void SPI_FLASH_Page_Write(uint32_t addr, uint8_t *data, uint32_t size){

	uint32_t i;

	for (i = 0; i < size; i++){

		if (i == 0 || (addr % 256 == 0)){

			SPI_FLASH_CS_HIGH();
			
			/*��ȡ״̬�Ĵ���*/
			SPI_FLASH_WaitForWriteEnd();

			/*��ȡ״̬�Ĵ���*/
			SPI_FLASH_WaitForWriteEnd();

			/*����ǰ����дʹ��*/
			SPI_FLASH_Write_Enable();

			SPI_FLASH_CS_LOW();

			/*д����*/
			SPI_FLASH_Send_Data(W25X_PageProgram);

			/*���������ֽ� Ҳ���ǵ�ַ*/
			SPI_FLASH_Send_Data((addr & 0xFF0000) >> 16);
			SPI_FLASH_Send_Data((addr & 0x00FF00) >> 8);
			SPI_FLASH_Send_Data(addr & 0xFF);
		}

		SPI_FLASH_Send_Data(*data); //����Ҫд�������
		data ++;
		addr ++;
	}

	SPI_FLASH_CS_HIGH();

	/*��ȡ״̬�Ĵ���*/
	SPI_FLASH_WaitForWriteEnd();
}
