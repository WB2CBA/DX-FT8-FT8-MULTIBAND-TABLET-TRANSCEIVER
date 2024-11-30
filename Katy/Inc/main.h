
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"

#include "stm32746g_discovery.h"
#include "lcd_log.h"
#include "stm32f7xx_hal.h"

void HAL_Delay(uint32_t Delay);

#define NoOp  __NOP()

//int16_t Clock_Source;

uint32_t current_time, start_time, ft8_time;
uint8_t  ft8_hours, ft8_minutes, ft8_seconds;
//uint32_t days_fraction;
uint32_t hours_fraction;
uint32_t minute_fraction;

void update_synchronization(void);



#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
