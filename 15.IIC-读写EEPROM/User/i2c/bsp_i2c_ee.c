# include "./i2c/bsp_i2c_ee.h"
# include "./i2c/bsp_i2c_gpio.h"

/*检测EEPROM 是否存在*/
/*1 表示没有检测到EEPROM*/
/*0 表示检测到了EEPROM*/
uint8_t ee_CHECK_DEVICE(uint8_t addr){


    uint8_t reply;
    i2c_START();

    /*发送EEPROM 设备地址*/
    i2c_WRITE_BYTE(addr);

    if (i2c_WAIT_ASK()){
        reply = 1;
    }
    else {
        reply = 0;
    }

    i2c_NASK();
		
    i2c_STOP();
    return reply;
}

/*等待函数*/
/*1 表示超时*/
/*0 表示完成*/
uint8_t ee_WAIT_STANDPY(void){

    uint16_t cycle = 0;
    
    while(ee_CHECK_DEVICE(EEPROM_ADDR | EEPROM_WRITE_DIR)){
        
        cycle ++;
        if (cycle >= 10000) return 1;
    }

    return 0;
}

/*往EEPROM 写入一个字节*/
/*正常：1  错误：0*/
uint8_t ee_WRITE_BYTE(uint8_t w_addr, uint8_t data){

    if (ee_WAIT_STANDPY()){
        goto w_fail;
    }

    i2c_START();

    /*发送EEPROM 设备地址*/
    i2c_WRITE_BYTE(EEPROM_ADDR | EEPROM_WRITE_DIR);

    if (i2c_WAIT_ASK()){
        goto w_fail;
    }
    else {

        /*发送要写入的存储单元格地址*/
        i2c_WRITE_BYTE(w_addr);
        if (i2c_WAIT_ASK()){
					goto w_fail;
					
        }
        else{

            /*发送要写入的数据*/
            i2c_WRITE_BYTE(data);
        }
        if (i2c_WAIT_ASK()){
					goto w_fail;
        }
        else {}
    }
    
    i2c_STOP();
    return 1;

    w_fail:
    i2c_STOP();
    return 0;
}

/*从EEPROM读一个字节*/
/*正常：1  错误：0*/
uint8_t ee_READ_BYTE(uint8_t r_addr, uint8_t *data){

    if (ee_WAIT_STANDPY()){
        goto r_fail;
    }

    i2c_START();

    /*发送EEPROM 设备地址*/
    i2c_WRITE_BYTE(EEPROM_ADDR | EEPROM_WRITE_DIR);

    if (i2c_WAIT_ASK()){
        goto r_fail;
    }
    else {

        /*发送要读取的存储单元格地址*/
        i2c_WRITE_BYTE(r_addr);
        if (i2c_WAIT_ASK()){
				goto r_fail;		
        }
        else{

            i2c_START();
            /*发送第二次设备地址 读方向*/
            i2c_WRITE_BYTE(EEPROM_ADDR | EEPROM_READ_DIR);
             if (i2c_WAIT_ASK()){
				goto r_fail;
            }
             else {
                *data = i2c_READ_BYTE();
            }
        }
    }
    
    i2c_NASK();
    i2c_STOP();
    return 1;

    r_fail:
    i2c_NASK();
    i2c_STOP();
    return 0;
}

/*从EEPROM读多个个字节*/
/*正常：1  错误：0*/
uint8_t ee_READ_BYTES(uint8_t r_addr, uint8_t *data, uint8_t size){

    if (ee_WAIT_STANDPY()){
        goto r_fail;
    }

    i2c_START();

    /*发送EEPROM 设备地址*/
    i2c_WRITE_BYTE(EEPROM_ADDR | EEPROM_WRITE_DIR);

    if (i2c_WAIT_ASK()){
        goto r_fail;
    }
    else {

        /*发送要读取的存储单元格地址*/
        i2c_WRITE_BYTE(r_addr);
        if (i2c_WAIT_ASK()){
				goto r_fail;		
        }
        else{

            i2c_START();
            /*发送第二次设备地址 读方向*/
            i2c_WRITE_BYTE(EEPROM_ADDR | EEPROM_READ_DIR);
             if (i2c_WAIT_ASK()){
				goto r_fail;
            }
             else {
                uint8_t i;

               for (i = 0; i < size; i ++){

                 *data = i2c_READ_BYTE();

                 if (i == size - 1){
                    i2c_NASK(); //接收数据够了产生非应答
                 }
                 else {
                    i2c_ASK();
                 }

                 data ++;   //指向下一个数据
               }
            }
        }
    }
    
    i2c_NASK();
    i2c_STOP();
    return 1;

    r_fail:
    i2c_NASK();
    i2c_STOP();
    return 0;
}
