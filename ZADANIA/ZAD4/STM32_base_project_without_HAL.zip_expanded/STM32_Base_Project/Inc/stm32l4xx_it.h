/* stm32l4xx_it.h */
#ifndef __STM32L4xx_IT_H
#define __STM32L4xx_IT_H

/* Eksportowane funkcje handlerów przerwań ----------------------------------------*/
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#endif /* __STM32L4xx_IT_H */