/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    beep.c
  * @brief   This file contains all the function prototypes for
  *          the rtc.c file
  ******************************************************************************
  */
/* USER CODE END Header */
#include "main.h"
#include "gpio.h"
#include "stdlib.h"	
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include "beep.h"
void delay500us(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=71;b>0;b--)
        for(a=2;a>0;a--);
}

void fs(int ms){ //·äÃùÆ÷ÏìÒ»Éù
	int i;
	for(i=0;i<200;i++){
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		delay500us(); //ÑÓÊ±		
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		delay500us(); //ÑÓÊ±		
	}
}
