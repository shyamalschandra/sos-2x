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

#ifndef _MODULE_PROC_H
#define _MODULE_PROC_H

#include <kertable_proc.h>

#ifdef _MODULE_

/**
 * @brief ADC Bind Port
 **/
typedef int8_t (*adc_bindPort_func_t)(uint8_t port, uint8_t adcPort, uint8_t driverpid);
static inline int8_t ker_adc_proc_bindPort(uint8_t port, uint8_t adcPort, uint8_t driverpid)
{
	adc_bindPort_func_t func = (adc_bindPort_func_t)get_kertable_entry(SYS_KERTABLE_END+1);
	return func(port, adcPort, driverpid);
}

typedef int8_t (*adc_getData_func_t)(uint8_t port);
static inline int8_t ker_adc_proc_getData(uint8_t port)
{
	adc_getData_func_t func = (adc_getData_func_t)get_kertable_entry(SYS_KERTABLE_END+2);
	return func(port);
}

/**
 * Get continuous data from ADC
 */
static inline int8_t ker_adc_proc_getContinuousData(uint8_t port)
{
	adc_getData_func_t func = (adc_getData_func_t)get_kertable_entry(SYS_KERTABLE_END+3);
	return func(port);
}

/**
 * Get Calibrated ADC data
 */
static inline int8_t ker_adc_proc_getCalData(uint8_t port)
{
	adc_getData_func_t func = (adc_getData_func_t)get_kertable_entry(SYS_KERTABLE_END+4);
	return func(port);
}

/**
 * Get Continuous Calibrated ADC data
 */
static inline int8_t ker_adc_proc_getCalContinuousData(uint8_t port)
{
	adc_getData_func_t func = (adc_getData_func_t)get_kertable_entry(SYS_KERTABLE_END+5);
	return func(port);
}

/**
 **/
typedef int8_t (*i2c_reserve_bus_func_t)(uint8_t calling_mod_id, uint8_t ownAddress, uint8_t flags);
static inline int8_t ker_i2c_reserve_bus(uint8_t calling_mod_id, uint8_t ownAddress, uint8_t flags) {
	i2c_reserve_bus_func_t func =
		(i2c_reserve_bus_func_t)get_kertable_entry(SYS_KERTABLE_END+6);
	return func(calling_mod_id, ownAddress, flags);
}

/**
 **/
typedef int8_t (*i2c_release_bus_func_t)(uint8_t calling_mod_id);
static inline int8_t ker_i2c_release_bus(uint8_t calling_mod_id)
{
	i2c_release_bus_func_t func =
		(i2c_release_bus_func_t)get_kertable_entry(SYS_KERTABLE_END+7);
	return func(calling_mod_id);
}

/**
 * @brief I2C send data function.
 * @param msg Pointer to the data to send
 * @param msg_size Length of data to send
 **/
typedef int8_t (*i2c_send_data_func_t)(
		uint8_t i2c_addr,
		 uint8_t *msg,
		 uint8_t msg_size,
		 uint8_t calling_id);
static inline int8_t ker_i2c_send_data(
		uint8_t i2c_addr,
		uint8_t *msg,
		uint8_t msg_size,
		uint8_t calling_id)
{
	i2c_send_data_func_t func = (i2c_send_data_func_t)get_kertable_entry(SYS_KERTABLE_END+8);
	return func(i2c_addr, msg, msg_size, calling_id);
}

/**
 * @brief I2C read data function. Split phase call. Reply is MSG_I2C_READ_DONE
 * @param msg_size Length of data to read
 **/
typedef int8_t (*i2c_read_data_func_t)(
		uint8_t i2c_addr,
		uint8_t msg_size,
		uint8_t calling_id);
static inline int8_t ker_i2c_read_data(
		uint8_t i2c_addr,
		uint8_t msg_size,
		uint8_t calling_id)
{
	i2c_read_data_func_t func = (i2c_read_data_func_t)get_kertable_entry(SYS_KERTABLE_END+9);
	return func(i2c_addr, msg_size, calling_id);
}

/**
 **/
typedef int8_t (*uart_reserve_bus_func_t)(uint8_t calling_mod_id, uint8_t flags);
static inline int8_t ker_uart_reserve_bus(uint8_t calling_mod_id, uint8_t flags) {
	uart_reserve_bus_func_t func =
		(uart_reserve_bus_func_t)get_kertable_entry(SYS_KERTABLE_END+10);
	return func(calling_mod_id, flags);
}

/**
 **/
typedef int8_t (*uart_release_bus_func_t)(uint8_t calling_mod_id);
static inline int8_t ker_uart_release_bus(uint8_t calling_mod_id)
{
	uart_release_bus_func_t func =
		(uart_release_bus_func_t)get_kertable_entry(SYS_KERTABLE_END+11);
	return func(calling_mod_id);
}

/**
 * @brief msg send data function.
 * @param msg Pointer to the data to send ((uint8_t*)msg or buff)
 * @param msg_size Length of data to send (msg->len of buff_len)
 **/
typedef int8_t (*uart_send_data_func_t)(
		 uint8_t *buff,
		 uint8_t msg_size,
		 uint8_t calling_id);
static inline int8_t ker_uart_send_data(
		uint8_t *buff,
		uint8_t msg_size,
		uint8_t calling_id)
{
	uart_send_data_func_t func = (uart_send_data_func_t)get_kertable_entry(SYS_KERTABLE_END+12);
	return func(buff, msg_size, calling_id);
}

/**
 * @brief uart read data function. Split phase call. Reply is MSG_UART_READ_DONE
 * @param msg_size length of data to read (msg->len or buff_len)
 **/
typedef int8_t (*uart_read_data_func_t)(
		uint8_t msg_size,
		uint8_t calling_id);
static inline int8_t ker_uart_read_data(
		uint8_t msg_size,
		uint8_t calling_id)
{
	uart_read_data_func_t func = (uart_read_data_func_t)get_kertable_entry(SYS_KERTABLE_END+13);
	return func(msg_size, calling_id);
}

/**
 * @brief Exception handler in the case of a memory access fault
 * @note Currently supported only for the AVR processor
 */
typedef void (*ker_memmap_perms_check_func_t)(void* x);
static inline void ker_memmap_perms_check(void* x)
{
  ker_memmap_perms_check_func_t func =
    (ker_memmap_perms_check_func_t)get_kertable_entry(SYS_KERTABLE_END+14);
  func(x);
  return;
}


#endif /* ifdef _MODULE_ */
#endif /* ifdef _MODULE_PROC_H */
