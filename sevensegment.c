#include "sevensegment.h"
#include "delay.h"
/* array contains the drawing of every number as digital*/
unsigned char segment_arr[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
void sevensegment_write(unsigned int segment, unsigned char num){
    segment++;
    PORTA &= ~(1<<3);
    PORTA &= ~(1<<4);
    PORTA |= (1<<segment);
    PORTD = segment_arr[num];
}
