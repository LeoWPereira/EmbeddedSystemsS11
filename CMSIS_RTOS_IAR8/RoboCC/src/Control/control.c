#include "control.h"

// Declare a message queue
osMessageQDef(controlMessage_q,
              5,
              CONTROL_MESSAGES);

// Declare an ID for the message queue
osMessageQId(controlMessage_q_id);

/**
 *
 */
void thread_control(void const *argument)
{
  osEvent event;
  
  // create the message queue inside the thread
  controlMessage_q_id = osMessageCreate(osMessageQ(controlMessage_q),
                                        NULL);
  
  while(DEF_TRUE)
  {
    event = osMessageGet(controlMessage_q_id, 
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