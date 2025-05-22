/* display.h */
#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "stm32l4xx_hal_conf.h"
#include "gpio.h"

/* Definicje pinów wyświetlacza */
#define DIGIT_PORT_RCC_EN           RCC_AHB2ENR_GPIOBEN
#define DIGIT_PORT                  GPIOB
#define DIGIT1_PIN_NUM              5  // PB5 (Jedności)
#define DIGIT2_PIN_NUM              4  // PB4 (Dziesiątki)
#define DIGIT3_PIN_NUM              3  // PB3 (Setki)
#define DIGIT4_PIN_NUM              2  // PB2 (Tysiące)

#define SEG_PORT_RCC_EN             RCC_AHB2ENR_GPIOGEN
#define SEG_PORT                    GPIOG
#define SEG_A_PIN_NUM               0  // PG0
#define SEG_B_PIN_NUM               1  // PG1
#define SEG_C_PIN_NUM               2  // PG2
#define SEG_D_PIN_NUM               3  // PG3
#define SEG_E_PIN_NUM               4  // PG4
#define SEG_F_PIN_NUM               5  // PG5
#define SEG_G_PIN_NUM               6  // PG6

#define DIGIT1_PIN_MASK             (1UL << DIGIT1_PIN_NUM)
#define DIGIT2_PIN_MASK             (1UL << DIGIT2_PIN_NUM)
#define DIGIT3_PIN_MASK             (1UL << DIGIT3_PIN_NUM)
#define DIGIT4_PIN_MASK             (1UL << DIGIT4_PIN_NUM)
#define ALL_DIGIT_PINS_MASK         (DIGIT1_PIN_MASK | DIGIT2_PIN_MASK | DIGIT3_PIN_MASK | DIGIT4_PIN_MASK)

#define SEG_A_PIN_MASK              (1UL << SEG_A_PIN_NUM)
#define SEG_B_PIN_MASK              (1UL << SEG_B_PIN_NUM)
#define SEG_C_PIN_MASK              (1UL << SEG_C_PIN_NUM)
#define SEG_D_PIN_MASK              (1UL << SEG_D_PIN_NUM)
#define SEG_E_PIN_MASK              (1UL << SEG_E_PIN_NUM)
#define SEG_F_PIN_MASK              (1UL << SEG_F_PIN_NUM)
#define SEG_G_PIN_MASK              (1UL << SEG_G_PIN_NUM)
#define ALL_SEGMENT_PINS_MASK       (SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK | SEG_E_PIN_MASK | SEG_F_PIN_MASK | SEG_G_PIN_MASK)

#define BLANK_DIGIT                 10   // Wartość oznaczająca pustą cyfrę (musi być >= NUM_SEGMENT_PATTERNS)
#define DISPLAY_REFRESH_DELAY_MS    2

/* Struktury danych związane z wyświetlaczem */
// Struktura do przechowywania informacji o cyfrze wyświetlacza
typedef struct
{
  GPIO_TypeDef *PORT;
  uint16_t PIN;
} DigitPinInfo_t;

// Struktura do przechowywania informacji o segmentach cyfry
typedef struct
{
  uint16_t SEGMENTS; // Maska bitowa aktywnych segmentów dla danej cyfry
} DigitSegments_t;

/* Deklaracje zmiennych zewnętrznych */
extern const DigitPinInfo_t digits[];
extern const DigitSegments_t digit_segments[];
extern const uint8_t DIGIT_COUNT;
extern const uint8_t SEGMENT_COUNT;

// Inicjalizuje GPIO dla wyświetlacza
void Display_Init(void);

// Konwertuje liczbę na tablicę cyfr do wyświetlenia
// number Liczba do konwersji
// digits_array Tablica na cyfry (musi mieć DIGIT_COUNT elementów)
void Get_Digits_For_Display(uint16_t number, uint8_t* digits_array);

// Wyświetla pojedynczą cyfrę na wyświetlaczu
// digit_value Cyfra do wyświetlenia (0-9 lub BLANK_DIGIT)
// digit_position Pozycja cyfry (0-3)
void Display_Digit(uint8_t digit_value, uint8_t digit_position);

#endif /* __DISPLAY_H */