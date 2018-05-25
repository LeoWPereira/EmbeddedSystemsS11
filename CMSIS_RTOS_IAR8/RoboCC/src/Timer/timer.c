#include "timer.h"

// Declare a message queue
osMessageQDef(timerMessage_q,
              5,
              TIMER_MESSAGES);

// Declare an ID for the message queue
osMessageQId(timerMessage_q_id);

/**
 *
 */
void thread_timer(void const *argument)
{
  osEvent event;
  
  // create the message queue inside the thread
  timerMessage_q_id = osMessageCreate(osMessageQ(timerMessage_q),
                                      NULL);
  
  while(DEF_TRUE)
  {
    event = osMessageGet(timerMessage_q_id, 
                         osWaitForever);
    
    if(event.status == osEventMessage)
    {
      switch(event.value.v)
      {
        case INIT_TIMER:
          break;

        default:
          break;
      }
    }
  }
  
  return;
}