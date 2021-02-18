/* 
 * File:   adc.h
 * Author: M.Magdy
 *
 * Created on 06 ?????, 2019, 01:50 ?
 */

// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#ifndef ADC_H
#define ADC_H

#include "sys.h"

/**
 * @breif initialize ADC in microcontroller
 *  
 * this function takes no inputs and return
 * no outputs, initialize ADC to read analog values
 * 
 * @param no parameters
 * 
 * @return no return
 */
void ADC_Initialize(void);

/**
 * @breif reads ADC value from analog pins
 *  
 * this function takes the channel number return
 * the digital value of the analog physical value
 * 
 * @param channel number
 * 
 * @return digital value
 */
unsigned int ADC_Read(unsigned char channel);

#endif 
