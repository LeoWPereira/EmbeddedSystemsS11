#include "timer.h"
#include "gui.h"
#include "rt_TypeDef.h"
#include "rt_Time.h"

//static uint32_t globalTime = 0;

/**
 *
 */
void thread_timer(void const *argument)
{
  // Inicializa o Timer 0 (LPC_CT32B0_BASE)
  /*timer_inicializarTimer(TIMER_INTERRUPCAO,
                         1,
                         0,
                         0);

  // Inicializa o Timer 0 (LPC_CT32B0_BASE)
  timer_inicializarTimer(TIMER_COUNTER,
                         0,
                         0,
                         0);*/
  
  while(DEF_TRUE)
  {
    if((rt_time_get() % TIMER_READ_KEYBOARD) == 0)
    {
      thread_gpio_writeMessage(READ_KEYBOARD);
    }
    
    if((rt_time_get() % TIMER_UPDATE_SCREEN) == 0)
    {
      thread_gui_writeMessage(UPDATE_SCREEN);
    }
    
    if((rt_time_get() % TIMER_READ_INTERRUPT_BUTTON) == 0)
    {
      thread_gpio_writeMessage(READ_INTERRUPT_BUTTON);
    }
    
    if((rt_time_get() % TIMER_APPLY_PWM_CONTROL) == 0)
    {
      thread_control_writeMessage(APLLY_PWM);
    }
    
    if((rt_time_get() % TIMER_READ_ENCODER) == 0)
    {
      thread_encoder_writeMessage(READ_ENCODER);
    }
  }
  
  return;
}