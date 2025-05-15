/* system_utils.c */
#include "system_utils.h"

/* Zmienne globalne do obsługi funkcji systemowych */
volatile uint32_t systick_counter = 0;

/**
  * @brief  Inicjalizuje licznik SysTick
  * @param  SystemCoreClockValue Wartość zegara systemowego
  * @retval None
  */
void My_SysTick_Init(uint32_t SystemCoreClockValue)
{
    SysTick->LOAD = (SystemCoreClockValue / 1000U) - 1UL; // Przerwanie co 1ms
    SysTick->VAL = 0UL;
    SysTick->CTRL = (1UL << 2) | (1UL << 1) | (1UL << 0); // Włącz SysTick, Włącz przerwanie, Użyj zegara procesora
}

// FCLK = 4MHz, każda iteracja pętli zajmuje około 8-10 cykli zegara
// Można dostosować wartość poniżej w zależności od potrzeb kalibracji
#define DELAY_LOOP_CYCLES_PER_ITERATION 10  // Szacowana liczba cykli na iterację (8-10)
#define DELAY_LOOP_ITERATIONS_PER_MS (4000000 / 1000 / DELAY_LOOP_CYCLES_PER_ITERATION)  // 4MHz/1000ms/10 = 400

/**
  * @brief  Funkcja opóźnienia (blokująca)
  * @param  milliseconds Czas opóźnienia w milisekundach
  * @retval None
  */
void Custom_Delay_ms(volatile uint32_t milliseconds) {
    volatile uint32_t i, j;
    for (i = 0; i < milliseconds; i++) {
        for (j = 0; j < DELAY_LOOP_ITERATIONS_PER_MS; j++) {
            asm volatile ("nop");
        }
    }
} 