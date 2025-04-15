/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h" // Podstawowe funkcje HAL i prototyp Error_Handler

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

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// === Definicje konfiguracyjne dla aplikacji ===

// --- Konfiguracja efektu LED ---
// Czas kroku w milisekundach (500ms ON + 500ms OFF = 1 sekunda na diodę)
#define LED_STEP_DELAY_MS 500
// Opcja efektu: 1 = odbicie (D1<->D8), 0 = pętla (D1->D8->D1)
#define LED_BOUNCE 1
// Liczba diod w sekwencji
#define LED_COUNT 8

// --- Definicje pinów i portów dla diod D1-D8 ---
// === Definicje portów ===
#define LED_PORT_C GPIOC
#define LED_PORT_E GPIOE
#define LED_PORT_D GPIOD

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

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// --- Tablica struktur przechowująca konfigurację pinów dla diod D1-D8 ---
// Używana w pętli głównej do iteracji po diodach
const LedPinInfo_t leds[LED_COUNT] = {
    {LED_PORT_C, LED1_PIN}, // Indeks 0: Dioda D1
    {LED_PORT_C, LED2_PIN}, // Indeks 1: Dioda D2
    {LED_PORT_C, LED3_PIN}, // Indeks 2: Dioda D3
    {LED_PORT_C, LED4_PIN}, // Indeks 3: Dioda D4
    {LED_PORT_E, LED5_PIN}, // Indeks 4: Dioda D5
    {LED_PORT_D, LED6_PIN}, // Indeks 5: Dioda D6
    {LED_PORT_E, LED7_PIN}, // Indeks 6: Dioda D7
    {LED_PORT_E, LED8_PIN}  // Indeks 7: Dioda D8
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
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
  int current_led = 0; // Indeks aktualnie świecącej diody (0-7)
  int direction = 1;   // Kierunek ruchu (1 lub -1)
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
  MX_GPIO_Init(); // Inicjalizacja GPIO dla diod LED
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */

    // --- Zapalenie aktualnej diody LED (metoda HAL z użyciem tablicy struktur) ---
    HAL_GPIO_WritePin(leds[current_led].PORT, leds[current_led].PIN, GPIO_PIN_SET);

    // --- Opóźnienie (czas świecenia) ---
    HAL_Delay(LED_STEP_DELAY_MS);

    // --- Zgaszenie aktualnej diody LED (metoda bitowa z użyciem tablicy struktur) ---
    leds[current_led].PORT->BRR = leds[current_led].PIN; // Bezpośredni zapis do rejestru BRR

    // --- Opóźnienie (czas zgaszenia) ---
    HAL_Delay(LED_STEP_DELAY_MS);

    // --- Logika zmiany diody na następną ---
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
  int i; // Zmienna iteracyjna dla pętli

/* USER CODE BEGIN MX_GPIO_Init_1 */

/* USER CODE END MX_GPIO_Init_1 */

  /* === Włączenie zegarów dla używanych portów GPIO === */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /* === Ustawienie początkowego stanu pinów na niski (diody zgaszone) === */
  /* Iterujemy po tablicy struktur, aby wyłączyć wszystkie diody */
  for (i = 0; i < LED_COUNT; i++)
  {
    HAL_GPIO_WritePin(leds[i].PORT, leds[i].PIN, GPIO_PIN_RESET);
  }

  /* === Konfiguracja każdego pinu LED w pętli z użyciem pełnej struktury === */
  for (i = 0; i < LED_COUNT; i++)
  {
    GPIO_InitStruct.Pin = leds[i].PIN;              // Pobranie pinu z tablicy struktur
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;     // Tryb wyjścia Push-Pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;             // Brak rezystorów Pull-up/Pull-down
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;    // Niska prędkość
    GPIO_InitStruct.Alternate = 0;                  // Nie dotyczy trybu wyjścia (ustawione na 0 dla bezpieczeństwa)
    HAL_GPIO_Init(leds[i].PORT, &GPIO_InitStruct);  // Wywołanie inicjalizacji dla danego portu i pinu
  }

/* USER CODE BEGIN MX_GPIO_Init_2 */

/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
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
