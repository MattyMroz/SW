/* main.c */
#include <stdint.h>
#include "main.h"
#include "init.h"

/* ========================================================================== */
/* == ZMIENNE GLOBALNE/STATYCZNE ============================================ */
/* ========================================================================== */
extern uint32_t SystemCoreClock;
uint16_t counter_value = 0;
static uint8_t current_display_digit_idx = 0; // Indeks aktualnie wyświetlanej cyfry (0 do DIGIT_COUNT-1)
// Tablica przechowująca cyfry do wyświetlenia (jedności, dziesiątki, etc.)
uint8_t digits_to_display[4] = {0, BLANK_DIGIT, BLANK_DIGIT, BLANK_DIGIT}; // Inicjalizacja dla 4 cyfr

static uint32_t last_counter_update_time = 0;
static uint32_t last_display_refresh_time = 0;

/**
 * @brief  Aktualizuje wartość licznika na podstawie stanu joysticka
 * @param  current_tick Aktualny czas systemowy
 * @retval None
 */
void Update_Counter(uint32_t current_tick)
{
    // --- Odczyt stanu joysticka ---
    uint8_t joy_ok_state = Joystick_Read_OK_Button_State(current_tick);

    // --- Logika aktualizacji licznika ---
    if ((current_tick - last_counter_update_time) >= COUNTER_UPDATE_DELAY_MS)
    {
        last_counter_update_time = current_tick;

        if (joy_ok_state == 0) {
            if (counter_value == 0) {
                counter_value = 9999; // Dostosuj, jeśli NUM_DISPLAY_DIGITS != 4
            } else {
                counter_value--;
            }
        } else {
            counter_value++;
            if (counter_value > 9999) { // Dostosuj, jeśli NUM_DISPLAY_DIGITS != 4
                counter_value = 0;
            }
        }
        Get_Digits_For_Display(counter_value, digits_to_display);
    }
}

/**
 * @brief  Odświeża wyświetlacz (obsługa multipleksowania)
 * @param  current_tick Aktualny czas systemowy
 * @retval None
 */
void Refresh_Display(uint32_t current_tick)
{
    if ((current_tick - last_display_refresh_time) >= DISPLAY_REFRESH_DELAY_MS)
    {
        last_display_refresh_time = current_tick;

        // Wyłącz aktualnie wyświetlaną cyfrę
        GPIO_WritePin(digits[current_display_digit_idx].PORT, digits[current_display_digit_idx].PIN, 0);

        current_display_digit_idx++;
        if (current_display_digit_idx >= DIGIT_COUNT) {
            current_display_digit_idx = 0;
        }
        Display_Digit(digits_to_display[current_display_digit_idx], current_display_digit_idx);
    }
}

/* ========================================================================== */
/* == FUNKCJA GŁÓWNA ======================================================== */
/* ========================================================================== */
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

int main(void)
{
  System_Init();

  uint32_t current_tick;

  while (1)
  {
    current_tick = systick_counter;
    
    Update_Counter(current_tick);
    Refresh_Display(current_tick);
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  while (1) {}
}
