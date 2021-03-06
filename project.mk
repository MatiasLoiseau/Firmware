################################################################################
#                            DO NOT EDIT THIS FILE!                            #
#           Copy project.mk.template to project.mk and use project.mk.         #
################################################################################
# Copyright 2016, Pablo Ridolfi
# Copyright 2017, Eric Pernia
# All rights reserved.
#
# This file is part of Workspace.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from this
#    software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

#-------------------------------------------------------------------------------
# current project
#-------------------------------------------------------------------------------

#projects

#MyProjects bare-metal
#PROJECT = projects/clean_code
#PROJECT = projects/semaforoMEF
#PROJECT = projects/keypad4x4
#PROJECT = projects/display7seg4digit
#PROJECT = projects/servoExample
#PROJECT = projects/esp8266_uart_bridge
#PROJECT = projects/test_tick
#PROJECT = projects/processing_uart
#PROJECT = projects/estados_leds_uart
#PROJECT = projects/ejemplo_boton_externo
#PROJECT = projects/entero_a_string
#PROJECT = projects/mef_botones
#PROJECT = projects/buffer_circular
#PROJECT = projects/bufferFIFO_reloj_uart
#PROJECT = projects/ejemplo_rtc
#PROJECT = projects/uart_receive_string
#PROJECT = projects/uart_receive_string_blocking
#PROJECT = projects/adc_plot
#PROJECT = projects/adc_plot_microfono
PROJECT = projects/gps_test


#OSEK
#Various projects
#PROJECT = projects/OSEK/mi_nuevo_proyecto
#PROJECT = projects/OSEK/gpio_blinky
#PROJECT = projects/OSEK/pruebas_task

#My projects CAPSE
#PROJECT = projects/OSEK/ej4osek_carlos
#PROJECT = projects/OSEK/ejercicio14_osek
#PROJECT = projects/OSEK/ejercicio18_osek
#PROJECT = projects/OSEK/ejercicio20_osek
#PROJECT = projects/OSEK/ejercicio21_osek
#PROJECT = projects/OSEK/ejercicio22_osek
#PROJECT = projects/OSEK/ejercicio28_osek
#PROJECT = projects/OSEK/matias_problema_isr
#PROJECT = projects/OSEK/isr_gpio_osek

#PROJECT = projects/OSEK/matias_examen

#Examples and exercises in class in CAPSE OSEK
#PROJECT = projects/OSEK/c8_ejercicio_8_osek_v3
#PROJECT = projects/OSEK/c10_ej23_delay_osek
#PROJECT = projects/OSEK/c12_ej25_mauricio_mod
#PROJECT = projects/OSEK/c13_freeOSEK_isr1
#PROJECT = projects/OSEK/c13_freeOSEK_isr1_propio_generador
#PROJECT = projects/OSEK/c14_ej25_mauricio_mod_isr
#PROJECT = projects/OSEK/c14_ej32_mauricio_mod_ColaCircular
#PROJECT = projects/OSEK/Ej30_FreeOSEK_4antireboteIRQ
#PROJECT = projects/OSEK/Ej30B_FreeOSEK_4antireboteIRQ
#PROJECT = projects/OSEK/c15_ej37_appmodes
#PROJECT = projects/OSEK/c15_ej39_mauricio_mod

#A la compilacion el target 
#ANOTACION IMPORTANTE MULTICORE--> Los targets: start_m0 = m4 ......... m0 = m0
#Tambien acordarse de fijarse de cambiar
# el etc/ld/lpc4337_m4_mem y etc/ld/lpc4337
#------------ MULTICORE examples -------------------------------

#PROJECT = examples/multicore/blinky/m0
#PROJECT = examples/multicore/blinky/start_m0
#PROJECT = examples/multicore/freeRTOS_blinky/m0
#PROJECT = examples/multicore/freeRTOS_blinky/start_m0
#PROJECT = examples/multicore/freeRTOS_fir/m0
#PROJECT = examples/multicore/freeRTOS_fir/start_m0
#PROJECT = examples/multicore/freeRTOS_led_toggle/m0
#PROJECT = examples/multicore/freeRTOS_led_toggle/start_m0
#PROJECT = examples/multicore/freeRTOS_msg_ipc/m0
#PROJECT = examples/multicore/freeRTOS_msg_ipc/start_m0
#PROJECT = examples/multicore/freeRTOS_static/m0
#PROJECT = examples/multicore/freeRTOS_static/start_m0


#------------ examples -----------------------------------------

#PROJECT = examples/blinky
#PROJECT = examples/blinky_rit
#PROJECT = examples/adc_fir_dac
#PROJECT = examples/freertos_blinky

#------------ sapi_examples ------------------------------------

#------------ Bare-metal examples ------------

#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/gpio/gpio_01_switches_leds
#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/gpio/gpio_02_blinky
#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/gpio/gpio_03_blinky_switch
#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/gpio/gpio_04_led_sequences

#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/keypad_7segment_01
#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/lcd_01

#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/uart/uart_01_echo
#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/uart/uart_02_receive_string_blocking
#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/uart/uart_03_receive_string

#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/stdio_01_printf_sprintf

#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/adc_dac_01

#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/cycles_counter_01
#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/tick_01_tickHook
#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/rtc_01

#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/pwm/pwm_01
#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/pwm/pwm_02_rgb_controller_uart
#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/servo_01

#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/magnetometers/i2c_01_hmc5883l
#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/magnetometers/i2c_02_qmc5883l

#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/temperature_humidity_sensors/dht11_01

#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/ultrasonicSensors/ultrasonicSensor_HCSR04_01

#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/spi_01_sdCard_fatFileSystem

#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/wifi_esp01_esp8266/01_uart_bridge
#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/wifi_esp01_esp8266/02_http_server
#PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/wifi_esp01_esp8266/03_thingspeak

#------------ Operating systems examples ------------

#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/coperative/scheduler_01_seos
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/coperative/scheduler_02_seos_background_foreground
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/coperative/seos_Pont2014_01
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/coperative/seos_pont_02_microwave

#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeOSEK/freeOSEK_01_blinky

#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_01_blinky
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_02_Queue
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_03_ChanFatFS_SPI_SdCard_ADC_log

#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example001
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example002
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example003
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example004
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example005
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example006
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example007
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example008
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example009
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example010
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example011
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example012
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example013
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example014
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example015
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example016
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example017
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example018
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example019
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example020
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example021
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example022
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example023
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example024
#PROJECT = sapi_examples/edu-ciaa-nxp/operating_systems/freeRTOS/freeRTOS_book/Example025

#-------------------------------------------------------------------------------
# current target
#-------------------------------------------------------------------------------

TARGET = lpc4337_m4
#TARGET = lpc4337_m0
#TARGET = lpc1769
#TARGET = lpc54102_m4
#TARGET = lpc54102_m0
#TARGET = lpc11u68

#-------------------------------------------------------------------------------
# current board (optional)
#-------------------------------------------------------------------------------

BOARD = edu_ciaa_nxp
#BOARD = ciaa_nxp
#BOARD = lpcxpresso1769

#-------------------------------------------------------------------------------

# Object file for multicore applications (only needed by lpc54102_m4 target if
# you need to add an lpc54102_m0 program). For example:
#SLAVE_OBJ_FILE = out/lpc54102_m0/blinky_m0.axf.o

#-------------------------------------------------------------------------------
