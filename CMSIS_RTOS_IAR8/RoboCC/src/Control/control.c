#include "control.h"
#include "pwm.h"

// Declare a message queue
osMessageQDef(controlMessage_q,
              5,
              CONTROL_MESSAGES);

// Declare an ID for the message queue
osMessageQId controlMessage_q;

/**
 *
 */
void thread_control(void const *argument)
{
  osEvent event;
  
  // create the message queue inside the thread
  controlMessage_q = osMessageCreate(osMessageQ(controlMessage_q),
                                     NULL);
  
  while(DEF_TRUE)
  {
    event = osMessageGet(controlMessage_q, 
                         osWaitForever);
    
    if(event.status == osEventMessage)
    {
      switch(event.value.v)
      {
        case EXECUTE_PID_CONTROL:
          break;
          
        case COMMAND_FORWARD:
          thread_pwm_writeMessage(DEC_PWM_1_VALUE);
          thread_pwm_writeMessage(DEC_PWM_2_VALUE);
          
          thread_pwm_writeMessage(HB_FORWARD);
          break;
          
        case COMMAND_BACK:
          
          
          thread_pwm_writeMessage(INC_PWM_1_VALUE);
          thread_pwm_writeMessage(INC_PWM_2_VALUE);
          
          
          thread_pwm_writeMessage(HB_BACK);
          break;
          
        case COMMAND_STOP:
          while((pwmMotor1 > 1) || (pwmMotor2 > 1))
          {
            thread_pwm_writeMessage(INC_PWM_1_VALUE);
            thread_pwm_writeMessage(INC_PWM_2_VALUE);
          
            osDelay(50);
          }
          break;
          
        case COMMAND_ROTATE_LEFT:
          thread_pwm_writeMessage(DEC_PWM_2_VALUE);
          thread_pwm_writeMessage(DEC_PWM_2_VALUE);
          thread_pwm_writeMessage(DEC_PWM_1_VALUE);
          break;
          
        case COMMAND_ROTATE_RIGHT:
          thread_pwm_writeMessage(DEC_PWM_1_VALUE);
          thread_pwm_writeMessage(DEC_PWM_1_VALUE);
          thread_pwm_writeMessage(DEC_PWM_2_VALUE);
          break;
          
        case COMMAND_TURN_LEFT:
          thread_pwm_writeMessage(DEC_PWM_2_VALUE);
          thread_pwm_writeMessage(DEC_PWM_1_VALUE);
          thread_pwm_writeMessage(HB_ROTATE_LEFT);
          break;
          
        case COMMAND_TURN_RIGHT:
          thread_pwm_writeMessage(DEC_PWM_2_VALUE);
          thread_pwm_writeMessage(DEC_PWM_1_VALUE);
          thread_pwm_writeMessage(HB_ROTATE_RIGHT);
          break;
          
        case COMMAND_ROTATE_LEFT_BACK:
          break;
          
        case COMMAND_ROTATE_RIGHT_BACK:
          break;

        default:
          break;
      }
    }
  }
  
  return;
}

void thread_control_writeMessage(CONTROL_MESSAGES message)
{
  osMessagePut(controlMessage_q,
               (uint32_t)message,
               osWaitForever);
  
  return;
}