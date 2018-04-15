/**
 * Laboratorio02
 * Juliano
 * Leonardo Winter Pereira
 * Rodrigo Yudi Endo
 */

#include "Timer.h"

void main(void)
{
  //////////////////////////
  /// Inicializa Sistema ///
  //////////////////////////
  SystemCoreClockUpdate();
  
  GPIOInit();
  
  SSPInit();
  
  oled_init();
  
  // Inicializa o Timer
  timer_inicializarTimer(0);
  
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
  }
}