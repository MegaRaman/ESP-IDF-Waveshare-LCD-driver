#include "spi_buffer.h"
#include "driver/spi_master.h"
#include "portmacro.h"
#include <string.h>

void init_spi_buf(spi_buf *buf, uint8_t max_len, spi_device_handle_t *spi) {
	if (max_len > SPI_BUF_MAX_SIZE) {
		buf->max_len = SPI_BUF_MAX_SIZE;
		return;
	}
	buf->max_len = max_len;
	buf->spi = spi;
}

void spi_buf_write_byte(spi_buf *buf, uint8_t byte) {
	buf->data[buf->cur_len++] = byte;
	if (buf->cur_len == buf->max_len)
		spi_buf_flush(buf);
}

void spi_buf_flush(spi_buf *buf) {
	if (buf->cur_len == 0)
		return;
	spi_transaction_t trans;
	memset(&trans, 0, sizeof(trans));
	trans.length = 8 * buf->cur_len;
	trans.tx_buffer = buf->data;
	trans.rx_buffer = NULL;
	spi_device_polling_transmit(*(buf->spi), &trans);
	buf->cur_len = 0;
}

void spi_buf_imm_write(spi_buf *buf, uint8_t byte) {
	spi_transaction_t trans;
	memset(&trans, 0, sizeof(trans));
	trans.length = 8;
	trans.tx_buffer = &byte;
	trans.rx_buffer = NULL;
	/* spi_device_queue_trans(*(buf->spi), &trans, portMAX_DELAY); */
	spi_device_polling_transmit(*(buf->spi), &trans);
}

