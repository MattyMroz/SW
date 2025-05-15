/* main.h */
#ifndef __MAIN_H
#define __MAIN_H

#include "stm32l4xx_hal_conf.h"
#include "gpio.h"
#include "display.h"
#include "joystick.h"
#include "system_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  Aktualizuje wartość licznika na podstawie stanu joysticka
 * @param  current_tick Aktualny czas systemowy
 * @retval None
 */
void Update_Counter(uint32_t current_tick);

/**
 * @brief  Odświeża wyświetlacz (obsługa multipleksowania)
 * @param  current_tick Aktualny czas systemowy
 * @retval None
 */
void Refresh_Display(uint32_t current_tick);

/**
 * @brief  Obsługa błędu
 * @retval None
 */
void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */ 