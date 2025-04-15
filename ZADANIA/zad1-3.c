/* USER CODE BEGIN Header */

/**

******************************************************************************

* @file : main.c

* @brief : Main program body

******************************************************************************

* @attention

*

* <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.

* All rights reserved.</center></h2>

*

* This software component is licensed by ST under BSD 3-Clause license,

* the "License"; You may not use this file except in compliance with the

* License. You may obtain a copy of the License at:

* opensource.org/licenses/BSD-3-Clause

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



/* USER CODE END PTD */


#define LED_RGB_Red_Port GPIOD
#define LED_RGB_Green_Port GPIOB
#define LED_RGB_Blue_Port GPIOD

#define LED_RGB_Red_Pin GPIO_PIN_13
#define LED_RGB_Green_Pin GPIO_PIN_8
#define LED_RGB_Blue_Pin GPIO_PIN_12

#define Joystick_Port GPIOE

#define Joystick_Left_Pin GPIO_PIN_1
#define Joystick_Right_Pin GPIO_PIN_0
#define Joystick_Up_Pin GPIO_PIN_3
#define Joystick_Down_Pin GPIO_PIN_2
#define Joystick_Click_Pin GPIO_PIN_15

#define LED_Port_Diode_4_6_7 GPIOE
#define LED_Port_Diode_0_1_2_3 GPIOC
#define LED_Port_Diode_5 GPIOD

#define LED_Pin_Diode_0 GPIO_PIN_6
#define LED_Pin_Diode_1 GPIO_PIN_7
#define LED_Pin_Diode_2 GPIO_PIN_8
#define LED_Pin_Diode_3 GPIO_PIN_9
#define LED_Pin_Diode_4 GPIO_PIN_4
#define LED_Pin_Diode_5 GPIO_PIN_3
#define LED_Pin_Diode_6 GPIO_PIN_5
#define LED_Pin_Diode_7 GPIO_PIN_6
#define Element_numbers 8
#define Tick_time 300
/* Private define ------------------------------------------------------------*/

/* USER CODE BEGIN PD */

/* USER CODE END PD */



/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PM */



/* USER CODE END PM */



/* Private variables ---------------------------------------------------------*/
struct PIN_PARAMETERS
{
	GPIO_TypeDef* PORT;
	uint16_t PIN;
};


/* USER CODE BEGIN PV */



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

* @brief The application entry point.

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

MX_GPIO_Init();

/* USER CODE BEGIN 2 */



/* USER CODE END 2 */



/* Infinite loop */

/* USER CODE BEGIN WHILE */

/* joy_up = PE3
* joy_down = PE2
* joy_right = PE0
* joy_left = PE1
* joy_okey = PE15
* red = PD13
* green = PB8
* blue = PD12

*/

struct PIN_PARAMETERS Dioda0 ={LED_Port_Diode_0_1_2_3 , LED_Pin_Diode_0};
struct PIN_PARAMETERS Dioda1 ={LED_Port_Diode_0_1_2_3 , LED_Pin_Diode_1};
struct PIN_PARAMETERS Dioda2 ={LED_Port_Diode_0_1_2_3 , LED_Pin_Diode_2};
struct PIN_PARAMETERS Dioda3 ={LED_Port_Diode_0_1_2_3 , LED_Pin_Diode_3};
struct PIN_PARAMETERS Dioda4 ={LED_Port_Diode_4_6_7 , LED_Pin_Diode_4};
struct PIN_PARAMETERS Dioda5 ={LED_Port_Diode_5 , LED_Pin_Diode_5};
struct PIN_PARAMETERS Dioda6 ={LED_Port_Diode_4_6_7 , LED_Pin_Diode_6};
struct PIN_PARAMETERS Dioda7 ={LED_Port_Diode_4_6_7 , LED_Pin_Diode_7};

struct PIN_PARAMETERS Diody[] = {Dioda0,Dioda1,Dioda2,Dioda3,Dioda4,Dioda5,Dioda6,Dioda7};

int active_button_flag = 0;
int active_diode_flag = 0;
uint32_t beg_tick = 0;
uint32_t test_value;
uint32_t end_tick = 0;
int iterator = 0;



while (1)

{


		if(HAL_GPIO_ReadPin(Joystick_Port, Joystick_Click_Pin)==0){
			HAL_GPIO_WritePin (LED_RGB_Blue_Port, LED_RGB_Blue_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin (LED_RGB_Red_Port, LED_RGB_Red_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin (LED_RGB_Green_Port, LED_RGB_Green_Pin, GPIO_PIN_SET);
			active_button_flag = 1;
		}
		else if(HAL_GPIO_ReadPin(Joystick_Port, Joystick_Left_Pin)==0){
			HAL_GPIO_WritePin (LED_RGB_Green_Port, LED_RGB_Green_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LED_RGB_Blue_Port, LED_RGB_Blue_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LED_RGB_Red_Port, LED_RGB_Red_Pin, GPIO_PIN_SET);
			active_button_flag = 1;
		}

		else if(HAL_GPIO_ReadPin(Joystick_Port, Joystick_Right_Pin)==0){
			HAL_GPIO_WritePin (LED_RGB_Green_Port, LED_RGB_Green_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LED_RGB_Red_Port, LED_RGB_Red_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LED_RGB_Blue_Port, LED_RGB_Blue_Pin, GPIO_PIN_SET);
			active_button_flag = 1;
		}
		else if(HAL_GPIO_ReadPin(Joystick_Port, Joystick_Down_Pin)==0){
			HAL_GPIO_WritePin (LED_RGB_Blue_Port, LED_RGB_Blue_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LED_RGB_Red_Port, LED_RGB_Red_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LED_RGB_Green_Port, LED_RGB_Green_Pin, GPIO_PIN_SET);
			active_button_flag = 1;
		}
		else if(HAL_GPIO_ReadPin(GPIOE, Joystick_Up_Pin)==0){
			HAL_GPIO_WritePin (LED_RGB_Blue_Port, LED_RGB_Blue_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LED_RGB_Red_Port, LED_RGB_Red_Pin, GPIO_PIN_SET); //zolty
			HAL_GPIO_WritePin (LED_RGB_Green_Port, LED_RGB_Green_Pin, GPIO_PIN_SET);
			active_button_flag = 1;
		}
		else active_button_flag = 0;

		end_tick = HAL_GetTick();
		test_value= end_tick - beg_tick;

		if (iterator < 8)
		{
		if( test_value>Tick_time)
		{
		if(active_diode_flag==0 && test_value>Tick_time){
			beg_tick = end_tick;
			HAL_GPIO_WritePin(Diody[iterator].PORT,Diody[iterator].PIN,GPIO_PIN_SET);
			active_diode_flag=1;
		}
		else{
			beg_tick = end_tick;
			HAL_GPIO_WritePin(Diody[iterator].PORT,Diody[iterator].PIN,GPIO_PIN_RESET);
			active_diode_flag=0;
			iterator++;
		}
		}
		}
		else iterator = 0;

		if (active_button_flag == 0)
		{
			HAL_GPIO_WritePin (LED_RGB_Green_Port, LED_RGB_Green_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LED_RGB_Blue_Port, LED_RGB_Blue_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LED_RGB_Red_Port, LED_RGB_Red_Pin, GPIO_PIN_RESET);
		}





}


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

RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;

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


/*Configure GPIO pin Output Level */

HAL_GPIO_WritePin(LED_RGB_Green_Port, LED_RGB_Green_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED_RGB_Blue_Port, LED_RGB_Blue_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED_RGB_Red_Port, LED_RGB_Red_Pin, GPIO_PIN_RESET);







/*Konfiguracja pinów */

GPIO_InitStruct.Pin = LED_RGB_Blue_Pin | LED_RGB_Red_Pin ;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // informacja ze dioda bedzie outputem w trybie push/pull
GPIO_InitStruct.Pull = GPIO_NOPULL; // informacja że pin sam z siebie nie zmienia sygnału, to co dostanei to przepuści
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; //niska czestotliość odswiezania pinu (tak sie robi dla diod) po prawej to wartosc stała
HAL_GPIO_Init(LED_RGB_Blue_Port, &GPIO_InitStruct);


GPIO_InitStruct.Pin = LED_RGB_Green_Pin;
HAL_GPIO_Init(LED_RGB_Green_Port, &GPIO_InitStruct);


/* joystic inicjalizacja */

//czyszczenie wejscia

HAL_GPIO_WritePin(Joystick_Port, Joystick_Right_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(Joystick_Port, Joystick_Left_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(Joystick_Port, Joystick_Down_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(Joystick_Port, Joystick_Up_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(Joystick_Port, Joystick_Click_Pin, GPIO_PIN_RESET);


GPIO_InitStruct.Pin = Joystick_Right_Pin |Joystick_Left_Pin|Joystick_Down_Pin|Joystick_Up_Pin|Joystick_Click_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
HAL_GPIO_Init(Joystick_Port, &GPIO_InitStruct);


//d1 dioda init

HAL_GPIO_WritePin(LED_Port_Diode_0_1_2_3,LED_Pin_Diode_0,GPIO_PIN_RESET); //D0
HAL_GPIO_WritePin(LED_Port_Diode_0_1_2_3,LED_Pin_Diode_1,GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED_Port_Diode_0_1_2_3,LED_Pin_Diode_2,GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED_Port_Diode_0_1_2_3,LED_Pin_Diode_3,GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED_Port_Diode_4_6_7,LED_Pin_Diode_4,GPIO_PIN_RESET);//D4
HAL_GPIO_WritePin(LED_Port_Diode_5,LED_Pin_Diode_5,GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED_Port_Diode_4_6_7,LED_Pin_Diode_6,GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED_Port_Diode_4_6_7,LED_Pin_Diode_7,GPIO_PIN_RESET);//D7




GPIO_InitStruct.Pin = LED_Pin_Diode_0|LED_Pin_Diode_1|LED_Pin_Diode_2|LED_Pin_Diode_3;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
HAL_GPIO_Init(LED_Port_Diode_0_1_2_3, &GPIO_InitStruct);


GPIO_InitStruct.Pin = LED_Pin_Diode_5;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
HAL_GPIO_Init(LED_Port_Diode_5, &GPIO_InitStruct);

GPIO_InitStruct.Pin = LED_Pin_Diode_4| LED_Pin_Diode_6|  LED_Pin_Diode_7;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
HAL_GPIO_Init(LED_Port_Diode_4_6_7, &GPIO_InitStruct);

}



/* USER CODE BEGIN 4 */



/* USER CODE END 4 */



/**

* @brief This function is executed in case of error occurrence.

* @retval None

*/

void Error_Handler(void)

{

/* USER CODE BEGIN Error_Handler_Debug */

/* User can add his own implementation to report the HAL error return state */



/* USER CODE END Error_Handler_Debug */

}



#ifdef USE_FULL_ASSERT

/**

* @brief Reports the name of the source file and the source line number

* where the assert_param error has occurred.

* @param file: pointer to the source file name

* @param line: assert_param error line source number

* @retval None

*/

void assert_failed(char *file, uint32_t line)

{

/* USER CODE BEGIN 6 */

while(1);

/* User can add his own implementation to report the file name and line number,

tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

/* USER CODE END 6 */

}

#endif /* USE_FULL_ASSERT */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

