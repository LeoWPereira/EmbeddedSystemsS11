#include "gui.h"

void PIOINT2_IRQHandler(void)
{
  uint32_t regVal = GPIOIntStatus(PORT2, 
                                  9);
  
  if (regVal)
  {
    GPIOIntClear(PORT2, 
                 9);
  }
  
  osMessagePut(guiMessage_q_id,
               (uint32_t)INIT_DISPLAY,
               osWaitForever);
  
  return;
}
