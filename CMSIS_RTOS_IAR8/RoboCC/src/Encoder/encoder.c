#include "encoder.h"

// Declare a message queue
osMessageQDef(encoderMessage_q,
              5,
              ENCODER_MESSAGES);

// Declare an ID for the message queue
osMessageQId(encoderMessage_q_id);

/**
 *
 */
void thread_encoder(void const *argument)
{
  osEvent event;
  
  // create the message queue inside the thread
  encoderMessage_q_id = osMessageCreate(osMessageQ(encoderMessage_q),
                                        NULL);
  
  while(DEF_TRUE)
  {
    event = osMessageGet(encoderMessage_q_id, 
                         osWaitForever);
    
    if(event.status == osEventMessage)
    {
      switch(event.value.v)
      {
        case INIT_ENCODER:
          break;

        default:
          break;
      }
    }
  }
  
  return;
}