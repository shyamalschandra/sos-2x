/* -*- Mode: C; tab-width:4 -*- */
/* ex: set ts=4 shiftwidth=4 softtabstop=4 cindent: */
/*
 * Copyright (c) 2003 The Regents of the University of California.
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
 *       This product includes software developed by Networked &
 *       Embedded Systems Lab at UCLA
 * 4. Neither the name of the University nor that of the Laboratory
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS''
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
 * @brief  SOS booting sequence
 * @author Simon Han (simonhan@ee.ucla.edu)
 *
 * Platform dependent booting sequence should go to 
 * hardware.c or hardware_*.c of particular platform
 */
#include <hardware.h>
#include <sos_sched.h>
#include <message_queue.h>
#include <sos_module_fetcher.h>
#include <random.h>
#include <sensor.h>

#ifdef NEW_SENSING_API
#include <sensor_kernel.h>
#endif

#include <malloc.h>
#include <monitor.h>
#include <fntable.h>
#include <sos_info.h>
#include <sos_shm.h>
#include <message.h>
#ifdef SOS_USE_PREEMPTION
#include <priority.h>
#endif
//#include <version_sync.h>

#ifdef SOS_SFI
#include <sfi_jumptable.h>
#endif


/**
 * @brief application start
 * 
 * Application will define this function
 */
extern void sos_start();


/**
 * @file     SOS core loop
 * @brief    main function 
 * @author   Simon Han (simonhan@ee.ucla.edu)
 */

/** 
 * @brief Core event loop
 */
int sos_main(uint8_t cond){

	//! disable interrupt
	DISABLE_GLOBAL_INTERRUPTS();
	
	//! Initialize the ID
	id_init();

    //! initialize memory manager
    mem_init();

	shm_init();

	//! initialize message pool
	msg_queue_init();

	//! initialize random number generator
	random_init();

    //! initialize scheduler
    sched_init(cond);

	//! initialize sensor manager
#ifdef NEW_SENSING_API
	sensor_system_init();
#else
	sensor_init();
#endif

	//! initialize the Function Table
	fntable_init();

	//! Initialize the monitor
	monitor_init();

    //! initialize hardware
    hardware_init();

	codemem_init();

	routing_init();

	//! starting memory module
	mem_start();

#ifdef SOS_SFI
	//! Initialize SFI
	sfi_modtable_init();
#endif

	//! Initialize the code fetcher
	fetcher_init();

    //! enable interrupt
	ENABLE_GLOBAL_INTERRUPTS();

#ifdef SOS_USE_PREEMPTION
	// Enable preemption
	MAIN_ENABLE_PREEMPTION();
#endif
	DEBUG("SOS booted\n");
    //! start application
    sos_start();

    //! enter main sched loop
    //! should never return from this call
	sched();
    return 0;
}

