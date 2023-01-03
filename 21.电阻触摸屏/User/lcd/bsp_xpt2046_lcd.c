# include "./lcd/bsp_xpt2046_lcd.h"

/*
1.��ʼ����������
2.��д���SPI ��д����
3.��XPT ���Ϳ����֣���������X��Y ��ԭʼ��������(��ѹ����)

ԭʼ�����������꣺��ѹ 0-4096 ------ 0-3.3V
�߼����꣺��Ч��Һ�����ķֱ��� x��0-240  y��0-320
*/

/**
 *  @brief  ��ʱ����
 *  @param  nCount  ��ʱnCount us
 *  @retval ��
 */
static void XPT2046_Delay(uint32_t nCount){
	for (; nCount != 0; nCount --);
}

/**
 *  @brief  XPT2046���ų�ʼ��
 *  @param  ��
 *  @retval ��
 */
void XPT2046_GPIO_Init(void){

    GPIO_InitTypeDef    GPIO_InitStructure;

    /*ʹ���������ʱ��*/
    RCC_APB2PeriphClockCmd(XPT2046_SPI_SCK_CLK|XPT2046_SPI_CS_CLK
    |XPT2046_SPI_MOSI_CLK|XPT2046_SPI_MISO_CLK|XPT2046_SPI_INT_CLK
    , ENABLE);

    /*SCK �����������*/
    GPIO_InitStructure.GPIO_Pin = xpt2046_SCK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(XPT2046_SPI_SCK_PORT, &GPIO_InitStructure);

    /*CS �����������*/
    GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_CS_PIN;
    GPIO_Init(XPT2046_SPI_CS_PORT, &GPIO_InitStructure);

    /*MOSI �����������*/
    GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_MOSI_PIN;
    GPIO_Init(XPT2046_SPI_MOSI_PORT, &GPIO_InitStructure);

    /*MISO ���ø�������*/
    GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(XPT2046_SPI_MISO_PORT, &GPIO_InitStructure);

    /*INT ���ø�������*/
    GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_INT_PIN;
    GPIO_Init(XPT2046_SPI_INT_PORT, &GPIO_InitStructure);

    /*ֹͣ�ź� CS ���Ÿߵ�ƽ*/
    SPI_XPT2046_CS_LOW();
}

/**
 *  @brief  XPT2046 дһ���ֽ�
 *  @param  data    Ҫд���һ���ֽ�
 *  @retval ��
 */
void XPT2046_Write_Byte(uint8_t data){

    uint8_t i;
    //SPI_XPT2046_CS_LOW();
    SPI_XPT2046_SCK_LOW();
    SPI_XPT2046_MOSI_LOW();

    for (i = 0; i < 8; i ++){
        if (data & 0x80) {
            SPI_XPT2046_MOSI_HIGH();
        }
        else {
            SPI_XPT2046_MOSI_LOW();
        }

        Delay();
        SPI_XPT2046_SCK_HIGH();
        Delay();
        SPI_XPT2046_SCK_LOW();
        data <<= 1;
    }
    //SPI_XPT2046_CS_HIGH();
}

/**
 *  @brief  XPT2046 ��ȡ����
 *  @param  ��
 *  @retval ����16λ�Ķ�ȡ���ݣ���12λ��Ч
 */
uint16_t XPT2046_Read_data(void){
    
    uint8_t i;
    uint16_t re_data = 0;
    SPI_XPT2046_SCK_HIGH();
    SPI_XPT2046_MOSI_LOW();

    for (i = 0; i < 12; i ++){

        re_data <<= 1;
        SPI_XPT2046_SCK_LOW();
        Delay();
        SPI_XPT2046_SCK_HIGH();
        re_data |= SPI_XPT2046_MISO();
    }
    SPI_XPT2046_CS_HIGH();
    return re_data;
}

/**
 *  @brief  XPT2046 ��ȡ����
 *  @param  cmd ���������
 *  @retval ����16λ�Ķ�ȡ���ݣ���12λ��Ч
 */
uint16_t XPT2046_Read_adc(uint8_t cmd){

    uint16_t temp;
    SPI_XPT2046_CS_LOW();

    XPT2046_Write_Byte(cmd);
    temp = XPT2046_Read_data();

    SPI_XPT2046_CS_HIGH();

    return temp;
}
