/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    game.c
  * @brief   This file contains all the function prototypes for
  *          the rtc.c file
  ******************************************************************************
  */
/* USER CODE END Header */
#include "oled.h"
#include "rtc.h"
#include "game.h"

extern unsigned char BMP4[],BMP5[];
void game(){
			if (jump_mark == 0) {
					OLED_ShowPicture(0, 0, 128, 8, BMP4);
				} else {
					OLED_ShowPicture(0, 0, 128, 8, BMP5);
					n++;
					if (n > 30) {
						jump_mark = 0;
						n = 0;
					}
				}
				speed++;
				if (speed > 5) {
					start_point_x = start_point_x + 2;
					speed = 0;
					OLED_Clear();
				}

				if (start_point_x == 128) {
					start_point_x = 0;
				}
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET) {
					jump_mark = 1;
				}
				if (jump_mark == 0 && start_point_x % 65 == 0) {

					flag = 4;

				}	
					
				}
void showgameover(){

	OLED_ShowString(0, 0, (unsigned char *)"GAME", 12);
				OLED_ShowString(0, 32, (unsigned char *)"OVER", 12);
				OLED_WR_Byte(0xa1, OLED_CMD);
				ms = 0;

}
void show_square(){
OLED_DrawSquare((0 + start_point_x) % 127, 50, (10 + start_point_x) % 127, 60);
OLED_DrawSquare((50 + start_point_x) % 127, 50, (60 + start_point_x) % 127, 60);
OLED_DrawSquare((100 + start_point_x) % 127, 50, (110 + start_point_x) % 127, 60);
}
