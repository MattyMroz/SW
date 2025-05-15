/* joystick.h */
#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "stm32l4xx_hal_conf.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Definicje pinów joysticka */
#define JOY_OK_PORT_RCC_EN          RCC_AHB2ENR_GPIOEEN
#define JOY_OK_PORT                 GPIOE
#define JOY_OK_PIN_NUM              15 // PE15
#define JOY_OK_PIN_MASK             (1UL << JOY_OK_PIN_NUM)

/* Parametry obsługi joysticka */
#define JOY_OK_DEBOUNCE_TIME_MS     50
#define JOY_OK_POLL_INTERVAL_MS     10   // Interwał odpytywania joysticka

/**
  * @brief  Inicjalizuje GPIO dla joysticka
  * @retval None
  */
void Joystick_Init(void);

/**
  * @brief  Odczytuje stan przycisku joysticka z debouncingiem
  * @param  current_tick Aktualna wartość licznika systemowego
  * @retval Stan przycisku joysticka (0: wciśnięty, 1: zwolniony)
  */
uint8_t Joystick_Read_OK_Button_State(uint32_t current_tick);

/* Deklaracje zmiennych związanych z obsługą joysticka */
extern uint32_t last_joy_ok_poll_time;
extern uint8_t joy_ok_prev_stable_state;
extern uint8_t joy_ok_last_raw_state;
extern uint32_t joy_ok_last_change_time;

#ifdef __cplusplus
}
#endif

#endif /* __JOYSTICK_H */ 