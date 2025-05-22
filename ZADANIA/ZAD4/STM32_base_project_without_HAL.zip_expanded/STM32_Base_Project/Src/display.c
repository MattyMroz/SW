/* display.c */
#include "display.h"

/* Tablica struktur przechowująca konfigurację pinów dla cyfr wyświetlacza */
const DigitPinInfo_t digits[] = {
    {DIGIT_PORT, DIGIT1_PIN_MASK}, // Indeks 0: Cyfra 1 (najbardziej na prawo)
    {DIGIT_PORT, DIGIT2_PIN_MASK}, // Indeks 1: Cyfra 2
    {DIGIT_PORT, DIGIT3_PIN_MASK}, // Indeks 2: Cyfra 3
    {DIGIT_PORT, DIGIT4_PIN_MASK}  // Indeks 3: Cyfra 4 (najbardziej na lewo)
};
const uint8_t DIGIT_COUNT = sizeof(digits) / sizeof(digits[0]);

/* Tablica segmentów dla cyfr 0-9 */
const DigitSegments_t digit_segments[] = {
    {SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK | SEG_E_PIN_MASK | SEG_F_PIN_MASK},                  // 0
    {SEG_B_PIN_MASK | SEG_C_PIN_MASK},                                                                                      // 1
    {SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_G_PIN_MASK | SEG_E_PIN_MASK | SEG_D_PIN_MASK},                                   // 2
    {SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_G_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK},                                   // 3
    {SEG_F_PIN_MASK | SEG_G_PIN_MASK | SEG_B_PIN_MASK | SEG_C_PIN_MASK},                                                    // 4
    {SEG_A_PIN_MASK | SEG_F_PIN_MASK | SEG_G_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK},                                   // 5
    {SEG_A_PIN_MASK | SEG_F_PIN_MASK | SEG_G_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK | SEG_E_PIN_MASK},                  // 6
    {SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_C_PIN_MASK},                                                                     // 7
    {SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK | SEG_E_PIN_MASK | SEG_F_PIN_MASK | SEG_G_PIN_MASK}, // 8
    {SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK | SEG_F_PIN_MASK | SEG_G_PIN_MASK}                   // 9
};
const uint8_t SEGMENT_COUNT = sizeof(digit_segments) / sizeof(digit_segments[0]);

// Inicjalizuje GPIO dla wyświetlacza
void Display_Init(void) {
    GPIO_Clock_Enable(DIGIT_PORT_RCC_EN);
    GPIO_Clock_Enable(SEG_PORT_RCC_EN);

    // Konfiguracja pinów anod cyfr
    GPIO_Pin_Setup(DIGIT_PORT, DIGIT1_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(DIGIT_PORT, DIGIT2_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(DIGIT_PORT, DIGIT3_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(DIGIT_PORT, DIGIT4_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);

    // Konfiguracja pinów segmentów
    GPIO_Pin_Setup(SEG_PORT, SEG_A_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(SEG_PORT, SEG_B_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(SEG_PORT, SEG_C_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(SEG_PORT, SEG_D_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(SEG_PORT, SEG_E_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(SEG_PORT, SEG_F_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(SEG_PORT, SEG_G_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);

    // Inicjalizacja stanów początkowych
    GPIO_WritePin(DIGIT_PORT, ALL_DIGIT_PINS_MASK, 0);
    GPIO_WritePin(SEG_PORT, ALL_SEGMENT_PINS_MASK, 0);
}

// Konwertuje liczbę na tablicę cyfr do wyświetlenia
// number Liczba do konwersji
// digits_array Tablica na cyfry (musi mieć DIGIT_COUNT elementów)
void Get_Digits_For_Display(uint16_t number, uint8_t* digits_array) {
    if (DIGIT_COUNT < 4 && number > 0) {} // Upewnij się, że digits_array ma co najmniej DIGIT_COUNT elementów

    if (number > 9999) number = 9999; // Ograniczenie do 9999 (dla 4 cyfr)

    // Rozkład liczby na cyfry - specyficzne dla 4 cyfr
    // Indeks 0 to jedności, 1 to dziesiątki, itd.
    digits_array[0] = number % 10;
    if (DIGIT_COUNT > 1) digits_array[1] = (number / 10) % 10;
    if (DIGIT_COUNT > 2) digits_array[2] = (number / 100) % 10;
    if (DIGIT_COUNT > 3) digits_array[3] = (number / 1000) % 10;

    // // Ustawienie cyfr na BLANK_DIGIT dla cyfr, które nie są używane
    // if (number == 0) {
    //     // Dla 0, wyświetl "   0" (lub odpowiednio dla DIGIT_COUNT)
    //     for(uint8_t i = 1; i < DIGIT_COUNT; ++i) {
    //         digits_array[i] = BLANK_DIGIT;
    //     }
    //     digits_array[0] = 0;
    //     return;
    // }

    // uint8_t leading_zero = 1;
    // // Iteracja od najbardziej znaczącej cyfry (np. tysiące dla 4 cyfr) w dół do dziesiątek
    // // Ta pętla jest specyficzna dla gaszenia zer od lewej, z wyjątkiem jedności
    // for(int i = DIGIT_COUNT - 1; i >= 1; i--)
    // {
    //     if(digits_array[i] == 0 && leading_zero)
    //     {
    //         digits_array[i] = BLANK_DIGIT;
    //     }
    //     else
    //     {
    //         leading_zero = 0;
    //     }
    // }
}

// Wyświetla pojedynczą cyfrę na wyświetlaczu
// digit_value Cyfra do wyświetlenia (0-9 lub BLANK_DIGIT)
// digit_position Pozycja cyfry (0-3)
void Display_Digit(uint8_t digit_value, uint8_t digit_position) {
    uint16_t segments_to_set = 0;
    // Sprawdź, czy digit_value jest poprawną cyfrą (0-9)
    if (digit_value < SEGMENT_COUNT) {
        segments_to_set = digit_segments[digit_value].SEGMENTS;
    }

    for(int i = 0; i < 7; i++) { // Zakładamy 7 segmentów (A-G)
        uint16_t current_segment_pin_mask = (1UL << (SEG_A_PIN_NUM + i));
        if ((segments_to_set >> i) & 0x01) {
             GPIO_WritePin(SEG_PORT, current_segment_pin_mask, 1);
        } else {
             GPIO_WritePin(SEG_PORT, current_segment_pin_mask, 0);
        }
    }

    // Włącz odpowiednią anodę cyfry, jeśli pozycja jest prawidłowa
    if (digit_position < DIGIT_COUNT) {
        GPIO_WritePin(digits[digit_position].PORT, digits[digit_position].PIN, 1);
    }
}