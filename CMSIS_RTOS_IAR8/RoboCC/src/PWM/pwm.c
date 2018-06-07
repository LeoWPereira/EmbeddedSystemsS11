#include "pwm.h"
#include "gpio.h"

// Declare a message queue
osMessageQDef(pwmMessage_q,
              5,
              PWM_MESSAGES);

// Declare an ID for the message queue
osMessageQId(pwmMessage_q_id);

/**
 *
 */
void thread_pwm(void const *argument)
{
  osEvent event;
  
  // create the message queue inside the thread
  pwmMessage_q_id = osMessageCreate(osMessageQ(pwmMessage_q),
                                      NULL);
  
  while(DEF_TRUE)
  {
    event = osMessageGet(pwmMessage_q_id, 
                         osWaitForever);
    
    if(event.status == osEventMessage)
    {
      switch(event.value.v)
      {
        case INIT_PWM:
          break;

        default:
          break;
      }
    }
  }
  
  return;
}

void thread_pwm_writeMessage(PWM_MESSAGES message)
{
  osMessagePut(pwmMessage_q_id,
               (uint32_t)message,
               osWaitForever);
  
  return;
}