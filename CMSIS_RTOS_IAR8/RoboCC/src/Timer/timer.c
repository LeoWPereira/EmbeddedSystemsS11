#include "timer.h"
#include "gui.h"
#include "rt_TypeDef.h"
#include "rt_Time.h"
#include "control.h"
#include "encoder.h"

//static uint32_t globalTime = 0;

/**
 *
 */
void thread_timer(void const *argument)
{  
  while(DEF_TRUE)
  {
    if((rt_time_get() % TIMER_READ_KEYBOARD) == 0)
    {
      thread_gpio_writeMessage(READ_KEYBOARD);
    }
    
    if((rt_time_get() % TIMER_READ_INTERRUPT_BUTTON) == 0)
    {
      thread_gpio_writeMessage(READ_INTERRUPT_BUTTON);
    }
    
    if((rt_time_get() % TIMER_UPDATE_SCREEN) == 0)
    {
      thread_gui_writeMessage(UPDATE_SCREEN);
    }
    
    if((rt_time_get() % TIMER_EXECUTE_PID) == 0)
    {
      thread_control_writeMessage(EXECUTE_PID_CONTROL);
    }
    
    if((rt_time_get() % TIMER_READ_ENCODER) == 0)
    {
      thread_encoder_writeMessage(READ_ENCODER);
    }
  }
  
  return;
}