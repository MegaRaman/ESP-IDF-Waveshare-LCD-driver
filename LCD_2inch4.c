#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "driver/spi_master.h"
#include "image.h"
#include "LCD_2inch4.h"
#include "portmacro.h"

void setup()
{
	spi_device_handle_t handle;
	Config_Init(&handle);
	spi_device_acquire_bus(handle, portMAX_DELAY);
	LCD_Init();
	LCD_Clear(0xffff);
	Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
	Paint_Clear(WHITE);

	/* for(int y = 0; y < 160; y++) */
	/* 	for(int x = 0; x < 120; x++) */
	/* 		Paint_SetPixel(x, y, x | y << 5); */

	Paint_DrawString_EN(30, 10, "123", &Font24, YELLOW, RED);
	Paint_DrawString_EN(30, 34, "ABC", &Font24, BLUE, CYAN);

	Paint_DrawRectangle(125, 10, 225, 58, RED,  DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
	Paint_DrawLine(125, 10, 225, 58, MAGENTA,   DOT_PIXEL_2X2,LINE_STYLE_SOLID);
	Paint_DrawLine(225, 10, 125, 58, MAGENTA,   DOT_PIXEL_2X2,LINE_STYLE_SOLID);

	Paint_DrawCircle(150,100, 25, BLUE,   DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
	Paint_DrawCircle(180,100, 25, BLACK,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
	Paint_DrawCircle(210,100, 25, RED,    DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
	Paint_DrawCircle(165,125, 25, YELLOW, DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
	Paint_DrawCircle(195,125, 25, GREEN,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);

	Paint_DrawImage(gImage_70X70, 20, 80, 70, 70);
	spi_device_release_bus(handle);
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

