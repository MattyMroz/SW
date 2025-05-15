/* joystick.c */
#include "joystick.h"

/* Zmienne globalne do obsługi joysticka */
uint32_t last_joy_ok_poll_time = 0;
uint8_t joy_ok_prev_stable_state = 1; // 1 = zwolniony (stan początkowy), 0 = wciśnięty
uint8_t joy_ok_last_raw_state = 1;    // Zakładamy początkowo zwolniony
uint32_t joy_ok_last_change_time = 0;  // Czas ostatniej zmiany stanu surowego joysticka

/**
  * @brief  Inicjalizuje GPIO dla joysticka
  * @retval None
  */
void Joystick_Init(void) {
    GPIO_Clock_Enable(JOY_OK_PORT_RCC_EN);
    GPIO_Pin_Setup(JOY_OK_PORT, JOY_OK_PIN_NUM, GPIO_MODER_MODE_INPUT, 0, 0, GPIO_PUPDR_PUPD_UP);
}

/**
  * @brief  Odczytuje stan przycisku joysticka z debouncingiem
  * @param  current_tick Aktualna wartość licznika systemowego
  * @retval Stan przycisku joysticka (0: wciśnięty, 1: zwolniony)
  */
uint8_t Joystick_Read_OK_Button_State(uint32_t current_tick) {
    if ((current_tick - last_joy_ok_poll_time) >= JOY_OK_POLL_INTERVAL_MS) {
        last_joy_ok_poll_time = current_tick;
        uint8_t joy_ok_raw_state = GPIO_ReadPin(JOY_OK_PORT, JOY_OK_PIN_MASK);

        if (joy_ok_raw_state != joy_ok_last_raw_state) {
            joy_ok_last_change_time = current_tick;
        }
        else {
            if ((current_tick - joy_ok_last_change_time) >= JOY_OK_DEBOUNCE_TIME_MS) {
                if (joy_ok_raw_state != joy_ok_prev_stable_state) {
                    joy_ok_prev_stable_state = joy_ok_raw_state;
                }
            }
        }
        joy_ok_last_raw_state = joy_ok_raw_state;
    }
    return joy_ok_prev_stable_state;
}