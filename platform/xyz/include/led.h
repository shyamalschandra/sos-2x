/* ex: set ts=4: */
/*
 * Copyright (c) 2005 Yale University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgement:
 *       This product includes software developed by the Embedded Networks
 *       and Applications Lab (ENALAB) at Yale University.
 * 4. Neither the name of the University nor that of the Laboratory
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY YALE UNIVERSITY AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

/**
 * @brief    Header file for LED module
 * @author   Andrew Barton-Sweeney (abs@cs.yale.edu)
 */

#ifndef _LED_H
#define _LED_H

#define LED_RED_ON           1
#define LED_GREEN_ON         2
#define LED_YELLOW_ON        3
#define LED_RED_OFF          4
#define LED_GREEN_OFF        5
#define LED_YELLOW_OFF       6
#define LED_RED_TOGGLE       7
#define LED_GREEN_TOGGLE     8
#define LED_YELLOW_TOGGLE    9



/**
 * @brief led functions
 */
#ifndef DISABLE_LEDS
#define led_red_on()        put_hvalue(GPPOD, get_hvalue(GPPOD) & ~0x20)
#define led_green_on()      put_hvalue(GPPOD, get_hvalue(GPPOD) & ~(0x20 << 2))
#define led_yellow_on()     put_hvalue(GPPOD, get_hvalue(GPPOD) & ~(0x20 << 1))
#define led_red_off()       put_hvalue(GPPOD, get_hvalue(GPPOD) | 0x20)
#define led_green_off()     put_hvalue(GPPOD, get_hvalue(GPPOD) | (0x20 << 2))
#define led_yellow_off()    put_hvalue(GPPOD, get_hvalue(GPPOD) | (0x20 << 1))
#define led_red_toggle()    put_hvalue(GPPOD, get_hvalue(GPPOD) ^ 0x20)
#define led_green_toggle()  put_hvalue(GPPOD, get_hvalue(GPPOD) ^ (0x20 << 2))
#define led_yellow_toggle() put_hvalue(GPPOD, get_hvalue(GPPOD) ^ (0x20 << 1))
#define led_init() \
		do{ \
    		put_hvalue(GPPMD, get_hvalue(GPPMD) | 0x00E0); \
    		led_green_off(); \
    		led_red_off(); \
    		led_yellow_off(); \
    	}while(0)

#define led_display(x) \
        do{ \
        	uint8_t _led_display; \
         	_led_display = x; \
         	if (_led_display & 0x01)\
           		led_yellow_on(); \
         	else \
           		led_yellow_off(); \
         	_led_display >>= 1; \
         	if (_led_display & 0x01)\
           		led_green_on(); \
         	else \
           		led_green_off(); \
         	_led_display >>= 1; \
         	if (_led_display & 0x01)\
           		led_red_on(); \
         	else \
           		led_red_off(); \
        }while(0)

#else
#define led_red_on()
#define led_green_on()
#define led_yellow_on()
#define led_red_off()
#define led_green_off()
#define led_yellow_off()
#define led_red_toggle()
#define led_green_toggle()
#define led_yellow_toggle()
#define led_init()     {  DDRA |= 0x7; }
#define led_display(x)
#endif

/**
 * kernel writer can just use macros provided by SOS
 *
 * led_red_on()
 * led_green_on()
 * led_yellow_on()
 * led_red_off()
 * led_green_off()
 * led_yellow_off()
 * led_red_toggle()
 * led_green_toggle()
 * led_yellow_toggle()
 */
#ifndef _MODULE_

#include <sos.h>
extern int8_t ker_led(uint8_t action);

#endif /* _MODULE_ */
#endif
