#include "control.h"

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
        case INIT_CONTROL:
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