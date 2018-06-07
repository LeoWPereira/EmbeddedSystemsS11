#include "gpio.h"
#include "gui.h"

static uint8_t changeScreenButton = 0;

void PIOINT2_IRQHandler(void)
{
  uint32_t regVal = GPIOIntStatus(PORT2, 
                                  9);
  
  if (regVal)
  {
    GPIOIntClear(PORT2, 
                 9);
    
    changeScreenButton = 1;
  }
  
  return;
}

/**
 *
 */
void thread_gpio(void const *argument)
{
  while(DEF_TRUE)
  {
    if(changeScreenButton)
    {
      thread_gui_writeMessage(CHANGE_SCREEN);
      
      changeScreenButton = 0;
    }
    
    osDelay(50);
  }
  
  return;
}