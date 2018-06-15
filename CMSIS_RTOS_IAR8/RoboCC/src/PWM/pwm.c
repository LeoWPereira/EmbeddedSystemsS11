#include "pwm.h"
#include "gpio.h"
#include "gui.h"

uint32_t pwmMotor1 = 0;
uint32_t pwmMotor2 = 0;

// Declare a message queue
osMessageQDef(pwmMessage_q,
              5,
              PWM_MESSAGES);

// Declare an ID for the message queue
osMessageQId pwmMessage_q;

static void initPWM(void);

static void changePWMValue(PWM_MOTORS chosenMotor, 
                           int32_t value);

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
          
        case INC_PWM_1_VALUE:
          changePWMValue(MOTOR_1,
                         PWM_PACE);
          break;
          
        case INC_PWM_2_VALUE:
          changePWMValue(MOTOR_2,
                         PWM_PACE);
          break;
          
        case DEC_PWM_1_VALUE:
          changePWMValue(MOTOR_1,
                         -PWM_PACE);
          break;
          
        case DEC_PWM_2_VALUE:
          changePWMValue(MOTOR_2,
                         -PWM_PACE);
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
  ///////////////////////////////////
  /// Inicializa PWM para motor 1 ///
  ///////////////////////////////////
  
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);
  
  REGISTER_PWM_CYCLE_BASE       = 0xD3;
  
  REGISTER_PWM_MOTOR_1          = 0xD2;
  
  REGISTER_PWM_MOTOR_2          = 0xD2;
   
  REGISTER_CONTROL_PWM_MOTORES  = 0x0B;
  REGISTER_MCR_PWM_MOTORES      = 0x400;
  
  REGISTER_MR3_PWM_MOTORES      = REGISTER_PWM_CYCLE_LENGTH;
  
  REGISTER_MR0_MOTOR_1          = (REGISTER_PWM_CYCLE_LENGTH - MINIMUM_PWM_VALUE);
    
  REGISTER_MR1_MOTOR_2          = (REGISTER_PWM_CYCLE_LENGTH - MINIMUM_PWM_VALUE);

  REGISTER_TCR_PWM_MOTORES = 1;    //enable timer
  
  return;
}

void changePWMValue(PWM_MOTORS chosenMotor,
                    int32_t value)
{
  if(value > 0)
  {
    if(chosenMotor == MOTOR_1)
    {
      if((REGISTER_MR0_MOTOR_1 + value) < (REGISTER_PWM_CYCLE_LENGTH - MINIMUM_PWM_VALUE))
      {
        REGISTER_MR0_MOTOR_1 += value;
      }
      
      else
      {
        REGISTER_MR0_MOTOR_1 = (REGISTER_PWM_CYCLE_LENGTH - MINIMUM_PWM_VALUE);
      }
      
      pwmMotor1 = ((REGISTER_PWM_CYCLE_LENGTH - REGISTER_MR0_MOTOR_1) * 100) / REGISTER_PWM_CYCLE_LENGTH;
    }
    
    else if(chosenMotor == MOTOR_2)
    {
      if((REGISTER_MR1_MOTOR_2 + value) < (REGISTER_PWM_CYCLE_LENGTH - MINIMUM_PWM_VALUE))
      {
        REGISTER_MR1_MOTOR_2 += value;
      }
      
      else
      {
        REGISTER_MR1_MOTOR_2 = (REGISTER_PWM_CYCLE_LENGTH - MINIMUM_PWM_VALUE);
      }
      
      pwmMotor2 = ((REGISTER_PWM_CYCLE_LENGTH - REGISTER_MR1_MOTOR_2) * 100) / REGISTER_PWM_CYCLE_LENGTH;
    }
  }
  
  else if(value < 0)
  {
    if(chosenMotor == MOTOR_1)
    {
      if((REGISTER_MR0_MOTOR_1 + value) > MINIMUM_PWM_VALUE)
      {
        REGISTER_MR0_MOTOR_1 += value;
      }
      
      else
      {
        REGISTER_MR0_MOTOR_1 = MINIMUM_PWM_VALUE;
      }
      
      pwmMotor1 = ((REGISTER_PWM_CYCLE_LENGTH - REGISTER_MR0_MOTOR_1) * 100) / REGISTER_PWM_CYCLE_LENGTH;
    }
    
    else if(chosenMotor == MOTOR_2)
    {
      if((REGISTER_MR1_MOTOR_2 + value) > MINIMUM_PWM_VALUE)
      {
        REGISTER_MR1_MOTOR_2 += value;
      }
      
      else
      {
        REGISTER_MR1_MOTOR_2 = MINIMUM_PWM_VALUE;
      }
      
      pwmMotor2 = ((REGISTER_PWM_CYCLE_LENGTH - REGISTER_MR1_MOTOR_2) * 100) / REGISTER_PWM_CYCLE_LENGTH;
    }
  }
  
  return;
}