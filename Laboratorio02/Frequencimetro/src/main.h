/**
 *
 */

#ifndef __MAIN_H__
#define __MAIN_H__

/****************************************************************************************
 * DEPENDENCIAS
 ****************************************************************************************/

#include <stdio.h>

#include "LPC13xx.h" // CMSIS-Core
#include "cmsis_os.h" // CMSIS-RTOS

#include "mcu_regs.h"
#include "type.h"

#include "ssp.h"

#include "oled.h"
#include "gpio.h"

/****************************************************************************************
 * CONSTANTES E MACROS
 ****************************************************************************************/

#ifndef DEF_TRUE
#define DEF_TRUE 1
#endif

#ifndef DEF_FALSE
#define DEF_FALSE 0
#endif

#define DISPLAY_FREQUENCY_LINE          30
#define DISPLAY_LAST_LINE               55

/****************************************************************************************
 * DEFINICOES DE TIPOS E ESTRUTURAS
 ****************************************************************************************/

enum FREQUENCY_SCALE
{
    HERTZ,
    KILO_HERTZ
};

extern uint8_t frequencyScale;

extern uint8_t ucFlagPrintFrequency;

extern uint8_t ucFlagPrintFrequencyScale;

extern uint32_t frequencyCounter;

typedef enum
{
  READ_INTERRUPT_BUTTON,
  READ_KEYBOARD
} GPIO_MESSAGES;

extern void thread_gpio(void const *argument);

extern void thread_gpio_writeMessage(GPIO_MESSAGES message);

#endif