/* stm32l4xx_hal_conf.h */
#ifndef __STM32L4XX_HAL_CONF_H
#define __STM32L4XX_HAL_CONF_H

#include <stdint.h>

/* Adresy bazowe peryferiów */
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

/* Struktury rejestrów */
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
  volatile uint32_t CALIB;
} SysTick_Type;

/* Instancje peryferii */
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define PWR                 ((PWR_TypeDef *) PWR_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)
#define SysTick             ((SysTick_Type *) SysTick_BASE)

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

/* Maski bitów dla GPIO */
#define GPIO_MODER_MODE_INPUT       (0x00UL)
#define GPIO_MODER_MODE_OUTPUT      (0x01UL)
#define GPIO_MODER_MODE_ALTERNATE   (0x02UL)
#define GPIO_MODER_MODE_ANALOG      (0x03UL)

#define GPIO_OTYPER_OT_PP           (0x00UL)
#define GPIO_OTYPER_OT_OD           (0x01UL)

#define GPIO_OSPEEDR_OSPEED_LOW     (0x00UL)
#define GPIO_OSPEEDR_OSPEED_MEDIUM  (0x01UL)
#define GPIO_OSPEEDR_OSPEED_HIGH    (0x02UL)
#define GPIO_OSPEEDR_OSPEED_VHIGH   (0x03UL)

#define GPIO_PUPDR_PUPD_NONE        (0x00UL)
#define GPIO_PUPDR_PUPD_UP          (0x01UL)
#define GPIO_PUPDR_PUPD_DOWN        (0x02UL)

#endif /* __STM32L4XX_HAL_CONF_H */