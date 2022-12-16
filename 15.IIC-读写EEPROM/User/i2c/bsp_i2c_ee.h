# ifndef _BSP_I2C_EE_H
# define _BSP_I2C_EE_H

# include "stm32f10x.h"

# define EEPROM_READ_DIR   0x01
# define EEPROM_WRITE_DIR  0x00

# define EEPROM_ADDR       0xA0

/*检测EEPROM 是否存在*/
/*1 表示没有检测到EEPROM*/
/*0 表示检测到了EEPROM*/
uint8_t ee_CHECK_DEVICE(uint8_t addr);

/*往EEPROM 写入一个字节*/
/*正常：1  错误：0*/
uint8_t ee_WRITE_BYTE(uint8_t w_addr, uint8_t data);

/*从EEPROM读一个字节*/
/*正常：1  错误：0*/
uint8_t ee_READ_BYTE(uint8_t r_addr, uint8_t *data);

/*从EEPROM读多个个字节*/
/*正常：1  错误：0*/
uint8_t ee_READ_BYTES(uint8_t r_addr, uint8_t *data, uint16_t size);

/*往EEPROM 写入多个字节*/
/*正常：1  错误：0*/
uint8_t ee_WRITE_BYTES(uint8_t w_addr, uint8_t *data, uint16_t size);

# endif
