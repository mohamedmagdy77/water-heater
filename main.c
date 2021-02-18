/*
 * File:   main.c
 * Author: M.Magdy
 *
 * Created on June 30, 2020, 5:05 PM
 */
#include <pic16f877a.h>
#include "sevensegment.h"
#include "delay.h"
#include "ext_eeprom.h"
#include "adc.h"

/**
 * temp: contains the measured temperature
 * seg_arr: the set temperature to be displayed on 7segment
 * count: counts the number of 10ms
 * pin: the selected 7segment
 * set_temp: the set temperature
 * countsec: counts the time in seconds
 * no_off: the state of on_off button
 * logic: to blink the 7segment on set mode
 * pass100ms: if its one then measure the temperature
 * count100: counts the number of 100 ms passed to measure temperature
 * current_temp: the current water temperature to be displayed on 7segment
 */
unsigned int temp;
unsigned int seg_arr[2] = {6, 0}, count = 0, pin=3, set_temp = 60, countsec = 0;
unsigned char on_off=1, logic=0, pass100ms=0;
unsigned int count100=0, current_temp[2];
unsigned char avg_temp_arr[10]={0};
unsigned int avg_temp=0;

/**
 * @breif interrupt service routine
 *  
 * this function is executed when an interrupt occurs 
 * 
 * @param no parameters
 * 
 * @return no return
 */
void __interrupt() Timer1_ISR(){
    if((INTCON&(1<<2)) == 4){       //timer 0 interrupt
        pin==2 ? (pin=3) : (pin=2); // switch between 7segments every 10 ms
        count++;
        count100++;
        TMR0 = 177;                 // reload value for timer 0
        if(count == 100){
            count = 0;              // count 10 ms
            countsec++;             // count seconds
            if((PORTC&(1<<5)) == 32){PORTB ^= (1<<3);}  // heating element led blinking
            logic ^= (1<<0);        // flip logic value
        }
        if(count100 == 100){
            count100 = 0;           // restart counting
            pass100ms = 1;          // means that 100 ms passed
        }
        INTCON &= ~(1<<2);          // clear timer0 flag
    }
    if((INTCON&(1<<1)) == 2){       // INT0E interrupt
        on_off ^= (1<<0);           // flip on_off value
        INTCON &= ~(1<<1);          //clear INT0 flag
    }
}

/**
 * @breif initializes timer0
 *  
 * this function initializes timer0 as a timer
 * that ticks every 10 milli seconds to keep 
 * track of time
 * 
 * @param no parameters
 * 
 * @return no return
 */
void init_timer0(void);

//------------------------------------------------------------------------------
void main1(void) {
    unsigned char i=0;
    i2c_init_master(100000);// initialize i2c communication
    ADC_Initialize();       // initialize ADC module
    init_timer0();          // initialize timer0 to tick every 10 milli s
    INTCON |= (1<<4);       // enable INT0E
    OPTION_REG |= (1<<6);   // INT0E interrupt on rising edge
    TRISD = 0;              // seven segment port as output
    TRISA &= ~(1<<3);       // seven segment number 3 pin
    TRISA &= ~(1<<4);       // seven segment number 4 pin
    TRISB |= (1<<1);        // UP button as input
    TRISB |= (1<<2);        // DOWN button as input
    TRISB &= ~(1<<3);       // heating element led as output
    TRISC &= ~(1<<1);       // 
    TRISC &= ~(1<<2);       // cooler as output
    TRISC &= ~(1<<5);       // heater as output
    TRISA &= ~(1<<5);       // heating element led as output
    PORTA &= ~(1<<5);       // heating element led off
    //INTCON &= ~(1<<5);
    //ext_eeprom_write(temp, 0xA0, 0x00);
    MSdelay(100);
    //unsigned char data1 = ext_eeprom_read(0xA0, 0x00);
    //INTCON |= (1<<5);
    while(1){
        while(on_off == 0){
            if(((PORTB&2)==0) || ((PORTB&4)==0)){           // UP or DoWN pressed
                while(((PORTB&2)==0) || ((PORTB&4)==0)){}   // wait till released
                countsec = 0;       // restart countsec
                count = 0;          // restart count 
                while(countsec<5){  // execute for five seconds
                    if(logic == 0){ // blink 7segments every 1 second
                        sevensegment_write(pin, seg_arr[pin-2]);    // display set temperature
                    }
                    else{           // blink 7segments every 1 second
                        PORTD = 0;
                    }
                    if((PORTB&(1<<1)) != 2){        // UP button pressed
                        while((PORTB&(1<<1)) != 2){}
                        set_temp+=5;
                        if(set_temp>75){set_temp=75;}
                        countsec = 0;
                        count = 0;
                        seg_arr[0] = set_temp/10;
                        seg_arr[1] = set_temp%10;
                    }
                    else if((PORTB&(1<<2)) != 4){   // DOWN button pressed
                        while((PORTB&(1<<2)) != 4){}
                        set_temp-=5;
                        if(set_temp<35){set_temp=35;}
                        countsec = 0;
                        count = 0;
                        seg_arr[0] = set_temp/10;
                        seg_arr[1] = set_temp%10;
                    }
                }
                /*ext_eeprom_write(seg_arr[0], 0xA0, 0x00);
                MSdelay(10);
                ext_eeprom_write(seg_arr[1], 0xA0, 0x01);
                MSdelay(10);*/
            }
            if(pass100ms == 1){     // every 100 ms
                pass100ms = 0;
                temp = ADC_Read(2);
                temp = (temp*500/1023);
                //avg_temp_arr[i++] = temp;
                //if(i==10){i=0;}
                current_temp[0] = temp/10;
                current_temp[1] = temp%10;
                if(temp < (set_temp-4)){        // water temperature is low
                    PORTC |= (1<<5);
                    PORTC &= ~(1<<2);
                }
                else if(temp > (set_temp+4)){  // water temperature is high 
                    PORTC |= (1<<2);
                    PORTC &= ~(1<<5);
                    PORTB |= (1<<3);
                }
                else if (temp == set_temp){               // reaching set temperature
                    PORTC &= ~(1<<2);
                    PORTC &= ~(1<<5);
                    PORTB &= ~(1<<3);
                }
            }
            
            sevensegment_write(pin, current_temp[pin-2]); // display current temperature
        }
        if(on_off == 1){    // on_off button state
            PORTD = 0;      // turn off 7segments   
            PORTC &= ~(1<<2);
            PORTC &= ~(1<<5);
            while(on_off == 1){}    // wait till pressed again
        }
        
    }
}
void main(void){
    i2c_init_master(100000);// initialize i2c communication
    //ADC_Initialize();       // initialize ADC module
    //init_timer0(); 
    TRISB &= ~(1<<3);
    TRISB=0x03;
    while(1){
        ext_eeprom_write(0x66, 0xA0, 0x00);
        MSdelay(1000);
        PORTB ^= (1<<3);
    }
}

//------------------------------------------------------------------------------
void init_timer0(void){
    OPTION_REG = 0x07;   //1:128     
    TMR0 = 177;          //for 10 ms
    INTCON = 0xe0;       // enable interrupts
}