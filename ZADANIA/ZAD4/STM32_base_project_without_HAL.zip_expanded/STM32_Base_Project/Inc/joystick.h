/* joystick.h */
#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "stm32l4xx_hal_conf.h"
#include "gpio.h"

/* Definicje pinów joysticka */
#define JOY_OK_PORT_RCC_EN          RCC_AHB2ENR_GPIOEEN
#define JOY_OK_PORT                 GPIOE
#define JOY_OK_PIN_NUM              15 // PE15
#define JOY_OK_PIN_MASK             (1UL << JOY_OK_PIN_NUM)

/* Parametry obsługi joysticka */
#define JOY_OK_DEBOUNCE_TIME_MS     50
#define JOY_OK_POLL_INTERVAL_MS     10   // Interwał odpytywania joysticka

// Inicjalizuje GPIO dla joysticka
void Joystick_Init(void);

// Odczytuje surowy stan przycisku joysticka (bez debouncingu)
// Zwraca stan przycisku (0: wciśnięty, 1: zwolniony)
uint8_t Joystick_Get_OK_Raw_State(void);

/* Deklaracje zmiennych związanych z obsługą joysticka */
extern uint32_t last_joy_ok_poll_time;
extern uint8_t joy_ok_prev_stable_state;
extern uint8_t joy_ok_last_raw_state;
extern uint32_t joy_ok_last_change_time;

#endif /* __JOYSTICK_H */