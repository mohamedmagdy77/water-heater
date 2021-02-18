/* 
 * File:   adc.c
 * Author: futurecomp
 *
 * Created on 06 ?????, 2019, 01:51 ?
 */


#include <pic16f877a.h>
#include "delay.h"
#include "adc.h"


//------------------------------------------------------------------------------
void ADC_Initialize(void)
{
    ADCON0 = 0b01000001; //ADC ON and Fosc/16 is selected
    ADCON1 = 0b11000000; // Internal reference voltage is selected
}

//------------------------------------------------------------------------------
unsigned int ADC_Read(unsigned char channel)
{
    ADCON0 &= 0x11000101; //Clearing the Channel Selection Bits
    ADCON0 |= channel<<3; //Setting the required Bits
    MSdelay(2); //Acquisition time to charge hold capacitor
    GO_nDONE = 1; //Initializes A/D Conversion
    while(GO_nDONE); //Wait for A/D Conversion to complete
    return ((ADRESH<<8)+ADRESL); //Returns Result
}