/* USER CODE BEGIN Header */
/**
  *******************************************************************************
  * @file           : Controller.c
  * @brief          : Controller source
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
#include "Controller.h"
#include "math.h"

extern DAC_HandleTypeDef hdac;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef hadc2;

uint8_t current_wave_type = 0; 
uint16_t adc_value, amplitude;
volatile uint8_t last_button_state = GPIO_PIN_RESET;  // butonun önceki durumu 
														

void microDelay (uint16_t delay)
{
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  while (__HAL_TIM_GET_COUNTER(&htim2) < delay);
}

  
// pot okuma
// PA2'den ADC degeri oku (genlik için)
uint16_t read_frequency_potentiometer() {
    // PA2 ADC okuma islemi
    HAL_ADC_Start(&hadc2);
    if (HAL_ADC_PollForConversion(&hadc2, 10) == HAL_OK) {
        return HAL_ADC_GetValue(&hadc2);
    }
    return 0; 
}

// PA1'den ADC degeri oku (frekans)
uint16_t read_amplitude_potentiometer() {
    // PA1 ADC okuma islemi
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
        return HAL_ADC_GetValue(&hadc1);
    }
    return 0; 
}
