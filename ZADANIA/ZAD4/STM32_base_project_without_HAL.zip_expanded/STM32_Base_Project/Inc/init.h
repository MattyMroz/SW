/* init.h */
#ifndef __INIT_H
#define __INIT_H

#include "stm32l4xx_hal_conf.h"
#include "gpio.h"
#include "display.h"
#include "joystick.h"
#include "system_utils.h"

// Inicjalizuje wszystkie komponenty systemu
void System_Init(void);

#endif /* __INIT_H */