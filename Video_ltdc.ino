/***************************************************************************
 * Arduino GIGA LTDC VGA demo 800x600 
 * Copyright (C) 2025 O2S
 *
 * I used STM32Cube IDE to set the parameters using an4861 doc from STM
 * (an4861-introduction-to-lcdtft-display-controller-ltdc-on-stm32-mcus-stmicroelectronics)
 ***************************************************************************/

#define HAL_MODULE_ENABLED

#define HAL_GPIO_MODULE_ENABLED
#define HAL_LTDC_MODULE_ENABLED

#include <arduino.h>

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_gpio.h"

// #include "stm32f10x.h"
#include <inttypes.h>

#include <SDRAM.h>

LTDC_HandleTypeDef hltdc;

/**LTDC GPIO Configuration for GIGA board
    PK5     ------> LTDC_B6
    PG10    ------> LTDC_G3
    PK4     ------> LTDC_B5
    PJ15    ------> LTDC_B3
    PH15    ------> LTDC_G4
    PK6     ------> LTDC_B7
    PK3     ------> LTDC_B4
    PG12    ------> LTDC_B1
    PK7     ------> LTDC_DE
    PG13    ------> LTDC_R0
    PJ14    ------> LTDC_B2
    PJ12    ------> LTDC_B0
    PE6     ------> LTDC_G1
    PI10    ------> LTDC_HSYNC
    PI11    ------> LTDC_G6
    PI13    ------> LTDC_VSYNC
    PI14    ------> LTDC_CLK
    PK2     ------> LTDC_G7
    PK0     ------> LTDC_G5
    PJ0     ------> LTDC_R1
    PJ7     ------> LTDC_G0
    PJ6     ------> LTDC_R7
    PI15    ------> LTDC_G2
    PJ1     ------> LTDC_R2
    PJ5     ------> LTDC_R6
    PJ2     ------> LTDC_R3
    PJ3     ------> LTDC_R4
    PJ4     ------> LTDC_R5
*/
void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hltdc->Instance==LTDC) {
  /** Initializes the peripherals clock (PLL IN is 24 MHz for Arduino GIGA at startup ...
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLL3.PLL3M = 4;
    PeriphClkInitStruct.PLL3.PLL3N = 10;
    PeriphClkInitStruct.PLL3.PLL3P = 1;
    PeriphClkInitStruct.PLL3.PLL3Q = 1;
    PeriphClkInitStruct.PLL3.PLL3R = 1;
    PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_3;
    PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
    PeriphClkInitStruct.PLL3.PLL3FRACN = 0.0;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
      Serial.println("LTDC MSP Clock init failed");
    }

    /* Peripheral clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOK_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOJ_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE(); 

    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_3
                          |GPIO_PIN_7|GPIO_PIN_2|GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_12|GPIO_PIN_0
                          |GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_1|GPIO_PIN_5
                          |GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_13|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    /* LTDC interrupt Init */
    HAL_NVIC_SetPriority(LTDC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LTDC_IRQn);
    HAL_NVIC_SetPriority(LTDC_ER_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LTDC_ER_IRQn);
  }
}

/*
 * not used here but anyway ...
 */
void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* hltdc) {  
  if(hltdc->Instance==LTDC) {
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOK, GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_3
                          |GPIO_PIN_7|GPIO_PIN_2|GPIO_PIN_0);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_13);

    HAL_GPIO_DeInit(GPIOJ, GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_12|GPIO_PIN_0
                          |GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_1|GPIO_PIN_5
                          |GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15);

    /* LTDC interrupt DeInit */
    HAL_NVIC_DisableIRQ(LTDC_IRQn);
    HAL_NVIC_DisableIRQ(LTDC_ER_IRQn);
  }
}

static void MX_LTDC_Init(void) {
  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AH;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AH;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AH;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 127;
  hltdc.Init.VerticalSync = 3;
  hltdc.Init.AccumulatedHBP = 215;
  hltdc.Init.AccumulatedVBP = 26;
  hltdc.Init.AccumulatedActiveW = 1015;
  hltdc.Init.AccumulatedActiveH = 626;
  hltdc.Init.TotalWidth = 1055;
  hltdc.Init.TotalHeigh = 627;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK) {
    Serial.println("LTDC Config failed");
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 800;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 600;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565; // LTDC_PIXEL_FORMAT_L8; // work also
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = SDRAM_START_ADDRESS;
  pLayerCfg.ImageWidth = 832;   // frame buffer aligned to 128 bytes ... an4661 better from docs
  pLayerCfg.ImageHeight = 600;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK) {
    Serial.println("LTDC Config failed");
  }
}

void setup(void) {
  Serial.begin(115200);
	SDRAM.begin(SDRAM_START_ADDRESS + 832*600*2);  // offset for Framebuffer at start
  delay(1000);
	Serial.println("Init Start");
	HAL_LTDC_MspInit(&hltdc);
	MX_LTDC_Init();
	Serial.println("Init Done");
}

int dec = 0;
void loop() {
	while (1) {
		uint16_t *buf = (uint16_t *)SDRAM_START_ADDRESS;  // frame buffer
		for (int y = 0; y < 600; y++) {
			for (int x = 0; x < 800; x++) {
        int col = x+dec;
				*buf++ = ((col & 0x2F) << 5) + (col & 0x1F);
			} buf += 32;  // skip 32 int16 for alignement
		} 
    // sync SDRAM content
    SCB_CleanInvalidateDCache_by_Addr((void *)SDRAM_START_ADDRESS, 832*600*2); 
    // needed to have a clean display due to M7 caches
    // otherwise declare the FB as writethrough ...
    // or compute the display with the M4 (no caches)
		delay(100);
    dec++;
	}
}

/**
  * @brief This function handles LTDC global interrupt.
  */
void LTDC_IRQHandler(void) {
	Serial.println("IRQ Called");
  HAL_LTDC_IRQHandler(&hltdc);
}

// #include "stm32h7xx_it.h"

/**
  * @brief This function handles LTDC global error interrupt.
  */
void LTDC_ER_IRQHandler(void) {
	Serial.println("IRQ ER Called");
  HAL_LTDC_IRQHandler(&hltdc);
}