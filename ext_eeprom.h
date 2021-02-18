/* 
 * File:   ext_eeprom.h
 * Author: M.Magdy
 *
 * Created on July 1, 2020, 3:37 PM
 */

#ifndef EXT_EEPROM_H
#define	EXT_EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#include "sys.h"
#include "pic16f877a.h"
#include "i2c.h"

/**
 * @breif write data to external i2c EEPROM
 *  
 * this function takes three inputs the data to be send,
 * the address of EEPROM device and internal address to 
 * write data in and returns no outputs
 * 
 * @param data, address for EEPROM and intrnal address
 * 
 * @return no return
 */
void ext_eeprom_write(unsigned char send, unsigned char address, unsigned int int_address);

/**
 * @breif reads data from external i2c EEPROM
 *  
 * this function takes two inputs
 * the address of EEPROM device (bit0 = 0) and internal address to 
 * read data from and returns the available data
 * 
 * @param address for EEPROM and internal address
 * 
 * @return available data
 */
unsigned char ext_eeprom_read(unsigned int address, unsigned int int_address);


#ifdef	__cplusplus
}
#endif

#endif	/* EXT_EEPROM_H */

