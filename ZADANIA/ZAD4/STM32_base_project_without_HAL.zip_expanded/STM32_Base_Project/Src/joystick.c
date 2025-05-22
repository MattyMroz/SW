/* joystick.c */
#include "joystick.h"

/* Zmienne globalne do obsługi joysticka */
uint32_t last_joy_ok_poll_time = 0;
uint8_t joy_ok_prev_stable_state = 1; // 1 = zwolniony (stan początkowy), 0 = wciśnięty
uint8_t joy_ok_last_raw_state = 1;    // Zakładamy początkowo zwolniony
uint32_t joy_ok_last_change_time = 0;  // Czas ostatniej zmiany stanu surowego joysticka

// Inicjalizuje GPIO dla joysticka
void Joystick_Init(void) {
    GPIO_Clock_Enable(JOY_OK_PORT_RCC_EN);
    GPIO_Pin_Setup(JOY_OK_PORT, JOY_OK_PIN_NUM, GPIO_MODER_MODE_INPUT, 0, 0, GPIO_PUPDR_PUPD_UP);
}

// Odczytuje surowy stan przycisku joysticka (bez debouncingu)
// Zwraca stan przycisku (0: wciśnięty, 1: zwolniony)
uint8_t Joystick_Get_OK_Raw_State(void) {
    return GPIO_ReadPin(JOY_OK_PORT, JOY_OK_PIN_MASK);
}