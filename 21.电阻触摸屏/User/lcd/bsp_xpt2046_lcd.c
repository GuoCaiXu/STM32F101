# include "./lcd/bsp_xpt2046_lcd.h"

/*
1.初始化驱动引脚
2.编写软件SPI 读写函数
3.向XPT 发送控制字，让它测量X，Y 的原始触摸坐标(电压数据)

原始触摸物理坐标：电压 0-4096 ------ 0-3.3V
逻辑坐标：等效于液晶屏的分辨率 x：0-240  y：0-320
*/

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
