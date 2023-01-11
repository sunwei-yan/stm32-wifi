/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    calendars.c
  * @brief   This file contains all the function prototypes for
  *          the rtc.c file
  ******************************************************************************
  */
/* USER CODE END Header */
#include "oled.h"
#include "rtc.h"
void showtime(){
OLED_WR_Byte(0xa1, OLED_CMD);
				OLED_ShowNum(0, 0, 2023, 4, 16);
				OLED_ShowString(33, 0, (unsigned char *)"-", 16);
				OLED_ShowNum(40, 0, mon, 2, 16);
				OLED_ShowString(56, 0, (unsigned char *)"-", 16);
				OLED_ShowNum(64, 0, date, 2, 16);
				OLED_ShowNum(0, 20, hour, 2, 16);
				OLED_ShowString(16, 20, (unsigned char *)":", 16);
				OLED_ShowNum(20, 20, minte, 2, 16);
				OLED_ShowString(36, 20, (unsigned char *)":", 16);
				OLED_ShowNum(40, 20, second, 2, 16);
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET) {
					OLED_WR_Byte(0xa1, OLED_CMD);
					OLED_ShowNum(0, 0, 2022, 4, 16);
					OLED_ShowString(33, 0, (unsigned char *)"-", 16);
					OLED_ShowNum(40, 0, mon, 2, 16);
					if (hour >= 0 && hour < 12) {
						OLED_ShowNum(0, 20, hour, 2, 16);

					} else if (hour == 12) {
						OLED_ShowNum(0, 20, hour, 2, 16);
					} else {
						OLED_ShowNum(0, 20, hour - 12, 2, 16);

					}

					OLED_ShowString(16, 20, (unsigned char *)":", 16);
					OLED_ShowNum(20, 20, minte, 2, 16);
					OLED_ShowString(36, 20, (unsigned char *)":", 16);
					OLED_ShowNum(40, 20, second, 2, 16);
				}}
void ADC1_show(){

OLED_WR_Byte(0xa1, OLED_CMD);
				OLED_ShowNum(0, 0, ADC_Value * 3.3 / 4095 * 100 / 100, 1, 16);
				OLED_ShowString(20, 0, (unsigned char *)".", 16);
				OLED_ShowNum(30, 0, (int)(ADC_Value * 3.3 / 4095 * 10) % 10, 1, 16);
				OLED_ShowNum(40, 0, (int)(ADC_Value * 3.3 / 4095 * 100) % 100, 1, 16);
				OLED_ShowNum(0, 32, (3.1 - 3.3 / 4095 * ADC_Value) / 0.0043 + 15, 2, 16);
				OLED_ShowString(50, 0, (unsigned char *)"V", 16);
				if (ADC_Value > 1800) {
					OLED_DrawPoint(refresh_tags % 127, 35 + (ADC_Value - 1280) / 10);
				}

}
void time_set(){
			OLED_WR_Byte(0xa1, OLED_CMD);
					OLED_ShowNum(0, 0, 2023, 4, 16);
					OLED_ShowString(33, 0, (unsigned char *)"-", 16);
					OLED_ShowNum(40, 0, mon, 2, 16);
					if (hour >= 0 && hour < 12) {
						OLED_ShowNum(0, 20, hour, 2, 16);

					} else if (hour == 12) {
						OLED_ShowNum(0, 20, hour, 2, 16);
					} else {
						OLED_ShowNum(0, 20, hour - 12, 2, 16);
					}
					OLED_ShowString(16, 20, (unsigned char *)":", 16);
					OLED_ShowNum(20, 20, mon, 2, 16);
					OLED_ShowString(36, 20, (unsigned char *)":", 16);
					OLED_ShowNum(40, 20, mon, 2, 16);
					OLED_Refresh ();
					if(scanf("%s",timedat)==1){
		printf("%s",timedat);
		dats=("%d",timedat[0])-48;
		dats2=("%d",timedat[1])-48;
							dats=dats*10+dats2;
							dats=otoh(dats );
		datf=("%d",timedat[2])-48;
		datf2=("%d",timedat[3])-48;
				datf=datf*10+datf2;	
datf=otoh(datf );							
		MX_RTC_Init();
		flag=0;
		}
}