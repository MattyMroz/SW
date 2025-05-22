/* gpio.h */
#ifndef __GPIO_H
#define __GPIO_H

#include "stm32l4xx_hal_conf.h"

// Włącza zegar dla portu GPIO
// GPIO_Port_Mask Maska bitowa dla zegara portu (np. RCC_AHB2ENR_GPIOBEN)
void GPIO_Clock_Enable(uint32_t GPIO_Port_Mask);

// Konfiguruje pin GPIO
// GPIOx_INSTANCE Wskaźnik do instancji GPIO (np. GPIOB)
// PinNumber Numer pinu (0-15)
// Mode Tryb pracy pinu (INPUT, OUTPUT, ALTERNATE, ANALOG)
// OutputType Typ wyjścia (PP, OD)
// Speed Prędkość wyjścia (LOW, MEDIUM, HIGH, VHIGH)
// Pull Podciąganie (NONE, UP, DOWN)
void GPIO_Pin_Setup(GPIO_TypeDef* GPIOx_INSTANCE, uint16_t PinNumber, uint32_t Mode, uint32_t OutputType, uint32_t Speed, uint32_t Pull);

// Ustawia stan pinu GPIO
// GPIOx_INSTANCE Wskaźnik do instancji GPIO (np. GPIOB)
// PinMask Maska bitowa pinu (1<<PIN_NUM)
// PinState Wartość 0 lub 1
void GPIO_WritePin(GPIO_TypeDef* GPIOx_INSTANCE, uint16_t PinMask, uint8_t PinState);

// Odczytuje stan pinu GPIO
// GPIOx_INSTANCE Wskaźnik do instancji GPIO (np. GPIOB)
// PinMask Maska bitowa pinu (1<<PIN_NUM)
// Zwraca stan pinu (0 lub 1)
uint8_t GPIO_ReadPin(GPIO_TypeDef* GPIOx_INSTANCE, uint16_t PinMask);

// Włącza zasilanie VDDIO2 (PG[15:2])
void My_EnableVddIO2(void);

#endif /* __GPIO_H */