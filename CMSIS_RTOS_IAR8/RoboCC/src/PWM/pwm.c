#include "pwm.h"
#include "gpio.h"

// Declare a message queue
osMessageQDef(pwmMessage_q,
              5,
              PWM_MESSAGES);

// Declare an ID for the message queue
osMessageQId pwmMessage_q;

static void initPWM(void);

/**
 *
 */
void thread_pwm(void const *argument)
{
  osEvent event;
  
  // create the message queue inside the thread
  pwmMessage_q = osMessageCreate(osMessageQ(pwmMessage_q),
                                 NULL);
  
  thread_pwm_writeMessage(INIT_PWM);
  
  while(DEF_TRUE)
  {
    event = osMessageGet(pwmMessage_q, 
                         osWaitForever);
    
    if(event.status == osEventMessage)
    {
      switch(event.value.v)
      {
        case INIT_PWM:
          initPWM();
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
  osMessagePut(pwmMessage_q,
               (uint32_t)message,
               osWaitForever);
  
  return;
}

void initPWM(void)
{
  
  return;
}