/**
 *
 */

#ifndef __MAIN_H__
#define __MAIN_H__

/****************************************************************************************
 * DEPENDENCIAS
 ****************************************************************************************/

#include <stdio.h>

#include "mcu_regs.h"
#include "type.h"
#include "oled.h"
#include "gpio.h"
#include "ssp.h"

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

#endif