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
#include "DEV_Config.h"
#include "driver/ledc.h"
#include "driver/spi_master.h"
#include "spi_buffer.h"

#define RST_PIN_CONF 	(1ULL << DEV_RST_PIN)
#define DC_PIN_CONF 	(1ULL << DEV_DC_PIN)
#define PIN_CONF 		(RST_PIN_CONF | DC_PIN_CONF)

static spi_buf lcd_buf;


void DEV_SPI_WRITE_DATA(uint8_t _dat) {
	spi_buf_write_byte(&lcd_buf, _dat);
}

void DEV_SPI_WRITE_COMMAND(uint8_t _com) {
	if (lcd_buf.cur_len != 0) {
		DEV_Digital_Write(DEV_DC_PIN, 1);
		spi_buf_flush(&lcd_buf);
		DEV_Digital_Write(DEV_DC_PIN, 0);
	}
	spi_buf_imm_write(&lcd_buf, _com);
}

void GPIO_Init() {
	/* GPIO configuration */
	gpio_config_t io_config = { 0 };
    io_config.intr_type = GPIO_INTR_DISABLE;
    io_config.mode = GPIO_MODE_OUTPUT;
	io_config.pin_bit_mask = PIN_CONF;
	gpio_config(&io_config);

	/* PWM configuration */
	ledc_timer_config_t pwm_timer = {
		.speed_mode = LEDC_LOW_SPEED_MODE,
		.timer_num = LEDC_TIMER_0,
		.duty_resolution = LEDC_TIMER_13_BIT,
		/* .freq_hz = 4000, */
		.freq_hz = 500,
		.clk_cfg = LEDC_AUTO_CLK
	};
    ESP_ERROR_CHECK(ledc_timer_config(&pwm_timer));

    ledc_channel_config_t pwm_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = DEV_BL_PIN,
        .duty           = 4500, // Set duty to 55%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_channel));
}

void setup_spi(spi_device_handle_t *spi) {
    esp_err_t ret;
    spi_bus_config_t buscfg = {
        .miso_io_num = -1,
        .mosi_io_num = VSPI_MOSI_PIN,
        .sclk_io_num = VSPI_CLK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0
    };

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 4 * 1000 * 1000,     	// Clock out at 4 MHz
        .mode = 3,                              // SPI mode 3
        .spics_io_num = VSPI_CS_PIN,            // CS pin
        .queue_size = 15,
        .pre_cb = NULL,
		.duty_cycle_pos = 0
    };
    ret = spi_bus_initialize(SPI3_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    ret = spi_bus_add_device(SPI3_HOST, &devcfg, spi);
    ESP_ERROR_CHECK(ret);
}


void Config_Init(spi_device_handle_t *spi) {
	GPIO_Init();

	/* SPI configuration */
	setup_spi(spi);

	/* SPI buffer configuration */
	init_spi_buf(&lcd_buf, 20, spi);
}

