#include <stdio.h>
#include "LCD_2inch4.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void) {
	setup();
	while (1) {
		vTaskDelay(100);
	}
}


