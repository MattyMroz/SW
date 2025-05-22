/* system_utils.h */
#ifndef __SYSTEM_UTILS_H
#define __SYSTEM_UTILS_H

#include "stm32l4xx_hal_conf.h"

/* Definicje parametrów systemowych */
#define COUNTER_UPDATE_DELAY_MS 1000

// Funkcja opóźnienia (blokująca)
// milliseconds Czas opóźnienia w milisekundach
void Custom_Delay_ms(volatile uint32_t milliseconds);

/* Deklaracje zmiennych zewnętrznych */
extern volatile uint32_t systick_counter;

#endif /* __SYSTEM_UTILS_H */