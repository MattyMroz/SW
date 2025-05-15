/* system_utils.h */
#ifndef __SYSTEM_UTILS_H
#define __SYSTEM_UTILS_H

#include "stm32l4xx_hal_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Definicje parametrów systemowych */
#define COUNTER_UPDATE_DELAY_MS 1000

/**
  * @brief  Inicjalizuje licznik SysTick
  * @param  SystemCoreClockValue Wartość zegara systemowego
  * @retval None
  */
void My_SysTick_Init(uint32_t SystemCoreClockValue);

/**
  * @brief  Funkcja opóźnienia (blokująca)
  * @param  milliseconds Czas opóźnienia w milisekundach
  * @retval None
  */
void Custom_Delay_ms(volatile uint32_t milliseconds);

/* Deklaracje zmiennych zewnętrznych */
extern volatile uint32_t systick_counter;

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_UTILS_H */ 