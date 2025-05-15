/* init.c */
#include "init.h"
#include "main.h"

extern uint32_t SystemCoreClock;
extern uint8_t digits_to_display[];
extern uint16_t counter_value;

/**
  * @brief  Inicjalizuje wszystkie komponenty systemu
  * @retval None
  */
void System_Init(void)
{
  SystemInit();
  SystemCoreClockUpdate();
  My_SysTick_Init(SystemCoreClock);
  
  // Inicjalizacja komponentów
  My_EnableVddIO2();
  Display_Init();
  Joystick_Init();

  // Inicjalizacja tablicy digits_to_display wartością początkową licznika
  Get_Digits_For_Display(counter_value, digits_to_display);
} 