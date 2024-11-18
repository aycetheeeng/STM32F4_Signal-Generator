/* USER CODE BEGIN Header */
/**
  *******************************************************************************
  * @file           : Controller.h
  * @brief          : Controller header
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
#include "main.h"
#include "stdint.h"


typedef enum
{
		SineWave,
		Sawtooth,
		Triangle,
		Square,
}Signal_type;

typedef struct
{
    float amplitude;   // Genlik
    float freq;        // Frekans
    uint8_t signal_type;  // Sinyal tipi (Sinüs, Testere, Üçgen, Kare)
} Signal_Properties;
