# ifndef _BSP_I2C_EE_H
# define _BSP_I2C_EE_H

# include "stm32f10x.h"

# define EEPROM_READ_DIR   0x01
# define EEPROM_WRITE_DIR  0x00

# define EEPROM_ADDR       0xA0

/*���EEPROM �Ƿ����*/
/*1 ��ʾû�м�⵽EEPROM*/
/*0 ��ʾ��⵽��EEPROM*/
uint8_t ee_CHECK_DEVICE(uint8_t addr);

/*��EEPROM д��һ���ֽ�*/
/*������1  ����0*/
uint8_t ee_WRITE_BYTE(uint8_t w_addr, uint8_t data);

/*��EEPROM��һ���ֽ�*/
/*������1  ����0*/
uint8_t ee_READ_BYTE(uint8_t r_addr, uint8_t *data);

/*��EEPROM��������ֽ�*/
/*������1  ����0*/
uint8_t ee_READ_BYTES(uint8_t r_addr, uint8_t *data, uint16_t size);

/*��EEPROM д�����ֽ�*/
/*������1  ����0*/
uint8_t ee_WRITE_BYTES(uint8_t w_addr, uint8_t *data, uint16_t size);

# endif
