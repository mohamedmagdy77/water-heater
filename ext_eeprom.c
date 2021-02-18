#include "ext_eeprom.h"
#include "delay.h"

void ext_eeprom_write(unsigned char send, unsigned char address, unsigned int int_address){
    //unsigned int temp = int_address>>8;
    //MSdelay(100);
    i2c_start();
    i2c_send(address);
    i2c_send(int_address>>8);
    i2c_send((unsigned char)int_address);
    i2c_send(send);
    i2c_stop();
}

//------------------------------------------------------------------------------
unsigned char ext_eeprom_read(unsigned int address, unsigned int int_address){
    unsigned char _data;
    i2c_start();
    i2c_send(address);
    i2c_send(int_address);
    i2c_repeated_start();
    i2c_send(address+0x01);
    _data = i2c_receive(0);
    i2c_stop();
    return _data;
}