/* main.c */
#include <stdint.h>

/* ========================================================================== */
/* == DEFINICJE SPRZĘTOWE (REJESTRY, ADRESY, MASKI) ======================== */
/* ========================================================================== */

/* Adresy bazowe peryferiów (część może być w system_stm32l4xx.c) */
#define PERIPH_BASE           (0x40000000UL)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x08000000UL)
#define APB1PERIPH_BASE       (PERIPH_BASE) // Dla PWR

#ifndef RCC_BASE
    #define RCC_BASE          (AHB1PERIPH_BASE + 0x1000UL)
#endif
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000UL)

#define GPIOB_BASE            (AHB2PERIPH_BASE + 0x0400UL)
#define GPIOE_BASE            (AHB2PERIPH_BASE + 0x1000UL)
#define GPIOG_BASE            (AHB2PERIPH_BASE + 0x1800UL)

#define SCS_BASE              (0xE000E000UL)
#define SysTick_BASE          (SCS_BASE +  0x0010UL)

/* Struktury rejestrów (RCC i SCB są w system_stm32l4xx.c) */
#ifndef RCC_TypeDef_DEFINED
#define RCC_TypeDef_DEFINED
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t ICSCR;
  volatile uint32_t CFGR;
  volatile uint32_t PLLCFGR;
  volatile uint32_t PLLSAI1CFGR;
  volatile uint32_t PLLSAI2CFGR;
  volatile uint32_t CIER;
  volatile uint32_t CIFR;
  volatile uint32_t CICR;
  uint32_t      RESERVED0;
  volatile uint32_t AHB1RSTR;
  volatile uint32_t AHB2RSTR;
  volatile uint32_t AHB3RSTR;
  uint32_t      RESERVED1;
  volatile uint32_t APB1RSTR1;
  volatile uint32_t APB1RSTR2;
  volatile uint32_t APB2RSTR;
  uint32_t      RESERVED2;
  volatile uint32_t AHB1ENR;
  volatile uint32_t AHB2ENR;
  volatile uint32_t AHB3ENR;
  uint32_t      RESERVED3;
  volatile uint32_t APB1ENR1;
  volatile uint32_t APB1ENR2;
  volatile uint32_t APB2ENR;
} RCC_TypeDef;
#endif

typedef struct
{
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFR[2];
  volatile uint32_t BRR;
  volatile uint32_t ASCR;
} GPIO_TypeDef;

typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CR3;
  volatile uint32_t CR4;
  volatile uint32_t SR1;
  volatile uint32_t SR2;
  volatile uint32_t SCR;
  uint32_t      RESERVED;
  volatile uint32_t PUCRA;
  volatile uint32_t PDCRA;
  volatile uint32_t PUCRB;
  volatile uint32_t PDCRB;
  volatile uint32_t PUCRC;
  volatile uint32_t PDCRC;
  volatile uint32_t PUCRD;
  volatile uint32_t PDCRD;
  volatile uint32_t PUCRE;
  volatile uint32_t PDCRE;
  volatile uint32_t PUCRF;
  volatile uint32_t PDCRF;
  volatile uint32_t PUCRG;
  volatile uint32_t PDCRG;
  volatile uint32_t PUCRH;
  volatile uint32_t PDCRH;
  volatile uint32_t PUCRI;
  volatile uint32_t PDCRI;
} PWR_TypeDef;

typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile  uint32_t CALIB;
} SysTick_Type;

#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define PWR                 ((PWR_TypeDef *) PWR_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)
#define SysTick             ((SysTick_Type   *) SysTick_BASE)

/* Maski bitów dla RCC */
#define RCC_APB1ENR1_PWREN_Pos      (28U)
#define RCC_APB1ENR1_PWREN          (1UL << RCC_APB1ENR1_PWREN_Pos)
#define RCC_AHB2ENR_GPIOBEN_Pos     (1U)
#define RCC_AHB2ENR_GPIOBEN         (1UL << RCC_AHB2ENR_GPIOBEN_Pos)
#define RCC_AHB2ENR_GPIOEEN_Pos     (4U)
#define RCC_AHB2ENR_GPIOEEN         (1UL << RCC_AHB2ENR_GPIOEEN_Pos)
#define RCC_AHB2ENR_GPIOGEN_Pos     (6U)
#define RCC_AHB2ENR_GPIOGEN         (1UL << RCC_AHB2ENR_GPIOGEN_Pos)

/* Maski bitów dla PWR */
#define PWR_CR2_IOSV_Pos            (9U)
#define PWR_CR2_IOSV                (1UL << PWR_CR2_IOSV_Pos)

/* Maski bitów dla GPIOx_MODER */
#define GPIO_MODER_MODE_INPUT       (0x00UL)
#define GPIO_MODER_MODE_OUTPUT      (0x01UL)
#define GPIO_MODER_MODE_ALTERNATE   (0x02UL)
#define GPIO_MODER_MODE_ANALOG      (0x03UL)

/* Maski bitów dla GPIOx_OTYPER */
#define GPIO_OTYPER_OT_PP           (0x00UL)
#define GPIO_OTYPER_OT_OD           (0x01UL)

/* Maski bitów dla GPIOx_OSPEEDR */
#define GPIO_OSPEEDR_OSPEED_LOW     (0x00UL)
#define GPIO_OSPEEDR_OSPEED_MEDIUM  (0x01UL)
#define GPIO_OSPEEDR_OSPEED_HIGH    (0x02UL)
#define GPIO_OSPEEDR_OSPEED_VHIGH   (0x03UL)

/* Maski bitów dla GPIOx_PUPDR */
#define GPIO_PUPDR_PUPD_NONE        (0x00UL)
#define GPIO_PUPDR_PUPD_UP          (0x01UL)
#define GPIO_PUPDR_PUPD_DOWN        (0x02UL)

/* Definicje pinów wyświetlacza i joysticka */
#define DIGIT_PORT_RCC_EN           RCC_AHB2ENR_GPIOBEN
#define DIGIT_PORT                  GPIOB
#define DIGIT1_PIN_NUM              5  // PB5 (Jedności)
#define DIGIT2_PIN_NUM              4  // PB4 (Dziesiątki)
#define DIGIT3_PIN_NUM              3  // PB3 (Setki)
#define DIGIT4_PIN_NUM              2  // PB2 (Tysiące)

#define SEG_PORT_RCC_EN             RCC_AHB2ENR_GPIOGEN
#define SEG_PORT                    GPIOG
#define SEG_A_PIN_NUM               0  // PG0
#define SEG_B_PIN_NUM               1  // PG1
#define SEG_C_PIN_NUM               2  // PG2
#define SEG_D_PIN_NUM               3  // PG3
#define SEG_E_PIN_NUM               4  // PG4
#define SEG_F_PIN_NUM               5  // PG5
#define SEG_G_PIN_NUM               6  // PG6

#define JOY_OK_PORT_RCC_EN          RCC_AHB2ENR_GPIOEEN
#define JOY_OK_PORT                 GPIOE
#define JOY_OK_PIN_NUM              15 // PE15

#define DIGIT1_PIN_MASK             (1UL << DIGIT1_PIN_NUM)
#define DIGIT2_PIN_MASK             (1UL << DIGIT2_PIN_NUM)
#define DIGIT3_PIN_MASK             (1UL << DIGIT3_PIN_NUM)
#define DIGIT4_PIN_MASK             (1UL << DIGIT4_PIN_NUM)
#define ALL_DIGIT_PINS_MASK         (DIGIT1_PIN_MASK | DIGIT2_PIN_MASK | DIGIT3_PIN_MASK | DIGIT4_PIN_MASK)

#define SEG_A_PIN_MASK              (1UL << SEG_A_PIN_NUM)
#define SEG_B_PIN_MASK              (1UL << SEG_B_PIN_NUM)
#define SEG_C_PIN_MASK              (1UL << SEG_C_PIN_NUM)
#define SEG_D_PIN_MASK              (1UL << SEG_D_PIN_NUM)
#define SEG_E_PIN_MASK              (1UL << SEG_E_PIN_NUM)
#define SEG_F_PIN_MASK              (1UL << SEG_F_PIN_NUM)
#define SEG_G_PIN_MASK              (1UL << SEG_G_PIN_NUM)
#define ALL_SEGMENT_PINS_MASK       (SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK | SEG_E_PIN_MASK | SEG_F_PIN_MASK | SEG_G_PIN_MASK)

#define JOY_OK_PIN_MASK             (1UL << JOY_OK_PIN_NUM)

#define COUNTER_UPDATE_DELAY_MS         1000
#define DISPLAY_REFRESH_DELAY_MS        2
#define JOY_OK_DEBOUNCE_TIME_MS         50
#define JOY_OK_POLL_INTERVAL_MS         10   // Interwał odpytywania joysticka
#define BLANK_DIGIT                     10   // Wartość oznaczająca pustą cyfrę

/* ========================================================================== */
/* == ZMIENNE GLOBALNE/STATYCZNE ============================================ */
/* ========================================================================== */
extern uint32_t SystemCoreClock;
volatile uint32_t systick_counter = 0;

static uint16_t counter_value = 0;
// static uint8_t count_direction_up = 1; // USUNIĘTE - nie jest już potrzebne
static uint8_t current_display_digit_idx = 0; // 0=jedności, 1=dziesiątki, 2=setki, 3=tysiące
static uint8_t digits_to_display[4] = {0, BLANK_DIGIT, BLANK_DIGIT, BLANK_DIGIT}; // Jedności, Dziesiątki, Setki, Tysiące

static uint32_t last_counter_update_time = 0;
static uint32_t last_display_refresh_time = 0;
static uint32_t last_joy_ok_poll_time = 0;
static uint8_t  joy_ok_prev_stable_state = 1; // 1 = zwolniony (stan początkowy), 0 = wciśnięty
static uint8_t  joy_ok_last_raw_state = 1;    // Zakładamy początkowo zwolniony
static uint32_t joy_ok_last_change_time = 0;  // Czas ostatniej zmiany stanu surowego joysticka

const uint16_t digit_segments_map[10] = { // Indeks 0-9 dla cyfr 0-9
    (SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK | SEG_E_PIN_MASK | SEG_F_PIN_MASK),             // 0
    (SEG_B_PIN_MASK | SEG_C_PIN_MASK),                                                                                // 1
    (SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_G_PIN_MASK | SEG_E_PIN_MASK | SEG_D_PIN_MASK),                            // 2
    (SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_G_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK),                            // 3
    (SEG_F_PIN_MASK | SEG_G_PIN_MASK | SEG_B_PIN_MASK | SEG_C_PIN_MASK),                                              // 4
    (SEG_A_PIN_MASK | SEG_F_PIN_MASK | SEG_G_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK),                            // 5
    (SEG_A_PIN_MASK | SEG_F_PIN_MASK | SEG_G_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK | SEG_E_PIN_MASK),            // 6
    (SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_C_PIN_MASK),                                                                // 7
    (SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK | SEG_E_PIN_MASK | SEG_F_PIN_MASK | SEG_G_PIN_MASK), // 8
    (SEG_A_PIN_MASK | SEG_B_PIN_MASK | SEG_C_PIN_MASK | SEG_D_PIN_MASK | SEG_F_PIN_MASK | SEG_G_PIN_MASK)             // 9
};

const uint16_t digit_anode_pins_mask[4] = {
    DIGIT1_PIN_MASK,  // Jedności - DIG1 (PB5)
    DIGIT2_PIN_MASK,  // Dziesiątki - DIG2 (PB4)
    DIGIT3_PIN_MASK,  // Setki - DIG3 (PB3)
    DIGIT4_PIN_MASK   // Tysiące - DIG4 (PB2)
};

/* ========================================================================== */
/* == FUNKCJE POMOCNICZE ==================================================== */
/* ========================================================================== */
void My_SysTick_Init(uint32_t SystemCoreClockValue)
{
    SysTick->LOAD = (SystemCoreClockValue / 1000U) - 1UL; // Przerwanie co 1ms
    SysTick->VAL = 0UL;
    SysTick->CTRL = (1UL << 2) | (1UL << 1) | (1UL << 0); // Włącz SysTick, Włącz przerwanie, Użyj zegara procesora
}

#define DELAY_LOOP_ITERATIONS_PER_MS 400 // Uwaga: To jest przybliżone i zależne od CPU
void Custom_Delay_ms(volatile uint32_t milliseconds) {
    volatile uint32_t i, j;
    for (i = 0; i < milliseconds; i++) {
        for (j = 0; j < DELAY_LOOP_ITERATIONS_PER_MS; j++) {
            asm volatile ("nop");
        }
    }
}

void GPIO_Clock_Enable(uint32_t GPIO_Port_Mask) {
    RCC->AHB2ENR |= GPIO_Port_Mask;
    volatile uint32_t dummy_read = RCC->AHB2ENR; // Opóźnienie po włączeniu zegara
    (void)dummy_read;
}

void My_EnableVddIO2(void) {
    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN; // Włącz zegar dla PWR
    volatile uint32_t dummy_read = RCC->APB1ENR1; // Opóźnienie
    (void)dummy_read;
    PWR->CR2 |= PWR_CR2_IOSV; // Ustaw bit IOSV (Włącza zasilanie VDDIO2 dla PG[15:2])
}


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

void GPIO_WritePin(GPIO_TypeDef* GPIOx_INSTANCE, uint16_t PinMask, uint8_t PinState) {
    if (PinState != 0) { // Ustaw bit
        GPIOx_INSTANCE->BSRR = (uint32_t)PinMask;
    } else { // Resetuj bit
        GPIOx_INSTANCE->BSRR = (uint32_t)PinMask << 16U;
    }
}

uint8_t GPIO_ReadPin(GPIO_TypeDef* GPIOx_INSTANCE, uint16_t PinMask) {
    return (GPIOx_INSTANCE->IDR & PinMask) ? 1 : 0;
}

void GPIO_Init_Display_Joystick(void) {
    My_EnableVddIO2(); // Włączenie zasilania VDDIO2 (jeśli używane są piny PG[15:2]). PG[6:0] są na VDDIO1.

    GPIO_Clock_Enable(DIGIT_PORT_RCC_EN); // GPIOB
    GPIO_Clock_Enable(SEG_PORT_RCC_EN);   // GPIOG
    GPIO_Clock_Enable(JOY_OK_PORT_RCC_EN); // GPIOE

    // Konfiguracja pinów anod cyfr (Wyjście, Push-Pull, Niska prędkość, Bez Pull)
    GPIO_Pin_Setup(DIGIT_PORT, DIGIT1_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(DIGIT_PORT, DIGIT2_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(DIGIT_PORT, DIGIT3_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(DIGIT_PORT, DIGIT4_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);

    // Konfiguracja pinów segmentów (Wyjście, Push-Pull, Niska prędkość, Bez Pull)
    GPIO_Pin_Setup(SEG_PORT, SEG_A_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(SEG_PORT, SEG_B_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(SEG_PORT, SEG_C_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(SEG_PORT, SEG_D_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(SEG_PORT, SEG_E_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(SEG_PORT, SEG_F_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);
    GPIO_Pin_Setup(SEG_PORT, SEG_G_PIN_NUM, GPIO_MODER_MODE_OUTPUT, GPIO_OTYPER_OT_PP, GPIO_OSPEEDR_OSPEED_LOW, GPIO_PUPDR_PUPD_NONE);

    // Konfiguracja pinu Joystick OK (Wejście, Pull-Up)
    GPIO_Pin_Setup(JOY_OK_PORT, JOY_OK_PIN_NUM, GPIO_MODER_MODE_INPUT, 0 /*OTYPE N/A*/, 0 /*OSPEED N/A*/, GPIO_PUPDR_PUPD_UP);

    // Inicjalizacja pinów wyświetlacza (wszystkie anody wyłączone, wszystkie segmenty wyłączone)
    GPIO_WritePin(DIGIT_PORT, ALL_DIGIT_PINS_MASK, 0); // Wyłącz wszystkie anody cyfr
    GPIO_WritePin(SEG_PORT, ALL_SEGMENT_PINS_MASK, 0); // Wyłącz wszystkie segmenty
}

void Get_Digits_For_Display(uint16_t number, uint8_t* digits_array) {
    if (number > 9999) number = 9999; // Ograniczenie do 9999

    digits_array[0] = number % 10;          // Jedności
    digits_array[1] = (number / 10) % 10;   // Dziesiątki
    digits_array[2] = (number / 100) % 10;  // Setki
    digits_array[3] = (number / 1000) % 10; // Tysiące

    if (number == 0) {
        digits_array[3] = BLANK_DIGIT;
        digits_array[2] = BLANK_DIGIT;
        digits_array[1] = BLANK_DIGIT;
        digits_array[0] = 0;  // Wyświetl "   0"
        return;
    }

    uint8_t leading_zero = 1;
    // Iteracja od najbardziej znaczącej cyfry (tysiące) w dół do dziesiątek, wygaszając wiodące zera
    for(int i = 3; i >= 1; i--) // Sprawdź tysiące, setki, dziesiątki
    {
        if(digits_array[i] == 0 && leading_zero)
        {
            digits_array[i] = BLANK_DIGIT; // Ustaw jako pustą
        }
        else
        {
            leading_zero = 0; // Znaleziono cyfrę różną od zera lub zero, które nie jest wiodące
        }
    }
}

void Display_Digit(uint8_t digit_value, uint8_t digit_position) {
    // GPIO_WritePin(DIGIT_PORT, ALL_DIGIT_PINS_MASK, 0); // Upewnij się, że wszystkie anody są wyłączone (robione przez wywołującego przez wyłączenie poprzedniej)

    uint16_t segments_to_set = 0;
    if (digit_value < 10) { // Poprawna cyfra 0-9
        segments_to_set = digit_segments_map[digit_value];
    }

    // Oryginalna logika ustawiania segmentów:
    // Zakładając, że SEG_A_PIN_NUM to 0, a segmenty A-G są na kolejnych pinach PG0-PG6
    for(int i=0; i < 7; i++) {
        uint16_t current_segment_pin_mask = (1UL << (SEG_A_PIN_NUM + i)); // To jest (1UL << i)
        // Sprawdź, czy i-ty bit w segments_to_set jest 1 (0=SegA, 1=SegB, ...)
        if ((segments_to_set >> i) & 0x01) {
             GPIO_WritePin(SEG_PORT, current_segment_pin_mask, 1); // Włącz segment
        } else {
             GPIO_WritePin(SEG_PORT, current_segment_pin_mask, 0); // Wyłącz segment
        }
    }

    // Włącz odpowiednią anodę cyfry
    if (digit_position < 4) {
        GPIO_WritePin(DIGIT_PORT, digit_anode_pins_mask[digit_position], 1);
    }
}

/* ========================================================================== */
/* == FUNKCJA GŁÓWNA ======================================================== */
/* ========================================================================== */
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

int main(void)
{
  SystemInit();
  SystemCoreClockUpdate();
  My_SysTick_Init(SystemCoreClock);
  GPIO_Init_Display_Joystick();

  Get_Digits_For_Display(counter_value, digits_to_display); // Inicjalizacja cyfr wyświetlacza

  uint32_t current_tick;

  while (1)
  {
    current_tick = systick_counter;

    // --- Obsługa wejścia joysticka z debouncingiem ---
    if ((current_tick - last_joy_ok_poll_time) >= JOY_OK_POLL_INTERVAL_MS) {
        last_joy_ok_poll_time = current_tick;
        uint8_t joy_ok_raw_state = GPIO_ReadPin(JOY_OK_PORT, JOY_OK_PIN_MASK); // 0 jeśli wciśnięty, 1 jeśli zwolniony

        if (joy_ok_raw_state != joy_ok_last_raw_state) {
            // Surowy stan się zmienił, zresetuj timer debounce
            joy_ok_last_change_time = current_tick;
        }
        // Ten blok 'else' był częścią oryginalnej logiki i jest poprawny:
        // oznacza, że joy_ok_raw_state był spójny od ostatniego odpytania.
        // Następnie sprawdzamy, czy był spójny przez cały okres debounce.
        else { // joy_ok_raw_state == joy_ok_last_raw_state
            if ((current_tick - joy_ok_last_change_time) >= JOY_OK_DEBOUNCE_TIME_MS) {
                // Stan był stabilny (równy joy_ok_raw_state) przez JOY_OK_DEBOUNCE_TIME_MS
                if (joy_ok_raw_state != joy_ok_prev_stable_state) {
                    // Stabilny stan się zmienił
                    joy_ok_prev_stable_state = joy_ok_raw_state;
                    // Brak konkretnej akcji na samo zdarzenie wciśnięcia/zwolnienia,
                    // stan przytrzymania (joy_ok_prev_stable_state) jest używany przez licznik.
                }
            }
        }
        joy_ok_last_raw_state = joy_ok_raw_state; // Zaktualizuj ostatnio widziany surowy stan
    }

    // --- Logika aktualizacji licznika ---
    if ((current_tick - last_counter_update_time) >= COUNTER_UPDATE_DELAY_MS)
    {
        last_counter_update_time = current_tick;

        // joy_ok_prev_stable_state: 0 = wciśnięty (zmniejszaj), 1 = zwolniony (zwiększaj)
        if (joy_ok_prev_stable_state == 0) { // Przycisk joysticka jest PRZYTRZYMANY
            // Zmniejszaj licznik
            if (counter_value == 0) {
                counter_value = 9999;
            } else {
                counter_value--;
            }
        } else { // Przycisk joysticka jest ZWOLNIONY
            // Zwiększaj licznik
            counter_value++;
            if (counter_value > 9999) {
                counter_value = 0;
            }
        }
        Get_Digits_For_Display(counter_value, digits_to_display);
    }

    // --- Logika odświeżania wyświetlacza (multipleksowanie) ---
    if ((current_tick - last_display_refresh_time) >= DISPLAY_REFRESH_DELAY_MS)
    {
        last_display_refresh_time = current_tick;

        // Wyłącz anodę aktualnie aktywnej cyfry przed przełączeniem
        GPIO_WritePin(DIGIT_PORT, digit_anode_pins_mask[current_display_digit_idx], 0);

        // Przejdź do następnej cyfry
        current_display_digit_idx++;
        if (current_display_digit_idx >= 4) {
            current_display_digit_idx = 0;
        }

        // Wyświetl nową bieżącą cyfrę
        // (Funkcja Display_Digit ustawi segmenty, a następnie włączy anodę nowej cyfry)
        Display_Digit(digits_to_display[current_display_digit_idx], current_display_digit_idx);
    }
  }
}

/* ========================================================================== */
/* == HANDLERY PRZERWAŃ ===================================================== */
/* ========================================================================== */
void SysTick_Handler(void)
{
  systick_counter++;
}

// Standardowe procedury obsługi błędów
void NMI_Handler(void) { while(1); }
void HardFault_Handler(void) { while(1); }
void MemManage_Handler(void) { while(1); }
void BusFault_Handler(void) { while(1); }
void UsageFault_Handler(void) { while(1); }
void SVC_Handler(void) {}
void DebugMon_Handler(void) {}
void PendSV_Handler(void) {}

// Error_Handler może być wywoływany przez sterowniki HAL (jeśli używane) lub niestandardowe sprawdzanie błędów
void Error_Handler(void)
{
  while (1) {}
}
