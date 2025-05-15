/* init.h */
#ifndef __INIT_H
#define __INIT_H

#include "stm32l4xx_hal_conf.h"
#include "gpio.h"
#include "display.h"
#include "joystick.h"
#include "system_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  Inicjalizuje GPIO całego systemu
  * @retval None
  */
void GPIO_Init_All(void);

/**
  * @brief  Inicjalizuje wszystkie komponenty systemu
  * @retval None
  */
void System_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __INIT_H */ 