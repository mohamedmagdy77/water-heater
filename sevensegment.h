/* 
 * File:   sevensegment.h
 * Author: M.Magdy
 *
 * Created on June 30, 2020, 5:13 PM
 */

#ifndef SEVENSEGMENT_H
#define	SEVENSEGMENT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "sys.h"
#include <pic16f877a.h>
    
/**
 * @breif write symbols to dynamic seven segments
 *  
 * this function takes two inputs the 7segment order and
 * the number to be displayed, displays this number on 
 * the choose 7segment
 * 
 * @param 7segment order and number
 * 
 * @return no return
 */
void sevensegment_write(unsigned int segment, unsigned char num);

#ifdef	__cplusplus
}
#endif

#endif	/* SEVENSEGMENT_H */

