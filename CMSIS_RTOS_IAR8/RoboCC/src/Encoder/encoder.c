#include "encoder.h"

// Declare a message queue
osMessageQDef(encoderMessage_q,
              5,
              ENCODER_MESSAGES);

// Declare an ID for the message queue
osMessageQId encoderMessage_q;

/**
 *
 */
void thread_encoder(void const *argument)
{
  osEvent event;
  
  // create the message queue inside the thread
  encoderMessage_q = osMessageCreate(osMessageQ(encoderMessage_q),
                                     NULL);
   
  thread_encoder_writeMessage(INIT_ENCODER);
    
  while(DEF_TRUE)
  {
    event = osMessageGet(encoderMessage_q, 
                         osWaitForever);
    
    if(event.status == osEventMessage)
    {
      switch(event.value.v)
      {
        case INIT_ENCODER:
          break;

        case READ_ENCODER:
          break;
          
        default:
          break;
      }
    }
  }
  
  return;
}

void thread_encoder_writeMessage(ENCODER_MESSAGES message)
{
  osMessagePut(encoderMessage_q,
               (uint32_t)message,
               osWaitForever);
  
  return;
}