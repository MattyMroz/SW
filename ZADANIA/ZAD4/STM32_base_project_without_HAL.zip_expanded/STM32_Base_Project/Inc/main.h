/* main.h */
#ifndef __MAIN_H
#define __MAIN_H

#include "stm32l4xx_hal_conf.h"
#include "gpio.h"
#include "display.h"
#include "joystick.h"
#include "system_utils.h"

// Odczytuje i przetwarza stan joysticka z prostym debouncingiem
void Process_Joystick(void);

// Aktualizuje wartość licznika na podstawie zapamiętanego stanu joysticka
void Update_Counter_Logic(void);

// Odświeża wyświetlacz (obsługa multipleksowania)
void Refresh_Display_Logic(void);

// Obsługa błędu
void Error_Handler(void);

#endif /* __MAIN_H */