/**
 *
 */

#include "control.h"
#include "encoder.h"
#include "gui.h"
#include "pwm.h"
#include "timer.h"

osThreadId thread_Timer_id;
osThreadId thread_GUI_id;
osThreadId thread_Encoder_id;
osThreadId thread_Control_id;
osThreadId thread_PWM_id;

osThreadDef(thread_timer, 
            osPriorityNormal, 
            1, 
            0);

osThreadDef(thread_pwm, 
            osPriorityNormal, 
            1, 
            0);

osThreadDef(thread_gui, 
            osPriorityNormal, 
            1, 
            0);

osThreadDef(thread_encoder, 
            osPriorityNormal, 
            1, 
            0);

osThreadDef(thread_control, 
            osPriorityNormal, 
            1, 
            0);

/**
 *
 */
int main()
{
  osKernelInitialize();
  SystemInit();
  
  // System thread initialization
  thread_Timer_id = osThreadCreate(osThread(thread_timer), 
                                   NULL);
  
  thread_GUI_id = osThreadCreate(osThread(thread_pwm), 
                                 NULL);
  
  thread_Encoder_id = osThreadCreate(osThread(thread_gui), 
                                     NULL);
  
  thread_Control_id = osThreadCreate(osThread(thread_encoder), 
                                     NULL);
  
  thread_PWM_id = osThreadCreate(osThread(thread_control), 
                                 NULL);
  
  osKernelStart();
  osDelay(osWaitForever);
  
  return 0;
}
