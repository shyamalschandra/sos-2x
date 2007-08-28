/* -*- Mode: C; tab-width:2 -*- */
/* ex: set ts=2 shiftwidth=2 softtabstop=2 cindent: */

#include <sys_module.h>

#include <sensor.h>

//#define LED_DEBUG
#include <led_dbg.h>

#include <tmote_sensors.h>

typedef struct temp_sensor_state {
	uint8_t state;
} temp_sensor_state_t;


// function registered with kernel sensor component
static int8_t temp_sensor_control(func_cb_ptr cb, uint8_t cmd, void *data);
// data ready callback registered with adc driver
int8_t temp_sensor_data_ready_cb(func_cb_ptr cb, uint8_t port, uint16_t value, uint8_t flags);

static int8_t temp_sensor_msg_handler(void *state, Message *msg);

static const mod_header_t mod_header SOS_MODULE_HEADER = {
  mod_id : TEMP_SENSOR_PID,
  state_size : sizeof(temp_sensor_state_t),
  num_timers : 0,
  num_sub_func : 0,
  num_prov_func : 2,
	platform_type : HW_TYPE,
	processor_type : MCU_TYPE,
	code_id : ehtons(TEMP_SENSOR_PID),
  module_handler : temp_sensor_msg_handler,
	funct : {
		{temp_sensor_control, "cCw2", TEMP_SENSOR_PID, SENSOR_CONTROL_FID},
		{temp_sensor_data_ready_cb, "cCS3", TEMP_SENSOR_PID, SENSOR_DATA_READY_FID},
	},
};


/**
 * adc call back
 * not a one to one mapping so not SOS_CALL
 */
int8_t temp_sensor_data_ready_cb(func_cb_ptr cb, uint8_t port, uint16_t value, uint8_t flags) {

	// post data ready message here
	switch(port) {
		case TEMP_SID:
			sys_sensor_data_ready(TEMP_SID, value, flags);
			break;
		default:
			return -EINVAL;
	}
	return SOS_OK;
}


static int8_t temp_sensor_control(func_cb_ptr cb, uint8_t cmd, void* data) {\

	//uint8_t ctx = *(uint8_t*)data;
	
	switch (cmd) {
		case SENSOR_GET_DATA_CMD:
			// get ready to read accel sensor
			return sys_adc_proc_getData(TEMP_SID, 0);

		case SENSOR_ENABLE_CMD:
			break;

		case SENSOR_DISABLE_CMD:
			break;

		case SENSOR_CONFIG_CMD:
			// no configuation
			if (data != NULL) {
				sys_free(data);
			}
			break;

		default:
			return -EINVAL;
	}
	return SOS_OK;
}


int8_t temp_sensor_msg_handler(void *state, Message *msg)
{
	
	temp_sensor_state_t *s = (temp_sensor_state_t*)state;
  
	switch (msg->type) {

		case MSG_INIT:
			// bind adc channel and register callback pointer

		  sys_adc_proc_bindPort(TEMP_SID, TEMP_HW_CH, TEMP_SENSOR_PID,  SENSOR_DATA_READY_FID);
			// register with kernel sensor interface
			sys_sensor_register(TEMP_SENSOR_PID, TEMP_SID, SENSOR_CONTROL_FID, (void*)(&s->state));
			break;

		case MSG_FINAL:
			//  unregister ADC port
			sys_adc_proc_unbindPort(TEMP_SENSOR_PID, TEMP_SID);
			// unregister sensor
			sys_sensor_deregister(TEMP_SENSOR_PID, TEMP_SID);
			break;

		default:
			return -EINVAL;
			break;
	}
	return SOS_OK;
}


#ifndef _MODULE_
mod_header_ptr temp_sensor_get_header() {
	return sos_get_header_address(mod_header);
}
#endif

