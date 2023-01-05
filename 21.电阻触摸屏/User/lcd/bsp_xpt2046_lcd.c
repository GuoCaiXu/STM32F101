# include "./lcd/bsp_xpt2046_lcd.h"

/*
1.��ʼ����������
2.��д���SPI ��д����
3.��XPT ���Ϳ����֣���������X��Y ��ԭʼ��������(��ѹ����)

ԭʼ�����������꣺��ѹ 0-4096 ------ 0-3.3V
�߼����꣺��Ч��Һ�����ķֱ��� x��0-240  y��0-320
*/

/******************************* ���� XPT2046 ȫ�ֱ��� ***************************/
//Ĭ�ϴ�����������ͬ����Ļ���в��죬�����µ��ô���У׼������ȡ
strType_XPT2046_TouchPara strXPT2046_TouchPara[] = { 	
   -0.006464,   -0.073259,  280.358032,    0.074878,    0.002052,   -6.545977,//ɨ�跽ʽ0
    0.086314,    0.001891,  -12.836658,   -0.003722,   -0.065799,  254.715714,//ɨ�跽ʽ1
	0.002782,    0.061522,  -11.595689,    0.083393,    0.005159,  -15.650089,//ɨ�跽ʽ2
	0.089743,   -0.000289,  -20.612209,   -0.001374,    0.064451,  -16.054003,//ɨ�跽ʽ3
	0.000767,   -0.068258,  250.891769,   -0.085559,   -0.000195,  334.747650,//ɨ�跽ʽ4
   -0.084744,    0.000047,  323.163147,   -0.002109,   -0.066371,  260.985809,//ɨ�跽ʽ5
   -0.001848,    0.066984,  -12.807136,   -0.084858,   -0.000805,  333.395386,//ɨ�跽ʽ6
   -0.085470,   -0.000876,  334.023163,   -0.003390,    0.064725,   -6.211169,//ɨ�跽ʽ7
};

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

/**
 *  @brief  XPT2046 ��������10�� �˲�ȡƽ��ֵ
 *  @param  pScreenCoordinate �ṹ��XY����ȡ����XY����ľ�ȷֵ
 *  @retval ��
 */
static void XPT2046_ReadAdc_Smooth_XY(strType_XPT2046_Coordinate *pScreenCoordinate){
    uint8_t ucCount = 0, i;
    uint16_t sAD_X, sAD_Y;
    uint16_t sBufferArray[ 2 ][ 10 ] = {{0}, {0}};
    uint16_t sum_X = 0, sum_Y = 0;

    /*�������ֵ����Сֵ*/
    uint16_t lX_Max, lX_Min, lY_Max, lY_Min;

    /*��ȡ10 ����������*/
    for (ucCount = 0; ucCount < 10; ucCount ++){

        sAD_X = XPT2046_Read_adc(XPT2046_CHANEL_X);
        XPT2046_Delay( 1 );
        sAD_Y = XPT2046_Read_adc(XPT2046_CHANEL_Y);

        sBufferArray[0][ucCount] = sAD_X;
        sBufferArray[1][ucCount] = sAD_Y;
    }

    if (ucCount == 10){

        /*����10 ������*/
        lX_Max = lX_Min = sBufferArray[0][0];
        lY_Max = lY_Min = sBufferArray[1][0];
        sum_X = sBufferArray[0][0];
        sum_Y = sBufferArray[1][0];

        /*ȡX��Y �������Сֵ*/
        for (i = 1; i < 10; i ++){
            if (sBufferArray[0][i] > lX_Max) 
                lX_Max = sBufferArray[0][i];
            else if (sBufferArray[0][i] < lX_Min) 
                lX_Min = sBufferArray[0][i];
            if (sBufferArray[1][i] > lY_Max) 
                lX_Max = sBufferArray[1][i];
            else if (sBufferArray[1][i] < lY_Min) 
                lX_Min = sBufferArray[1][i];

            sum_X += sBufferArray[0][i];
            sum_Y += sBufferArray[1][i];
        }

        /*ȥ����Сֵ�����ֵ֮����ƽ��ֵ*/
        pScreenCoordinate->x = (sum_X - lX_Max - lX_Min) >> 3;
        pScreenCoordinate->y = (sum_Y - lY_Max - lY_Min) >> 3;
    }
}

void test(uint16_t test[]){

    static strType_XPT2046_Coordinate Now_XY;

    XPT2046_ReadAdc_Smooth_XY(&Now_XY);

    test[0] = ((strXPT2046_TouchPara[6].dX_X*Now_XY.x) + (strXPT2046_TouchPara[6].dX_Y*Now_XY.y) + strXPT2046_TouchPara[6].dX);
    test[1] = ((strXPT2046_TouchPara[6].dY_X*Now_XY.x) + (strXPT2046_TouchPara[6].dY_Y*Now_XY.y) + strXPT2046_TouchPara[6].dY);
}
