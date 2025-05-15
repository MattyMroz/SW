/* gpio.h */
#ifndef __GPIO_H
#define __GPIO_H

#include "stm32l4xx_hal_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  Włącza zegar dla portu GPIO
  * @param  GPIO_Port_Mask Maska bitowa dla zegara portu (np. RCC_AHB2ENR_GPIOBEN)
  * @retval None
  */
void GPIO_Clock_Enable(uint32_t GPIO_Port_Mask);

/**
  * @brief  Konfiguruje pin GPIO
  * @param  GPIOx_INSTANCE Wskaźnik do instancji GPIO (np. GPIOB)
  * @param  PinNumber Numer pinu (0-15)
  * @param  Mode Tryb pracy pinu (INPUT, OUTPUT, ALTERNATE, ANALOG)
  * @param  OutputType Typ wyjścia (PP, OD)
  * @param  Speed Prędkość wyjścia (LOW, MEDIUM, HIGH, VHIGH)
  * @param  Pull Podciąganie (NONE, UP, DOWN)
  * @retval None
  */
void GPIO_Pin_Setup(GPIO_TypeDef* GPIOx_INSTANCE, uint16_t PinNumber, uint32_t Mode, uint32_t OutputType, uint32_t Speed, uint32_t Pull);

/**
  * @brief  Ustawia stan pinu GPIO
  * @param  GPIOx_INSTANCE Wskaźnik do instancji GPIO (np. GPIOB)
  * @param  PinMask Maska bitowa pinu (1<<PIN_NUM)
  * @param  PinState Wartość 0 lub 1
  * @retval None
  */
void GPIO_WritePin(GPIO_TypeDef* GPIOx_INSTANCE, uint16_t PinMask, uint8_t PinState);

/**
  * @brief  Odczytuje stan pinu GPIO
  * @param  GPIOx_INSTANCE Wskaźnik do instancji GPIO (np. GPIOB)
  * @param  PinMask Maska bitowa pinu (1<<PIN_NUM)
  * @retval Stan pinu (0 lub 1)
  */
uint8_t GPIO_ReadPin(GPIO_TypeDef* GPIOx_INSTANCE, uint16_t PinMask);

/**
  * @brief  Włącza zasilanie VDDIO2 (PG[15:2])
  * @retval None
  */
void My_EnableVddIO2(void);

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H */ 