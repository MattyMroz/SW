/* gpio.c */
#include "gpio.h"

/**
  * @brief  Włącza zegar dla portu GPIO
  * @param  GPIO_Port_Mask Maska bitowa dla zegara portu (np. RCC_AHB2ENR_GPIOBEN)
  * @retval None
  */
void GPIO_Clock_Enable(uint32_t GPIO_Port_Mask) {
    RCC->AHB2ENR |= GPIO_Port_Mask;
    volatile uint32_t dummy_read = RCC->AHB2ENR; // Opóźnienie po włączeniu zegara
    (void)dummy_read;
}

/**
  * @brief  Konfiguruje pin GPIO
  * @param  GPIOx_INSTANCE Wskaźnik do instancji GPIO (np. GPIOB)
  * @param  PinNumber Numer pinu (0-15)
  * @param  Mode Tryb pracy pinu (INPUT, OUTPUT, ALTERNATE, ANALOG)
  * @param  OutputType Typ wyjścia (PP, OD)
  * @param  Speed Prędkość wyjścia (LOW, MEDIUM, HIGH, VHIGH)
  * @param  Pull Podciąganie (NONE, UP, DOWN)
  * @retval None
  */
void GPIO_Pin_Setup(GPIO_TypeDef* GPIOx_INSTANCE, uint16_t PinNumber, uint32_t Mode, uint32_t OutputType, uint32_t Speed, uint32_t Pull) {
    uint32_t moder_pos = PinNumber * 2;
    uint32_t ospeedr_pos = PinNumber * 2;
    uint32_t pupdr_pos = PinNumber * 2;

    GPIOx_INSTANCE->MODER &= ~(0x3UL << moder_pos);
    GPIOx_INSTANCE->MODER |= (Mode << moder_pos);

    if ((Mode == GPIO_MODER_MODE_OUTPUT) || (Mode == GPIO_MODER_MODE_ALTERNATE)) {
        GPIOx_INSTANCE->OTYPER &= ~(1UL << PinNumber);
        GPIOx_INSTANCE->OTYPER |= (OutputType << PinNumber);

        GPIOx_INSTANCE->OSPEEDR &= ~(0x3UL << ospeedr_pos);
        GPIOx_INSTANCE->OSPEEDR |= (Speed << ospeedr_pos);
    }

    GPIOx_INSTANCE->PUPDR &= ~(0x3UL << pupdr_pos);
    GPIOx_INSTANCE->PUPDR |= (Pull << pupdr_pos);
}

/**
  * @brief  Ustawia stan pinu GPIO
  * @param  GPIOx_INSTANCE Wskaźnik do instancji GPIO (np. GPIOB)
  * @param  PinMask Maska bitowa pinu (1<<PIN_NUM)
  * @param  PinState Wartość 0 lub 1
  * @retval None
  */
void GPIO_WritePin(GPIO_TypeDef* GPIOx_INSTANCE, uint16_t PinMask, uint8_t PinState) {
    if (PinState != 0) { // Ustaw bit
        GPIOx_INSTANCE->BSRR = (uint32_t)PinMask;
    } else { // Resetuj bit
        GPIOx_INSTANCE->BSRR = (uint32_t)PinMask << 16U;
    }
}

/**
  * @brief  Odczytuje stan pinu GPIO
  * @param  GPIOx_INSTANCE Wskaźnik do instancji GPIO (np. GPIOB)
  * @param  PinMask Maska bitowa pinu (1<<PIN_NUM)
  * @retval Stan pinu (0 lub 1)
  */
uint8_t GPIO_ReadPin(GPIO_TypeDef* GPIOx_INSTANCE, uint16_t PinMask) {
    return (GPIOx_INSTANCE->IDR & PinMask) ? 1 : 0;
}

/**
  * @brief  Włącza zasilanie VDDIO2 (PG[15:2])
  * @retval None
  */
void My_EnableVddIO2(void) {
    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN; // Włącz zegar dla PWR
    volatile uint32_t dummy_read = RCC->APB1ENR1; // Opóźnienie
    (void)dummy_read;
    PWR->CR2 |= PWR_CR2_IOSV; // Ustaw bit IOSV (Włącza zasilanie VDDIO2 dla PG[15:2])
} 