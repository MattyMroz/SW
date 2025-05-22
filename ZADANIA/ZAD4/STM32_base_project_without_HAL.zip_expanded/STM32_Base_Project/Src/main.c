/* main.c */
#include <stdint.h>
#include "main.h"
#include "init.h"

/* ========================================================================== */
/* == DEFINICJE CZASÓW OPÓŹNIEŃ ============================================= */
/* ========================================================================== */
#define BASE_LOOP_DELAY_MS         1     // Podstawowe opóźnienie pętli (bardzo krótkie dla responsywności)

#define DISPLAY_REFRESH_INTERVAL_MS 5    // Częstotliwość odświeżania wyświetlacza
#define DISPLAY_CYCLES             (DISPLAY_REFRESH_INTERVAL_MS / BASE_LOOP_DELAY_MS)

#define JOYSTICK_POLL_INTERVAL_MS  20    // Częstotliwość odpytywania joysticka
#define JOYSTICK_CYCLES            (JOYSTICK_POLL_INTERVAL_MS / BASE_LOOP_DELAY_MS)

#define COUNTER_UPDATE_INTERVAL_MS 1000  // Czas między aktualizacjami licznika
#define COUNTER_CYCLES             (COUNTER_UPDATE_INTERVAL_MS / BASE_LOOP_DELAY_MS)

/* ========================================================================== */
/* == ZMIENNE GLOBALNE/STATYCZNE ============================================ */
/* ========================================================================== */
extern uint32_t SystemCoreClock;
uint16_t counter_value = 0;
static uint8_t current_display_digit_idx = 0; // Indeks aktualnie wyświetlanej cyfry (0 do DIGIT_COUNT-1)
// Tablica przechowująca cyfry do wyświetlenia (jedności, dziesiątki, etc.)
uint8_t digits_to_display[4] = {0, BLANK_DIGIT, BLANK_DIGIT, BLANK_DIGIT}; // Inicjalizacja dla 4 cyfr

// Zmienne do obsługi prostego debouncingu joysticka
static uint8_t joy_ok_state = 1;            // 1 = zwolniony (stan początkowy), 0 = wciśnięty
static uint8_t joy_ok_debounce_counter = 0; // Licznik dla debouncingu

// Liczniki cykli dla różnych operacji
static uint16_t display_cycle_counter = 0;
static uint16_t joystick_cycle_counter = 0;
static uint16_t counter_cycle_counter = 0;

// Odczytuje i przetwarza stan joysticka z prostym debouncingiem
void Process_Joystick(void)
{
    uint8_t raw_state = Joystick_Get_OK_Raw_State();

    if (raw_state == joy_ok_state) {
        // Stan stabilny - resetujemy licznik debounce
        joy_ok_debounce_counter = 0;
    } else {
        // Stan się zmienił - inkrementujemy licznik debounce
        joy_ok_debounce_counter++;

        // Jeśli stan jest stabilny przez kilka odczytów, akceptujemy go jako nowy stan
        if (joy_ok_debounce_counter >= 3) {
            joy_ok_state = raw_state;
            joy_ok_debounce_counter = 0;
        }
    }
}

// Aktualizuje wartość licznika na podstawie zapamiętanego stanu joysticka
void Update_Counter_Logic(void)
{
    if (joy_ok_state == 0) { // Przycisk wciśnięty
        if (counter_value == 0) {
            counter_value = 9999;
        } else {
            counter_value--;
        }
    } else { // Przycisk zwolniony
        counter_value++;
        if (counter_value > 9999) {
            counter_value = 0;
        }
    }

    Get_Digits_For_Display(counter_value, digits_to_display);
}

// Odświeża wyświetlacz (obsługa multipleksowania)
void Refresh_Display_Logic(void)
{
    // Wyłącz aktualnie wyświetlaną cyfrę
    GPIO_WritePin(digits[current_display_digit_idx].PORT, digits[current_display_digit_idx].PIN, 0);

    // Przejdź do następnej cyfry
    current_display_digit_idx++;
    if (current_display_digit_idx >= DIGIT_COUNT) {
        current_display_digit_idx = 0;
    }

    // Wyświetl nową cyfrę
    Display_Digit(digits_to_display[current_display_digit_idx], current_display_digit_idx);
}

/* ========================================================================== */
/* == FUNKCJA GŁÓWNA ======================================================== */
/* ========================================================================== */
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

int main(void)
{
    System_Init();

    while (1)
    {
        Custom_Delay_ms(BASE_LOOP_DELAY_MS);

        if (display_cycle_counter >= DISPLAY_CYCLES) {
            Refresh_Display_Logic();
            display_cycle_counter = 0;
        }

        if (joystick_cycle_counter >= JOYSTICK_CYCLES) {
            Process_Joystick();
            joystick_cycle_counter = 0;
        }

        if (counter_cycle_counter >= COUNTER_CYCLES) {
            Update_Counter_Logic();
            counter_cycle_counter = 0;
        }

        display_cycle_counter++;
        joystick_cycle_counter++;
        counter_cycle_counter++;
    }
}

// Ta funkcja jest wykonywana w przypadku wystąpienia błędu
void Error_Handler(void)
{
    while (1) {}
}
