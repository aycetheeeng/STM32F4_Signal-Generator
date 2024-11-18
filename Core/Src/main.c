/* USER CODE BEGIN Header */
/**
  *******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  *******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  * @author         : Ayçe Mýsýrlýlar
  * @date           : 09.11.2024
  * @version        : 1.1
  *
  *******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Controller.h"
#include "stdint.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

DAC_HandleTypeDef hdac;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DAC_Init(void);
static void MX_TIM2_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//dalga serileri
uint16_t sawtooth[100] = {0, 41, 82, 123, 164, 205, 246, 287, 328, 369,
                        410, 451, 492, 533, 574, 615, 656, 697, 738, 779,
                        820, 861, 902, 943, 984, 1025, 1066, 1107, 1148, 1189,
                        1230, 1271, 1312, 1353, 1394, 1435, 1476, 1517, 1558, 1599,
                        1640, 1681, 1722, 1763, 1804, 1845, 1886, 1927, 1968, 2009,
                        2050, 2091, 2132, 2173, 2214, 2255, 2296, 2337, 2378, 2419,
                        2460, 2501, 2542, 2583, 2624, 2665, 2706, 2747, 2788, 2829,
                        2870, 2911, 2952, 2993, 3034, 3075, 3116, 3157, 3198, 3239,
                        3280, 3321, 3362, 3403, 3444, 3485, 3526, 3567, 3608, 3649,
                        3690, 3731, 3772, 3813, 3854, 3895, 3936, 3977, 4018, 4059};
uint16_t triangle[100] = {0, 81, 162, 243, 324, 405, 486, 567, 648, 729,
                        810, 891, 972, 1053, 1134, 1215, 1296, 1377, 1458, 1539,
                        1620, 1701, 1782, 1863, 1944, 2025, 2106, 2187, 2268, 2349,
                        2430, 2511, 2592, 2673, 2754, 2835, 2916, 2997, 3078, 3159,
                        3240, 3321, 3402, 3483, 3564, 3645, 3726, 3807, 3888, 3969,
                        4050, 3969, 3888, 3807, 3726, 3645, 3564, 3483, 3402, 3321,
                        3240, 3159, 3078, 2997, 2916, 2835, 2754, 2673, 2592, 2511,
                        2430, 2349, 2268, 2187, 2106, 2025, 1944, 1863, 1782, 1701,
                        1620, 1539, 1458, 1377, 1296, 1215, 1134, 1053, 972, 891,
                        810, 729, 648, 567, 486, 405, 324, 243, 162, 81};
uint16_t sinewave[100] = {0, 4, 16, 36, 64, 100, 144, 195, 253, 319,
                        391, 470, 555, 646, 742, 844, 950, 1061, 1176, 1294,
                        1415, 1538, 1664, 1791, 1919, 2048, 2176, 2304, 2431, 2557,
                        2680, 2801, 2919, 3034, 3145, 3251, 3353, 3449, 3540, 3625,
                        3704, 3776, 3842, 3900, 3951, 3995, 4031, 4059, 4079, 4091,
                        4095, 4091, 4079, 4059, 4031, 3995, 3951, 3900, 3842, 3776,
                        3704, 3625, 3540, 3449, 3353, 3251, 3145, 3034, 2919, 2801,
                        2680, 2557, 2431, 2304, 2176, 2048, 1919, 1791, 1664, 1538,
                        1415, 1294, 1176, 1061, 950, 844, 742, 646, 555, 470,
                        391, 319, 253, 195, 144, 100, 64, 36, 16, 4};
uint16_t squarewave[100] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4095, 4095, 4095, 4095,
														4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 
														4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 
														4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 
														4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 
														4095, 4095, 4095, 4095, 0, 0};

uint16_t *waveforms[] = {sawtooth, triangle, sinewave, squarewave};
uint8_t num_waveforms = sizeof(waveforms) / sizeof(waveforms[0]);

void microDelay (uint16_t delay);
uint16_t read_frequency_potentiometer(void);
uint16_t read_amplitude_potentiometer(void);
void generate_waveform(void);
void ButtonRead(void);
void DAC_Waves(void);
void change_waveform(void) ;
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
  MX_DAC_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  /* USER CODE BEGIN 2 */
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_TIM_Base_Start(&htim2);
	
	uint8_t current_wave_type = 0;   
	uint8_t last_button_state = GPIO_PIN_RESET;  // butonun önceki durumu 
														
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		    //buton durum
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET && last_button_state == GPIO_PIN_RESET) 
			{
        // dalga degistir
					if (current_wave_type == SineWave) {
							current_wave_type = Sawtooth;  // Sine -> Sawtooth
					} else if (current_wave_type == Sawtooth) {
							current_wave_type = Triangle;  // Sawtooth -> Triangle
					} else if (current_wave_type == Triangle) {
							current_wave_type = Square;  // Triangle -> Square
					} else if (current_wave_type == Square) {
							current_wave_type = SineWave;  // Square -> Sine
					}

        // debounce
        HAL_Delay(200);
			}

    // son buton durumunu kaydet
    last_button_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0); // buton

    // pot degerlerini oku
		uint16_t adc_value_freq = read_frequency_potentiometer(); // PA1 - Frekans ayari
		uint16_t adc_value_amp = read_amplitude_potentiometer(); // PA2 - Genlik ayari

		// Frekansi (delay_time) ayarla
		uint16_t delay_time = (adc_value_freq / 4095.0) * 10;  // 0-10 arasinda bir gecikme

		// Genligi (amplitude) ayarla
		uint16_t amplitude = (adc_value_amp / 4095.0) * 4095;  // 0-4095 arasinda genlik

    // dalgayi dac a gönder
	switch (current_wave_type) 
	{
    case SineWave:
        for (uint8_t i = 0; i < 100; i++) 
				{
            uint16_t scaled_value = (sinewave[i] * amplitude) / 4095;  // genlik ile ölçeklendir
            HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, scaled_value);
            microDelay(delay_time); // pota bagli gecikme (frekans)
        }
        break;
    
    case Sawtooth:
        for (uint8_t i = 0; i < 100; i++) 
				{
            uint16_t scaled_value = (sawtooth[i] * amplitude) / 4095;  // genlik ile ölçeklendir
            HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, scaled_value);
            microDelay(delay_time); // pota bagli gecikme (frekans)
        }
        break;

    case Triangle:
        for (uint8_t i = 0; i < 100; i++) 
				{
            uint16_t scaled_value = (triangle[i] * amplitude) / 4095;  // genlik ile ölçeklendir
            HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, scaled_value);
            microDelay(delay_time); // pota bagli gecikme (frekans)
        }
        break;

    case Square:
        for (uint8_t i = 0; i < 100; i++) 
				{
            uint16_t scaled_value = (squarewave[i] * amplitude) / 4095;  // genlik ile ölçeklendir
            HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, scaled_value);
            microDelay(delay_time); // pota bagli gecikme (frekans)
        }
        break;
	}

					
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */
  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */
  /* USER CODE END DAC_Init 1 */

  /** DAC Initialization
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */
  /* USER CODE END DAC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */
  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */
  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 83;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 99;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */
  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
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
  while (1)
  {
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
