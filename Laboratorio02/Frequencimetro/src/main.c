/**
 * Laboratorio02
 * Juliano
 * Leonardo Winter Pereira
 * Rodrigo Yudi Endo
 */

#include "Timer.h"
#include "Auxiliar.h"

/****************************************************************************************
* VARIAVEIS EXTERNAVEIS
****************************************************************************************/

uint8_t frequencyScale = HERTZ;

uint8_t ucFlagPrintFrequency = DEF_TRUE;

uint8_t ucFlagPrintFrequencyScale = DEF_TRUE;

/****************************************************************************************
 * DEFINICOES DE FUNCOES EXTERNAVEIS
 ****************************************************************************************/

static void SystemStart(void);

static void analyseAndPrintFrequencyScale(uint8_t y);

static void printFrequency(void);

void main(void)
{
  //
  SystemStart();
  
  //
  oled_clearScreen(OLED_COLOR_WHITE);
  
  //
  oled_putString(5,
                 1,
                 (uint8_t*)"Laboratorio 02",
                 OLED_COLOR_BLACK, 
                 OLED_COLOR_WHITE);
    
  while(DEF_TRUE)
  {
    if(ucFlagPrintFrequency)
    {
      printFrequency();
      
      ucFlagPrintFrequency = DEF_FALSE;
    }
    
    if(ucFlagPrintFrequencyScale)
    {      
      // analisamos a escala de frequencia selecionada e imprimimos no display
      analyseAndPrintFrequencyScale(DISPLAY_LAST_LINE);
      
      ucFlagPrintFrequencyScale = DEF_FALSE;
    }
  }
}

void SystemStart(void)
{
  //
  SystemCoreClockUpdate();
  
  // Inicializa General I/O
  GPIOInit();
  
  // Inicializa o Timer 0 (LPC_CT32B0_BASE)
  timer_inicializarTimer(TIMER_INTERRUPCAO,
                         1,
                         0,
                         0);

  // Inicializa o Timer 0 (LPC_CT32B0_BASE)
  timer_inicializarTimer(TIMER_COUNTER,
                         0,
                         0,
                         0);

  // Inicializa SSP (necessario para oled)
  SSPInit();
  
  // Inicializa o display
  oled_init();  
  
  GPIOSetInterrupt(PORT2,
                   9,
                   1,
                   0,
                   0);
  
  GPIOIntEnable(PORT2, 
                9);
  
  return;
}

void printFrequency(void)
{
  uint8_t frequencyValue[10];
  
  intToString(frequencyCounter, 
              frequencyValue, 
              6,
              10); 
    
  oled_fillRect(30, 
                DISPLAY_FREQUENCY_LINE, 
                69, 
                DISPLAY_FREQUENCY_LINE + 10, 
                OLED_COLOR_WHITE);
  
  //
  oled_putString(30,
                 DISPLAY_FREQUENCY_LINE,
                 frequencyValue,
                 OLED_COLOR_BLACK, 
                 OLED_COLOR_WHITE);
  
  //
  if(frequencyScale == HERTZ)
  {
    oled_putString(60,
                   DISPLAY_FREQUENCY_LINE,
                   (uint8_t *)" Hz ",
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);
  }
  
  else if(frequencyScale == KILO_HERTZ)
  {
    oled_putString(60,
                   DISPLAY_FREQUENCY_LINE,
                   (uint8_t *)" kHz",
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);
  }
  
  return;
}

void analyseAndPrintFrequencyScale(uint8_t y)
{
  oled_fillRect(0, 
                DISPLAY_LAST_LINE, 
                50, 
                DISPLAY_LAST_LINE + 10, 
                OLED_COLOR_WHITE);

  switch(frequencyScale)
  {
    case HERTZ:
      //
      oled_putString(5,
                     y,
                     (uint8_t*)"[X] Hz",
                     OLED_COLOR_BLACK, 
                     OLED_COLOR_WHITE);
      
      //
      oled_putString(50,
                     y,
                     (uint8_t*)"[ ] kHz",
                     OLED_COLOR_BLACK, 
                     OLED_COLOR_WHITE);
      break;
      
    case KILO_HERTZ:
        //
        oled_putString(5,
                       y,
                       (uint8_t*)"[ ] Hz",
                       OLED_COLOR_BLACK, 
                       OLED_COLOR_WHITE);
        
        //
        oled_putString(50,
                       y,
                       (uint8_t*)"[X] kHz",
                       OLED_COLOR_BLACK, 
                       OLED_COLOR_WHITE);
      break;
      
    default:
      break;
  }
  
  return;
}