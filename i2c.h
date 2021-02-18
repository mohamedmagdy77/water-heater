/* 
 * File:   i2c.h
 * Author: M.Magdy
 *
 * Created on 16 ?????, 2019, 10:44 ?
 */

#ifndef I2C_H
#define I2C_H

#include "sys.h"
#include <pic16f877a.h>

/**
 * @breif initialize i2c in microcontroller
 *  
 * this function takes rate of i2c speed and return
 * no outputs
 * 
 * @param rate of i2c speed
 * 
 * @return no return
 */
void i2c_init_master(unsigned long int rate);

/**
 * @breif send start bit to start communication
 *  
 * this function takes no inputs and return
 * no outputs, starts serial communication with
 * other i2c devices
 * 
 * @param no parameters
 * 
 * @return no return
 */
void i2c_start(void);

/**
 * @breif send byte via i2c
 *  
 * this function takes byte to write via i2c
 * to send it and return no outputs
 * 
 * @param byte to be send
 * 
 * @return no return
 */
void i2c_send(unsigned char write);

/**
 * @breif stops i2c communication
 *  
 * this function takes no inputs and return
 * no outputs, it send stop bit via i2c to
 * end serial communication
 * 
 * @param no parameters
 * 
 * @return no return
 */
void i2c_stop(void);

/**
 * @breif resend start bit
 *  
 * this function takes no inputs and return
 * no outputs, send start bit again before 
 * sending stop bit
 * 
 * @param no parameters
 * 
 * @return no return
 */
void i2c_repeated_start(void);

/**
 * @breif ensures of sending signals
 *  
 * this function takes no inputs and returns
 * no outputs, ensures that start bit, stop bit
 * and data has been sent correctly
 * 
 * @param no parameters
 * 
 * @return no return
 */
void mssp_idle(void);

/**
 * @breif ensures the bus is idle
 *  
 * this function takes no inputs and returns
 * no outputs, ensures that no start bit, no stop bit
 * and no data is being send currently
 * 
 * @param no parameters
 * 
 * @return no return
 */
void i2c_idle(void);

/**
 * @breif receive byte via i2c bus
 *  
 * this function takes Acknowledge or NotAcknowledge  
 * as input and returns the received byte, akn if data is 
 * received or nakn if not
 * 
 * @param Acknowledge or NotAcknowledge
 * 
 * @return the received byte
 */
unsigned char i2c_receive(char _compare);

/**
 * @breif sends Acknowledge signal
 *  
 * this function takes no inputs and returns
 * no outputs, send akn signal after receiving data
 * 
 * @param no parameters
 * 
 * @return no return
 */
void i2c_akn(void);

/**
 * @breif sends NotAcknowledge signal
 *  
 * this function takes no inputs and returns
 * no outputs, send nakn signal after fail in receiving data
 * 
 * @param no parameters
 * 
 * @return no return
 */
void i2c_nakn(void);

#endif