/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

// --- Struktura do przechowywania informacji o pinie LED ---
// Grupuje wskaźnik do portu i numer pinu dla łatwiejszego zarządzania
typedef struct
{
  GPIO_TypeDef* PORT; // Wskaźnik na rejestry portu GPIO (np. GPIOC)
  uint16_t      PIN;  // Maska bitowa pinu GPIO (np. GPIO_PIN_6)
} LedPinInfo_t;

// --- Struktura do przechowywania informacji o cyfrze wyświetlacza ---
// Grupuje wskaźnik do portu i numer pinu dla łatwiejszego zarządzania
typedef struct
{
  GPIO_TypeDef* PORT;
  uint16_t      PIN;
} DigitPinInfo_t;

// --- Struktura do przechowywania informacji o segmentach cyfry ---
typedef struct
{
  uint16_t SEGMENTS; // Maska bitowa aktywnych segmentów dla danej cyfry
} DigitSegments_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// === Definicje konfiguracyjne dla aplikacji ===

// --- Konfiguracja efektu LED ---
// Czas kroku w milisekundach (1000ms = sekunda na diodę)
#define LED_STEP_DELAY_MS 1000
// Opcja efektu: 1 = odbicie (D1<->D8), 0 = pętla (D1->D8->D1)
#define LED_BOUNCE 1

// --- Definicje pinów i portów dla diod D1-D8 ---
// === Definicje portów ===
#define LED_0_1_2_3_PORT GPIOC
#define LED_4_6_7_PORT GPIOE
#define LED_5_PORT GPIOD

// === Definicje pinów ===
// Port C (D1-D4)
#define LED1_PIN  GPIO_PIN_6
#define LED2_PIN  GPIO_PIN_7
#define LED3_PIN  GPIO_PIN_8
#define LED4_PIN  GPIO_PIN_9

// Port E (D5, D7, D8)
#define LED5_PIN  GPIO_PIN_4
#define LED7_PIN  GPIO_PIN_5
#define LED8_PIN  GPIO_PIN_6

// Port D (D6)
#define LED6_PIN  GPIO_PIN_3

/* ================================================== */
/* ================================================== */

// === Definicje portów JOYSTICK ===
// --- Definicje pinów i portów dla diody RGB D9 ---

// === Definicje portów ===
#define LED_RGB_RED_PORT GPIOD
#define LED_RGB_GREEN_PORT GPIOB
#define LED_RGB_BLUE_PORT GPIOD

// === Definicje pinów ===
#define LED_RGB_RED_PIN GPIO_PIN_13
#define LED_RGB_GREEN_PIN GPIO_PIN_8
#define LED_RGB_BLUE_PIN GPIO_PIN_12

// --- Definicje pinów i portów dla dżojstika SW1 ---

// === Definicje portów ===
#define JOYSTICK_PORT GPIOE

// === Definicje pinów ===
#define JOYSTICK_LEFT_PIN GPIO_PIN_1
#define JOYSTICK_RIGHT_PIN GPIO_PIN_0
#define JOYSTICK_UP_PIN GPIO_PIN_3
#define JOYSTICK_DOWN_PIN GPIO_PIN_2
#define JOYSTICK_CLICK_PIN GPIO_PIN_15

/* ================================================== */
/* ================================================== */

// === Definicje dla wyświetlacza 7-segmentowego ===
// Port aktywacji cyfr
#define DIGIT_PORT GPIOB
#define DIGIT1_PIN GPIO_PIN_5
#define DIGIT2_PIN GPIO_PIN_4
#define DIGIT3_PIN GPIO_PIN_3
#define DIGIT4_PIN GPIO_PIN_2

// Port segmentów
#define SEG_PORT GPIOG
#define SEG_A_PIN GPIO_PIN_0
#define SEG_B_PIN GPIO_PIN_1
#define SEG_C_PIN GPIO_PIN_2
#define SEG_D_PIN GPIO_PIN_3
#define SEG_E_PIN GPIO_PIN_4
#define SEG_F_PIN GPIO_PIN_5
#define SEG_G_PIN GPIO_PIN_6

// Określenie, która cyfra wyświetlacza ma być aktywna (0-3)
#define DIGIT 0 // Zmieniono na 0, czyli DIGIT1

// Czas kroku w milisekundach (1000ms = sekunda na cyfre / liczbe)
#define COUNTER_DELAY_MS 1000

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// --- Tablica struktur przechowująca konfigurację pinów dla diod D1-D8 ---
// Używana w pętli głównej do iteracji po diodach
const LedPinInfo_t leds[] = {
    {LED_0_1_2_3_PORT, LED1_PIN}, // Indeks 0: Dioda D1
    {LED_0_1_2_3_PORT, LED2_PIN}, // Indeks 1: Dioda D2
    {LED_0_1_2_3_PORT, LED3_PIN}, // Indeks 2: Dioda D3
    {LED_0_1_2_3_PORT, LED4_PIN}, // Indeks 3: Dioda D4
    {LED_4_6_7_PORT, LED5_PIN},   // Indeks 4: Dioda D5
    {LED_5_PORT, LED6_PIN},       // Indeks 5: Dioda D6
    {LED_4_6_7_PORT, LED7_PIN},   // Indeks 6: Dioda D7
    {LED_4_6_7_PORT, LED8_PIN}    // Indeks 7: Dioda D8
};

// --- Tablica struktur przechowująca konfigurację pinów dla cyfr wyświetlacza ---
// Używana do aktywacji odpowiedniej cyfry
const DigitPinInfo_t digits[] = {
    {DIGIT_PORT, DIGIT1_PIN},  // Indeks 0: Cyfra 1 (najbardziej na prawo)
    {DIGIT_PORT, DIGIT2_PIN},   // Indeks 1: Cyfra 2
    {DIGIT_PORT, DIGIT3_PIN},   // Indeks 2: Cyfra 3
    {DIGIT_PORT, DIGIT4_PIN}    // Indeks 3: Cyfra 4 (najbardziej na lewo)
};

// --- Tablica segmentów dla cyfr 0-9 ---
// Używana do wyświetlania odpowiednich cyfr na wyświetlaczu 7-segmentowym
const DigitSegments_t digit_segments[] = {
    {SEG_A_PIN | SEG_B_PIN | SEG_C_PIN | SEG_D_PIN | SEG_E_PIN | SEG_F_PIN},                // 0
    {SEG_B_PIN | SEG_C_PIN},                                                                // 1
    {SEG_A_PIN | SEG_B_PIN | SEG_G_PIN | SEG_E_PIN | SEG_D_PIN},                            // 2
    {SEG_A_PIN | SEG_B_PIN | SEG_G_PIN | SEG_C_PIN | SEG_D_PIN},                            // 3
    {SEG_F_PIN | SEG_G_PIN | SEG_B_PIN | SEG_C_PIN},                                        // 4
    {SEG_A_PIN | SEG_F_PIN | SEG_G_PIN | SEG_C_PIN | SEG_D_PIN},                            // 5
    {SEG_A_PIN | SEG_F_PIN | SEG_G_PIN | SEG_C_PIN | SEG_D_PIN | SEG_E_PIN},                // 6
    {SEG_A_PIN | SEG_B_PIN | SEG_C_PIN},                                                    // 7
    {SEG_A_PIN | SEG_B_PIN | SEG_C_PIN | SEG_D_PIN | SEG_E_PIN | SEG_F_PIN | SEG_G_PIN},    // 8
    {SEG_A_PIN | SEG_B_PIN | SEG_C_PIN | SEG_D_PIN | SEG_F_PIN | SEG_G_PIN}                 // 9
};

// Liczba diod w sekwencji
#define LED_COUNT (sizeof(leds) / sizeof(leds[0]))
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void led_sequence(); // Funkcja do obsługi sekwencji LED D1-D8
void joystick_rgb_control(); // Funkcja do obsługi dżojstika i diody RGB
void seven_segment_counter(); // Funkcja do obsługi licznika na wyświetlaczu 7-segmentowym
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init(); // Inicjalizacja GPIO dla diod LED, dżojstika i wyświetlacza 7-segmentowego
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    // --- Zadanie 1: Obsługa sekwencji LED D1-D8 ---
    led_sequence();

    // --- Zadanie 2: Obsługa dżojstika i diody RGB ---
    joystick_rgb_control();

    // --- Zadanie 3: Obsługa licznika na wyświetlaczu 7-segmentowym ---
    seven_segment_counter();

  } // Koniec pętli while(1)
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6; // 4MHz
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();

  /* ================================================== */
  /* ================================================== */

  /* === Konfiguracja pinów LED dla Portu C === */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = 0;

  GPIO_InitStruct.Pin = LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN;
  HAL_GPIO_Init(LED_0_1_2_3_PORT, &GPIO_InitStruct);

  /* === Konfiguracja pinów LED dla Portu E === */
  GPIO_InitStruct.Pin = LED5_PIN | LED7_PIN | LED8_PIN;
  HAL_GPIO_Init(LED_4_6_7_PORT, &GPIO_InitStruct);

  /* === Konfiguracja pinów LED dla Portu D === */
  GPIO_InitStruct.Pin = LED6_PIN;
  HAL_GPIO_Init(LED_5_PORT, &GPIO_InitStruct);

  /* ================================================== */
  /* ================================================== */

  /* === Konfiguracja pinów LED RGB dla Portu D i B === */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  GPIO_InitStruct.Pin = LED_RGB_RED_PIN | LED_RGB_BLUE_PIN;
  HAL_GPIO_Init(LED_RGB_RED_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LED_RGB_GREEN_PIN;
  HAL_GPIO_Init(LED_RGB_GREEN_PORT, &GPIO_InitStruct);

  /* === Konfiguracja pinów Joystick dla Portu E === */
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP; // Aktywacja rezystorów podciągających
  GPIO_InitStruct.Pin = JOYSTICK_LEFT_PIN | JOYSTICK_RIGHT_PIN | JOYSTICK_UP_PIN | JOYSTICK_DOWN_PIN | JOYSTICK_CLICK_PIN;
  HAL_GPIO_Init(JOYSTICK_PORT, &GPIO_InitStruct);

  /* ================================================== */
  /* ================================================== */

  /* === Konfiguracja pinów wyświetlacza 7-segmentowego === */
  /* === Piny aktywacyjne wyświetlacza === */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Pin = DIGIT1_PIN | DIGIT2_PIN | DIGIT3_PIN | DIGIT4_PIN;
  HAL_GPIO_Init(DIGIT_PORT, &GPIO_InitStruct);

  /* === Piny segmentów wyświetlacza=== */
  GPIO_InitStruct.Pin = SEG_A_PIN | SEG_B_PIN | SEG_C_PIN |
                       SEG_D_PIN | SEG_E_PIN | SEG_F_PIN | SEG_G_PIN;
  HAL_GPIO_Init(SEG_PORT, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */
void led_sequence()
{
  static uint8_t current_led = 0; // Indeks aktualnie świecącej diody (0-7)
  static int8_t direction = 1;   // Kierunek ruchu (1 lub -1)
  static uint32_t beg_tick = 0; // Czas rozpoczęcia kroku
  uint32_t end_tick = HAL_GetTick(); // Aktualny czas

  // --- Sprawdzenie, czy minął czas na zmianę diody ---
  if ((end_tick - beg_tick) > LED_STEP_DELAY_MS)
  {
    beg_tick = end_tick; // Aktualizacja czasu rozpoczęcia

    // --- Zgaszenie poprzedniej diody ---
    HAL_GPIO_WritePin(leds[current_led].PORT, leds[current_led].PIN, GPIO_PIN_RESET);

    // --- Aktualizacja indeksu diody ---
    if (LED_BOUNCE == 1)
    {
      // Tryb Odbicia (D1 <-> D8)
      current_led += direction;
      if (current_led == (LED_COUNT - 1))
      {
        direction = -1;
      }
      else if (current_led == 0)
      {
        direction = 1;
      }
    }
    else
    {
      // Tryb Pętli (D1 -> D8 -> D1)
      current_led++;
      if (current_led >= LED_COUNT)
      {
        current_led = 0;
      }
    }

    // --- Zapalenie nowej diody ---
    HAL_GPIO_WritePin(leds[current_led].PORT, leds[current_led].PIN, GPIO_PIN_SET);
  }
}

void joystick_rgb_control()
{
  // Odczyt stanu przycisków dżojstika
  GPIO_PinState joy_left = HAL_GPIO_ReadPin(JOYSTICK_PORT, JOYSTICK_LEFT_PIN);
  GPIO_PinState joy_right = HAL_GPIO_ReadPin(JOYSTICK_PORT, JOYSTICK_RIGHT_PIN);
  // GPIO_PinState joy_up = HAL_GPIO_ReadPin(Joystick_Port, Joystick_Up_Pin);
  GPIO_PinState joy_down = HAL_GPIO_ReadPin(JOYSTICK_PORT, JOYSTICK_DOWN_PIN);
  GPIO_PinState joy_ok = HAL_GPIO_ReadPin(JOYSTICK_PORT, JOYSTICK_CLICK_PIN);

  // Sterowanie diodą RGB
  if (joy_left == GPIO_PIN_RESET) {
    HAL_GPIO_WritePin(LED_RGB_RED_PORT, LED_RGB_RED_PIN, GPIO_PIN_SET); // Lewo = Czerwony
  } else {
    HAL_GPIO_WritePin(LED_RGB_RED_PORT, LED_RGB_RED_PIN, GPIO_PIN_RESET);
  }

  if (joy_down == GPIO_PIN_RESET) {
    HAL_GPIO_WritePin(LED_RGB_GREEN_PORT, LED_RGB_GREEN_PIN, GPIO_PIN_SET);  // Dół = Zielony
  } else {
    HAL_GPIO_WritePin(LED_RGB_GREEN_PORT, LED_RGB_GREEN_PIN, GPIO_PIN_RESET);
  }

  if (joy_right == GPIO_PIN_RESET) {
    HAL_GPIO_WritePin(LED_RGB_BLUE_PORT, LED_RGB_BLUE_PIN, GPIO_PIN_SET);  // Prawo = Niebieski
  } else {
    HAL_GPIO_WritePin(LED_RGB_BLUE_PORT, LED_RGB_BLUE_PIN, GPIO_PIN_RESET);
  }

  // Środkowy przycisk zapala wszystkie kolory
  if (joy_ok == GPIO_PIN_RESET)
  {
    HAL_GPIO_WritePin(LED_RGB_RED_PORT, LED_RGB_RED_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_RGB_GREEN_PORT, LED_RGB_GREEN_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_RGB_BLUE_PORT, LED_RGB_BLUE_PIN, GPIO_PIN_SET);
  }
}

void seven_segment_counter()
{
  static uint8_t counter = 0; // Wartość licznika (0-9)
  static uint32_t last_tick = 0; // Czas ostatniej zmiany licznika
  uint32_t current_tick = HAL_GetTick(); // Aktualny czas

  // Odczyt stanu przycisku OK joysticka
  GPIO_PinState joy_ok = HAL_GPIO_ReadPin(JOYSTICK_PORT, JOYSTICK_CLICK_PIN);

  // Sprawdzenie, czy minął czas na zmianę licznika
  if ((current_tick - last_tick) > COUNTER_DELAY_MS)
  {
    last_tick = current_tick; // Aktualizacja czasu ostatniej zmiany

    // Określenie kierunku zliczania
    if (joy_ok == GPIO_PIN_RESET) // Przycisk naciśnięty - liczenie w dół
    {
      if (counter == 0)
        counter = 9;
      else
        counter--;
    }
    else // Przycisk nie naciśnięty - liczenie w górę
    {
      if (counter == 9)
        counter = 0;
      else
        counter++;
    }

    // Wyczyszczenie wszystkich segmentów
    HAL_GPIO_WritePin(SEG_PORT, SEG_A_PIN | SEG_B_PIN | SEG_C_PIN |
                     SEG_D_PIN | SEG_E_PIN | SEG_F_PIN | SEG_G_PIN, GPIO_PIN_RESET);

    // Aktywacja odpowiedniej cyfry wyświetlacza
    // Wyłączenie wszystkich cyfr
    HAL_GPIO_WritePin(DIGIT_PORT, DIGIT1_PIN | DIGIT2_PIN | DIGIT3_PIN | DIGIT4_PIN, GPIO_PIN_RESET);

    // Wybór aktywnej cyfry wyświetlacza używając tablicy digits
    uint8_t digit_index = DIGIT; // Używamy DIGIT jako indeksu (0-3)
    if (digit_index >= 0 && digit_index < 4) // Zabezpieczenie
    {
      HAL_GPIO_WritePin(digits[digit_index].PORT, digits[digit_index].PIN, GPIO_PIN_SET);
    }

    // Wyświetlenie odpowiedniej cyfry na wyświetlaczu 7-segmentowym używając tablicy segmentów
    if (counter < 10) // Zabezpieczenie
    {
      HAL_GPIO_WritePin(SEG_PORT, digit_segments[counter].SEGMENTS, GPIO_PIN_SET);
    }
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
