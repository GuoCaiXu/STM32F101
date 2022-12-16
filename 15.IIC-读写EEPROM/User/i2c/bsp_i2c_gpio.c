# include "./i2c/bsp_i2c_gpio.h"

//初始化i2c GPIO 函数
void i2c_GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStruct;

    /*SCL 配置*/
    //第一步：打开外设的时钟函数
    RCC_APB2PeriphClockCmd(I2C_SCL_GPIO_CLK | I2C_SDA_GPIO_CLK, ENABLE);  //ENABLE 表示启用参数

    //第二步：配置外设初始化结构体
    GPIO_InitStruct.GPIO_Pin = I2C_SCL_GPIO_PIN;

    //配置模式：开漏输出
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    //配置速度：150MHz
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    //第三步：调用外设初始化函数，把配置好的结构体成员写到寄存器里
    GPIO_Init(I2C_SCL_GPIO_PORT, &GPIO_InitStruct);

    /*SDA配置*/
    GPIO_InitStruct.GPIO_Pin = I2C_SDA_GPIO_PIN;

    GPIO_Init(I2C_SDA_GPIO_PORT, &GPIO_InitStruct);
}

/*延时函数*/
static void i2c_Delay(void){

    uint8_t i;

    for (i = 0; i < 10; i ++);
    /*　
	 	下面的时间是通过逻辑分析仪测试得到的。
    工作条件：CPU主频72MHz ，MDK编译环境，1级优化
  
		循环次数为10时，SCL频率 = 205KHz 
		循环次数为7时，SCL频率 = 347KHz， SCL高电平时间1.5us，SCL低电平时间2.87us 
	 	循环次数为5时，SCL频率 = 421KHz， SCL高电平时间1.25us，SCL低电平时间2.375us 
	*/
}

/*产生起始信号*/
void i2c_START(void){

    EEPROM_I2C_SDA_1();
    EEPROM_I2C_SCL_1();
    i2c_Delay();
    
    EEPROM_I2C_SDA_0();
    i2c_Delay();
    EEPROM_I2C_SCL_0();
    i2c_Delay();
}

/*产生结束信号*/
void i2c_STOP(void){

    EEPROM_I2C_SDA_0();
    EEPROM_I2C_SCL_1();
    i2c_Delay();
    
    EEPROM_I2C_SDA_1();
    i2c_Delay();
}

/*产生应答信号*/
void i2c_ASK(void){

    EEPROM_I2C_SDA_0();
    i2c_Delay();

    EEPROM_I2C_SCL_1();
    i2c_Delay();
    
    EEPROM_I2C_SCL_0();
    i2c_Delay();

    EEPROM_I2C_SDA_1(); //释放控制权
    i2c_Delay();
}

/*产生非应答信号*/
void i2c_NASK(void){

    EEPROM_I2C_SDA_1();
    i2c_Delay();

    EEPROM_I2C_SCL_1();
    i2c_Delay();
    
    EEPROM_I2C_SCL_0();
    i2c_Delay();
}

/*等待应答信号 NASK:1  ASK:0*/
uint8_t i2c_WAIT_ASK(void){

    uint8_t reply;

    EEPROM_I2C_SDA_1(); //释放控制权

    EEPROM_I2C_SCL_1();
    i2c_Delay();

    if (EEPROM_I2C_READ() == 1){

        reply = 1;
    }
    else{
        reply = 0;
    }

    EEPROM_I2C_SCL_0();
    i2c_Delay();

    return reply;
}

/*写入一个字节*/
void i2c_WRITE_BYTE(uint8_t data){

    uint8_t i;

    for (i = 0; i < 8; i ++){

        if (data & 0x80){
            EEPROM_I2C_SDA_1();
        }
        else {
            EEPROM_I2C_SDA_0();
        }
        EEPROM_I2C_SCL_1();
        i2c_Delay();
        EEPROM_I2C_SCL_0();
        i2c_Delay();

        if (i == 7){
            EEPROM_I2C_SDA_1(); //释放控制权
        }
        data <<= 1;
    }
}

/*读取一个字节*/
uint8_t i2c_READ_BYTE(void){

    uint8_t i;
    uint8_t temp = 0;

    for (i = 0; i < 8; i ++){

        temp <<= 1;

        EEPROM_I2C_SCL_1();
        i2c_Delay();

        if (EEPROM_I2C_READ() == 1){
            temp += 1;
        }
        else {

        }

        EEPROM_I2C_SCL_0();
        i2c_Delay();
    }

    return temp;
}
