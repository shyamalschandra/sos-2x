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
 
#ifndef _ADC_PROC_H
#define _ADC_PROC_H

/**
 * @brief ADC functions
 */
typedef void (*adc_callback_t)(uint16_t data); /*!< the callback functions used when data is ready */

/**
 * @brief init function for ADC
 */
void adc_proc_init();

/**
 * @brief bind port with callback
 * The port will be used in ker_adc_proc_getData and ker_adc_proc_getContinuousData
 */
extern int8_t ker_adc_proc_bindPort(uint8_t port, uint8_t adcPort, sos_pid_t driverpid);

/**
 * @brief Get ADC data
 * @param uint8_t port Logical ADC port
 * @return int8_t SOS_OK if valid port and available; -EBUSY if port is busy; -EINVAL for invalid port
 */
extern int8_t ker_adc_proc_getData(uint8_t port);

/**
 * @brief Get Calibrated ADC data
 * @param uint8_t port Logical ADC port
 * @return int8_t SOS_OK if valid port and available; -EBUSY if port is busy; -EINVAL for invalid port
 */
extern int8_t ker_adc_proc_getCalData(uint8_t port);

/**
 * @brief Get continuous ADC data
 * @param uint8_t port Logical ADC port
 * @return int8_t SOS_OK if valid port and available; -EBUSY if port is busy; -EINVAL for invalid port
 */
extern int8_t ker_adc_proc_getContinuousData(uint8_t port);

/**
 * @brief Get Continuous Calibrated ADC data
 * @param uint8_t port Logical ADC port
 * @return int8_t SOS_OK if valid port and available; -EBUSY if port is busy; -EINVAL for invalid port
 */
extern int8_t ker_adc_proc_getCalContinuousData(uint8_t port);

#endif // _ADC_PROC_H
