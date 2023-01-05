# include "./lcd/bsp_xpt2046_lcd.h"

/*
1.初始化驱动引脚
2.编写软件SPI 读写函数
3.向XPT 发送控制字，让它测量X，Y 的原始触摸坐标(电压数据)

原始触摸物理坐标：电压 0-4096 ------ 0-3.3V
逻辑坐标：等效于液晶屏的分辨率 x：0-240  y：0-320
*/

/******************************* 定义 XPT2046 全局变量 ***************************/
//默认触摸参数，不同的屏幕稍有差异，可重新调用触摸校准函数获取
strType_XPT2046_TouchPara strXPT2046_TouchPara[] = { 	
   -0.006464,   -0.073259,  280.358032,    0.074878,    0.002052,   -6.545977,//扫描方式0
    0.086314,    0.001891,  -12.836658,   -0.003722,   -0.065799,  254.715714,//扫描方式1
	0.002782,    0.061522,  -11.595689,    0.083393,    0.005159,  -15.650089,//扫描方式2
	0.089743,   -0.000289,  -20.612209,   -0.001374,    0.064451,  -16.054003,//扫描方式3
	0.000767,   -0.068258,  250.891769,   -0.085559,   -0.000195,  334.747650,//扫描方式4
   -0.084744,    0.000047,  323.163147,   -0.002109,   -0.066371,  260.985809,//扫描方式5
   -0.001848,    0.066984,  -12.807136,   -0.084858,   -0.000805,  333.395386,//扫描方式6
   -0.085470,   -0.000876,  334.023163,   -0.003390,    0.064725,   -6.211169,//扫描方式7
};

/**
 *  @brief  延时函数
 *  @param  nCount  延时nCount us
 *  @retval 无
 */
static void XPT2046_Delay(uint32_t nCount){
	for (; nCount != 0; nCount --);
}

/**
 *  @brief  XPT2046引脚初始化
 *  @param  无
 *  @retval 无
 */
void XPT2046_GPIO_Init(void){

    GPIO_InitTypeDef    GPIO_InitStructure;

    /*使能引脚相关时钟*/
    RCC_APB2PeriphClockCmd(XPT2046_SPI_SCK_CLK|XPT2046_SPI_CS_CLK
    |XPT2046_SPI_MOSI_CLK|XPT2046_SPI_MISO_CLK|XPT2046_SPI_INT_CLK
    , ENABLE);

    /*SCK 配置推挽输出*/
    GPIO_InitStructure.GPIO_Pin = xpt2046_SCK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(XPT2046_SPI_SCK_PORT, &GPIO_InitStructure);

    /*CS 配置推挽输出*/
    GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_CS_PIN;
    GPIO_Init(XPT2046_SPI_CS_PORT, &GPIO_InitStructure);

    /*MOSI 配置推挽输出*/
    GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_MOSI_PIN;
    GPIO_Init(XPT2046_SPI_MOSI_PORT, &GPIO_InitStructure);

    /*MISO 配置浮空输入*/
    GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(XPT2046_SPI_MISO_PORT, &GPIO_InitStructure);

    /*INT 配置浮空输入*/
    GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_INT_PIN;
    GPIO_Init(XPT2046_SPI_INT_PORT, &GPIO_InitStructure);

    /*停止信号 CS 引脚高电平*/
    SPI_XPT2046_CS_LOW();
}

/**
 *  @brief  XPT2046 写一个字节
 *  @param  data    要写入的一个字节
 *  @retval 无
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
 *  @brief  XPT2046 读取数据
 *  @param  无
 *  @retval 返回16位的读取数据，低12位有效
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
 *  @brief  XPT2046 读取数据
 *  @param  cmd 传入的命令
 *  @retval 返回16位的读取数据，低12位有效
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
 *  @brief  XPT2046 触摸采样10次 滤波取平均值
 *  @param  pScreenCoordinate 结构体XY，获取现在XY坐标的精确值
 *  @retval 无
 */
static void XPT2046_ReadAdc_Smooth_XY(strType_XPT2046_Coordinate *pScreenCoordinate){
    uint8_t ucCount = 0, i;
    uint16_t sAD_X, sAD_Y;
    uint16_t sBufferArray[ 2 ][ 10 ] = {{0}, {0}};
    uint16_t sum_X = 0, sum_Y = 0;

    /*储存最大值和最小值*/
    uint16_t lX_Max, lX_Min, lY_Max, lY_Min;

    /*获取10 个物理坐标*/
    for (ucCount = 0; ucCount < 10; ucCount ++){

        sAD_X = XPT2046_Read_adc(XPT2046_CHANEL_X);
        XPT2046_Delay( 1 );
        sAD_Y = XPT2046_Read_adc(XPT2046_CHANEL_Y);

        sBufferArray[0][ucCount] = sAD_X;
        sBufferArray[1][ucCount] = sAD_Y;
    }

    if (ucCount == 10){

        /*采用10 个样本*/
        lX_Max = lX_Min = sBufferArray[0][0];
        lY_Max = lY_Min = sBufferArray[1][0];
        sum_X = sBufferArray[0][0];
        sum_Y = sBufferArray[1][0];

        /*取X，Y 的最大最小值*/
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

        /*去除最小值和最大值之后求平均值*/
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
