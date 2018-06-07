#include "gpio.h"
#include "gui.h"

// Declare a message queue
osMessageQDef(gpioMessage_q,
              5,
              GUI_MESSAGES);

osMessageQId gpioMessage_q;

void PIOINT2_IRQHandler(void)
{
  uint32_t regVal = GPIOIntStatus(PORT2, 
                                  9);
  
  if (regVal)
  {
    GPIOIntClear(PORT2, 
                 9);
  }
  
  thread_gui_writeMessage(CHANGE_SCREEN);
  
  return;
}
