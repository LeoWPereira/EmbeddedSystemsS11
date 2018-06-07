#include "timer.h"
#include "gui.h"

static uint32_t globalTime = 0;

/**
 *
 */
void thread_timer(void const *argument)
{
  while(DEF_TRUE)
  {
    osDelay(100);
    
    thread_gui_writeMessage(UPDATE_SCREEN);
  }
  
  return;
}