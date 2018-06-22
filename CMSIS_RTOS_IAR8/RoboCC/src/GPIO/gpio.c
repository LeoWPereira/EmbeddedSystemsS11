#include "gpio.h"
#include "gui.h"
#include "control.h"

// Declare a message queue
osMessageQDef(gpioMessage_q,
              5,
              GPIO_MESSAGES);

osMessageQId gpioMessage_q;                 

static uint8_t changeScreenButton = 0;

static void KeypadGetKey(void);

static void configPUPD(void);

void PIOINT2_IRQHandler(void)
{
  uint32_t regVal_2_9 = GPIOIntStatus(PORT2, 
                                      9);
    
  if (regVal_2_9)
  {
    GPIOIntClear(PORT2, 
                 9);
    
    changeScreenButton = 1;
  }
  
  return;
}

/**
 *
 */
void thread_gpio(void const *argument)
{
  osEvent event;
  
  configPUPD();
  
  GPIOSetInterrupt(PORT2,
                   9,
                   1,
                   0,
                   0);
  
  GPIOIntEnable(PORT2, 
                9);
  
  // create the message queue inside the thread
  gpioMessage_q = osMessageCreate(osMessageQ(gpioMessage_q),
                                   NULL);
  
  while(DEF_TRUE)
  {
    event = osMessageGet(gpioMessage_q, 
                         osWaitForever);
    
    if(event.status == osEventMessage)
    {
      switch(event.value.v)
      {
        case READ_INTERRUPT_BUTTON:
          if(changeScreenButton)
          {
            thread_gui_writeMessage(CHANGE_SCREEN);
           
            changeScreenButton = 0;
          }
         
          break;
          
        case READ_KEYBOARD:
          KeypadGetKey();
          
          break;
          
        default:
          break;
      }
    }
  }
  
  return;
}

void configPUPD(void)
{
  LPC_IOCON->PIO2_0 = 0xC8; // pull-down
  LPC_IOCON->PIO2_2 = 0xC8; // pull-down
  LPC_IOCON->PIO2_4 = 0xC8; // pull-down
  LPC_IOCON->PIO2_6 = 0xC8; // pull-down
  
  GPIOSetDir( PORT2, 0, 0 );
  GPIOSetDir( PORT2, 2, 0 );
  GPIOSetDir( PORT2, 5, 0 );
  GPIOSetDir( PORT2, 6, 0 );
  
  GPIOSetDir( PORT2, 8, 1 );
  GPIOSetDir( PORT2, 10, 1 );
  GPIOSetDir( PORT3, 0, 1 );
  GPIOSetDir( PORT3, 2, 1 );
    
  return;
}

void KeypadGetKey(void)
{
    static uint8_t STATE_MACHINE = 0;
    
    if(STATE_MACHINE == 0)
    {
      // Scan column 0 (column 0 pin is grounded, other column pins 
      // is open drain)
      GPIOSetValue(PORT2,
                   8,
                   0);
      
      GPIOSetValue(PORT2,
                 10,
                 1);
      
      GPIOSetValue(PORT3,
                 0,
                 1);
      
      GPIOSetValue(PORT3,
                 2,
                 1);
      
      osDelay(10);
      
      // Read rows
      if (!GPIOGetValue(PORT2,
                 0))
      {
          thread_control_writeMessage(COMMAND_ROTATE_LEFT);
      }
      
      else if (!GPIOGetValue(PORT2,
                 2))
      {
        thread_control_writeMessage(COMMAND_TURN_LEFT);
      }
      
      else if (!GPIOGetValue(PORT2,
                 4))
      {
        thread_control_writeMessage(COMMAND_ROTATE_LEFT_BACK);
      }
      
      STATE_MACHINE = 1;
    }
    
    else if(STATE_MACHINE == 1)
    {
      // Scan column 0 (column 0 pin is grounded, other column pins 
      // is open drain)
      GPIOSetValue(PORT2,
                   8,
                   1);
      
      GPIOSetValue(PORT2,
                 10,
                 0);
      
      GPIOSetValue(PORT3,
                 0,
                 1);
      
      GPIOSetValue(PORT3,
                 2,
                 1);
      
      osDelay(10);
      
      // Read rows
      if (!GPIOGetValue(PORT2,
                 0))
      {
          thread_control_writeMessage(COMMAND_FORWARD);
      }
      
      else if (!GPIOGetValue(PORT2,
                 2))
      {
        thread_control_writeMessage(COMMAND_STOP);
      }
      
      else if (!GPIOGetValue(PORT2,
                 4))
      {
        thread_control_writeMessage(COMMAND_BACK);
      }
      
      STATE_MACHINE = 2;
    }
    
    else if(STATE_MACHINE == 2)
    {
      // Scan column 0 (column 0 pin is grounded, other column pins 
      // is open drain)
      GPIOSetValue(PORT2,
                   8,
                   1);
      
      GPIOSetValue(PORT2,
                 10,
                 1);
      
      GPIOSetValue(PORT3,
                 0,
                 0);
      
      GPIOSetValue(PORT3,
                 2,
                 1);
      
      osDelay(10);
      
      // Read rows
      if (!GPIOGetValue(PORT2,
                 0))
      {
          thread_control_writeMessage(COMMAND_ROTATE_RIGHT);
      }
      
      else if (!GPIOGetValue(PORT2,
                 2))
      {
        thread_control_writeMessage(COMMAND_TURN_RIGHT);
      }
      
      else if (!GPIOGetValue(PORT2,
                 4))
      {
        thread_control_writeMessage(COMMAND_ROTATE_RIGHT_BACK);
      }
      
      STATE_MACHINE = 0;
    }
    
    return;
}

void thread_gpio_writeMessage(GPIO_MESSAGES message)
{
  osMessagePut(gpioMessage_q,
               (uint32_t)message,
               osWaitForever);
  
  return;
}