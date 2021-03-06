# -*-Makefile-*-
# Testing ALL sensors on Tmote platform
# NOTE: This is for testing the new sensing sub-system only.

PROJ = test_sensors_app
MODE = new_sensing_api
SB = tmote
ROOTDIR = ../..
INCDIR += -I$(ROOTDIR)/modules/sensordrivers/include

SUPPORTLIST = tmote

ifeq ($(SB), tmote)
# Testing Tmote Sky sensors
# Add necessary source files.
# Test PAR (Photo-active radiation) Light sensor
SRCS += par_sensor.c 
# Test TSR (Ambient) Light Sensor
SRCS += tsr_sensor.c
# Test SHT1x Temperature and Humidity sensor
SRCS += sht11.c
# Test Internal Temperature sensor
SRCS += temp_sensor.c
# Test Internal Voltage sensor
SRCS += volt_sensor.c
# Application module to pull sensor data
SRCS += test_sensor.c

# Paths
vpath test_sensor.c $(ROOTDIR)/modules/sensordrivers/tmote/sky/test/
vpath par_sensor.c $(ROOTDIR)/modules/sensordrivers/tmote/sky/par/
vpath tsr_sensor.c $(ROOTDIR)/modules/sensordrivers/tmote/sky/tsr/
vpath sht11.c $(ROOTDIR)/modules/sensordrivers/tmote/sky/sht1x/
vpath temp_sensor.c $(ROOTDIR)/modules/sensordrivers/tmote/sky/temp/
vpath volt_sensor.c $(ROOTDIR)/modules/sensordrivers/tmote/sky/volt/
endif

ifeq ($(SB), tmote_invent)
# Testing Tmote Sky sensors
# Add necessary source files.
# Test PAR (Photo-active radiation) Light sensor
SRCS += light_sensor.c
# Microphone
SRCS += mic_sensor.c
# Application module to pull sensor data
SRCS += test_sensor.c

# Paths
vpath test_sensor.c $(ROOTDIR)/modules/sensordrivers/tmote/invent/test/
vpath light_sensor.c $(ROOTDIR)/modules/sensordrivers/tmote/invent/light/
vpath mic_sensor.c $(ROOTDIR)/modules/sensordrivers/tmote/invent/mic/
endif

ifeq ($(SB), tmote_impact)
# Testing custom ADXL321 sensor board for Tmote Sky.
# Add necessary source files.
# Test ADXL321 Impact sensor board
SRCS += accel_sensor.c
# Application module to pull sensor data
SRCS += test_sensor.c
# Include directory for the ADXL321 sensor board
INCDIR += -I$(ROOTDIR)/modules/sensordrivers/tmote/sky/adxl321

# Paths
vpath test_sensor.c $(ROOTDIR)/modules/sensordrivers/tmote/sky/adxl321/test/
vpath accel_sensor.c $(ROOTDIR)/modules/sensordrivers/tmote/sky/adxl321/
endif

include $(ROOTDIR)/config/Makerules

clean2:
	rm -f *.o *.srec *.elf *.lst $(PROJ).map $(PROJ).exe $(PROJ).exe.out.* $(PROJ).od $(PROJ).srec.out.* .build.tmp
	rm -f $(PROJ).c Makefile

