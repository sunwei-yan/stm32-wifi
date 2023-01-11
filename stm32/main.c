/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
uint8_t zt[4];
uint8_t Rx_buf = 0;	//串口字符接收变量
uint8_t Rx_Flag = 0;	//串口接收正确数据标志位
uint8_t string[4];	//sprintf函数字符缓冲数组
uint16_t ADC_Value = 0;	//AD采集量化值变量
float ADC_Volt = 0;	//AD采集电压值变量
int refresh_tags = 0;
int flag = 0;
int jump_mark = 0;
int n = 0;
int start_point_x = 15;
int speed = 0;
int serial_port_speed = 0;
int ad_speed = 0;
int ms = 0;
int hour = 0;
int sec = 1;
int minu = 0;
int countdown_sign = 0;
int press_sign = 0;
int key_interruption = 10;
char timedat[20];
int dats=0x0;
int datf=0x0;
int dats2=0x0;
int datf2=0x0;
int mon;
int date;
int hour ;
int minte;
int second;
double	num1;
#define LEFT 2
#define RIGHT 3
unsigned char bx, by, hx, hy;
#include "oled.h"
#include "bmp.h"
#include "key.h"
#include "beep.h"
#include "game.h"
#include "calendars.h"
#include "countdown.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
RTC_DateTypeDef GetData;

RTC_TimeTypeDef GetTime;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_RTC_Init();
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	OLED_Init();
	HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	HAL_ADCEx_Calibration_Start(&hadc1);    //AD校准
	HAL_ADC_Start(&hadc1);
	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);//获取时间
		/* Get the RTC current Date */
		HAL_RTC_GetDate(&hrtc, &GetData, RTC_FORMAT_BIN);//获取日期
		mon=GetData.Month;
		date=GetData.Date;
		hour=GetTime.Hours;
		minte=GetTime.Minutes;
		second=GetTime.Seconds;

		switch (flag) {
			case 0:
				showtime();
				break;
			case 1:
				ADC1_show();
				break;
			case 2:
	show_square();
				game();
				break;
			case 4:
			showgameover();
				break;
			case 6:
				countdown();
				break;
			default:
				break;
			case 7:
			time_set();
				break;
		}
		OLED_Refresh ();
		flag = key(flag);
		HAL_ADC_Start_IT(&hadc1);
		refresh_tags++;
		if (refresh_tags == 127) {
			OLED_Clear();
			refresh_tags = 0;
		}
		num1 = (3.1 - 3.3 / 4095 * ADC_Value) / 0.0043 + 15;
		sprintf((char *)string, "%lf\n", num1 );
		if (serial_port_speed > 100) {
			HAL_UART_Transmit(&huart3, string, sizeof(string), 10000);	//串口3发送数据
			serial_port_speed = 0;
		}
		if (ad_speed > 5) {
			ADC_Value = HAL_ADC_GetValue(&hadc1);
			ad_speed = 0;
		}
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	static uint32_t time_cnt = 0;

	if (htim->Instance == TIM2) {
		if (++time_cnt >= 100) { //0.1s
			serial_port_speed++;
			ad_speed++;
			time_cnt = 0;
			if (press_sign == 1 && key_interruption > 0) {
				key_interruption--;


			}
			if (countdown_sign == 1 && ms > 0) {
				ms--;
			}
		}
	}


}
int fputc(int ch, FILE *f) {

	HAL_UART_Transmit(&huart1, (uint8_t*)&ch,1, HAL_MAX_DELAY);
	return ch;
}
int fgetc(FILE *f) {
	uint8_t ch;
	HAL_UART_Receive(&huart2, (uint8_t*)&ch,1, HAL_MAX_DELAY);
	return ch;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
