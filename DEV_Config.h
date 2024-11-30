/*****************************************************************************
* | File        :   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
*----------------
* | This version:   V1.0
* | Date        :   2018-11-22
* | Info        :

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include <stdint.h>
#include <stdio.h>
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "Debug.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * GPIO config
**/
#define DEV_DC_PIN  (4)
#define DEV_RST_PIN (22)
#define DEV_BL_PIN	(21)

#define VSPI_MOSI_PIN (23)
#define VSPI_CLK_PIN (18)
#define VSPI_CS_PIN (5)

/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) gpio_set_level(_pin, _value)
#define DEV_Digital_Read(_pin) gpio_get_level(_pin)


/**
 * SPI
**/
void DEV_SPI_WRITE_COMMAND(uint8_t _com);
void DEV_SPI_WRITE_DATA(uint8_t _dat);

/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms)    (vTaskDelay(pdMS_TO_TICKS(__xms)))

/*-----------------------------------------------------------------------------*/
 void Config_Init(spi_device_handle_t *spi);
#endif

