# ifndef _BSP_I2C_GPIO_H
# define _BSP_I2C_GPIO_H

# include "stm32f10x.h"

# define I2C_SCL_GPIO_CLK   RCC_APB2Periph_GPIOC
# define I2C_SCL_GPIO_PORT  GPIOA
# define I2C_SCL_GPIO_PIN   GPIO_Pin_2

# define I2C_SDA_GPIO_CLK   RCC_APB2Periph_GPIOC
# define I2C_SDA_GPIO_PORT  GPIOA
# define I2C_SDA_GPIO_PIN   GPIO_Pin_3

/*控制引脚电平*/
# define EEPROM_I2C_SDA_1()     GPIO_SetBits(I2C_SDA_GPIO_PORT, I2C_SDA_GPIO_PIN)
# define EEPROM_I2C_SDA_0()     GPIO_ResetBits(I2C_SDA_GPIO_PORT, I2C_SDA_GPIO_PIN)

# define EEPROM_I2C_SCL_1()     GPIO_SetBits(I2C_SCL_GPIO_PORT, I2C_SCL_GPIO_PIN)
# define EEPROM_I2C_SCL_0()     GPIO_ResetBits(I2C_SCL_GPIO_PORT, I2C_SCL_GPIO_PIN)

# define EEPROM_I2C_READ()      GPIO_ReadInputDataBit(I2C_SDA_GPIO_PORT, I2C_SDA_GPIO_PIN)

//初始化i2c GPIO 函数
void i2c_GPIO_Config(void);

/*产生起始信号*/
void i2c_START(void);

/*产生结束信号*/
void i2c_STOP(void);

/*产生应答信号*/
void i2c_ASK(void);

/*产生非应答信号*/
void i2c_NASK(void);

/*等待应答信号 NASK:1  ASK:0*/
uint8_t i2c_WAIT_ASK(void);

/*写入一个字节*/
void i2c_WRITE_BYTE(uint8_t data);

/*读取一个字节*/
uint8_t i2c_READ_BYTE(void);

# endif
