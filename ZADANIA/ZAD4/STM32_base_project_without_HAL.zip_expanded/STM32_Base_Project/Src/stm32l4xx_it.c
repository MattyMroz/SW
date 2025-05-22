// stm32l4xx_it.c
#include "main.h"

// Obsługa przerwania NMI (Non-Maskable Interrupt)
void NMI_Handler(void)
{
  while (1)
  {
  }
}

// Obsługa przerwania Hard Fault (błąd krytyczny)
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

// Obsługa przerwania Memory Management (zarządzanie pamięcią)
void MemManage_Handler(void)
{
  while (1)
  {
  }
}

// Obsługa przerwania Bus Fault (błąd magistrali)
void BusFault_Handler(void)
{
  while (1)
  {
  }
}

// Obsługa przerwania Usage Fault (błąd użycia)
void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

// Obsługa przerwania SVCall (System Service Call)
void SVC_Handler(void)
{
}

// Obsługa przerwania Debug Monitor
void DebugMon_Handler(void)
{
}

// Obsługa przerwania PendSV (Pendable Service Request)
void PendSV_Handler(void)
{
}