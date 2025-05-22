/* system_utils.c */
#include "system_utils.h"

// FCLK = 4MHz, każda iteracja pętli zajmuje około 8-10 cykli zegara
// Można dostosować wartość poniżej w zależności od potrzeb kalibracji
#define DELAY_LOOP_CYCLES_PER_ITERATION 10  // Szacowana liczba cykli na iterację (8-10)
#define DELAY_LOOP_ITERATIONS_PER_MS (4000000 / 1000 / DELAY_LOOP_CYCLES_PER_ITERATION)  // 4MHz/1000ms/10 = 400

// Funkcja opóźniająca (blokująca)
// milliseconds Czas opóźnienia w milisekundach
void Custom_Delay_ms(volatile uint32_t milliseconds) {
    volatile uint32_t i, j;
    for (i = 0; i < milliseconds; i++) {
        for (j = 0; j < DELAY_LOOP_ITERATIONS_PER_MS; j++) {
            // asm volatile ("nop");
        }
    }
}