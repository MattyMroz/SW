/* init.c */
#include "init.h"
#include "main.h"

extern uint32_t SystemCoreClock;
extern uint8_t digits_to_display[];
extern uint16_t counter_value;

// Inicjalizuje wszystkie komponenty systemu
void System_Init(void)
{
  // Inicjalizacja komponentów
  My_EnableVddIO2();
  Display_Init();
  Joystick_Init();

  // Inicjalizacja tablicy digits_to_display wartością początkową licznika
  Get_Digits_For_Display(counter_value, digits_to_display);
}