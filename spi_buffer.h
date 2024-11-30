#ifndef __SPI_BUFFER_H__
#define __SPI_BUFFER_H__

#include "stdint.h"
#include "driver/spi_master.h"

#define SPI_BUF_MAX_SIZE 64

typedef struct {
	uint8_t data[SPI_BUF_MAX_SIZE];
	uint8_t cur_len;
	uint8_t max_len;
	spi_device_handle_t *spi;
} spi_buf;

void init_spi_buf(spi_buf *buf, uint8_t max_len, spi_device_handle_t *spi);
void spi_buf_write_byte(spi_buf *buf, uint8_t byte);
void spi_buf_flush(spi_buf *buf);
void spi_buf_imm_write(spi_buf *buf, uint8_t byte);

#endif // __SPI_BUFFER_H__

