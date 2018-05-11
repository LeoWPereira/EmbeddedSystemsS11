#include "Timer.h"

void PIOINT2_IRQHandler(void)
{
  uint32_t regVal = GPIOIntStatus(PORT2, 
                                  9);
  
  if (regVal)
  {
    GPIOIntClear(PORT2, 
                 9);
  }
  
  if(!ucFlagPrintFrequencyScale)
  {
    if(frequencyScale == HERTZ)
    {
      frequencyScale = KILO_HERTZ;
      
      timer_inicializarTimer(TIMER_INTERRUPCAO,
                             0,
                             1,
                             0);
    }
    
    else if(frequencyScale == KILO_HERTZ)
    {
      frequencyScale = HERTZ;
      
      timer_inicializarTimer(TIMER_INTERRUPCAO,
                             1,
                             0,
                             0);
    }
                                
    ucFlagPrintFrequencyScale = DEF_TRUE;
  }
  
  return;
}
