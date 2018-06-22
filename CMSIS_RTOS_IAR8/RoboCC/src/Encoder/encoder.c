/**
 *
 */  

/****************************************************************************************
 * DEPENDENCIAS
 ****************************************************************************************/

#include "encoder.h"

/****************************************************************************************
 * CONSTANTES E MACROS
 ****************************************************************************************/

// Declare a message queue
osMessageQDef(encoderMessage_q,
              5,
              ENCODER_MESSAGES);

// Declare an ID for the message queue
osMessageQId encoderMessage_q;

/****************************************************************************************
 * DEFINICOES DE TIPOS E ESTRUTURAS
 ****************************************************************************************/

/***************************************************************************************
 * PROTOTIPOS DE FUNCOES LOCAIS
 ***************************************************************************************/

static void readEncoder(void);

/****************************************************************************************
 * VARIAVEIS EXTERNAVEIS
 ****************************************************************************************/

uint32_t counterMotor1 = 0;
uint32_t counterMotor2 = 0;

/****************************************************************************************
 * VARIAVEIS GLOBAIS
 ****************************************************************************************/

/****************************************************************************************
 * DEFINICOES DE FUNCOES EXTERNAVEIS
 ****************************************************************************************/

/**
 *
 */
void thread_encoder(void const *argument)
{
  osEvent event;
  
  // create the message queue inside the thread
  encoderMessage_q = osMessageCreate(osMessageQ(encoderMessage_q),
                                     NULL);
  
  timer_inicializarTimer(TIMER_COUNTER_MOTOR1);
  timer_inicializarTimer(TIMER_COUNTER_MOTOR2);
  
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
          readEncoder();
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

/**
 *
 */
uint8_t timer_inicializarTimer(LPC_TMR_TypeDef* timer)
{  
  uint32_t intNum = 0;

  
  if(timer == LPC_TMR16B0)
  {
    //Libera o clock para o Timer
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 7);
    
    // Timer1_16 CAP0 
    LPC_IOCON->PIO0_2 |= 0x01;		
    
    intNum = TIMER_16_0_IRQn;
    
    //Sem prescale
    timer->PC = 0x00;
    
    timer->CTCR = 0x1;
  }
  
  else if(timer == LPC_TMR16B1)
  {
    //Libera o clock para o Timer
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 8);
    
    // Timer1_16 CAP0 
    LPC_IOCON->PIO1_8 |= 0x01;		
    
    intNum = TIMER_16_1_IRQn;
    
    //Sem prescale
    timer->PC = 0x00;
    
    timer->CTCR = 0x1;
  }
  
  //Bit 1 : Reseta Timer
  timer->TCR = 0x02;

  //Inicia o Timer
  timer->TCR = 0x01;
  
  // Enable the Interrupt
  NVIC_EnableIRQ(intNum);
  
  return DEF_TRUE;
}

/**
 *
 */
uint8_t timer_habilitaTimer(LPC_TMR_TypeDef* timer)
{
  timer->TCR = 1;
  
  return DEF_TRUE;
}

/**
 *
 */
uint8_t timer_desabilitaTimer(LPC_TMR_TypeDef* timer)
{
  timer->TCR = 0;
  
  return DEF_TRUE;
}

/****************************************************************************************
 * DEFINICOES DE FUNCOES LOCAIS
 ****************************************************************************************/

void readEncoder(void)
{
  counterMotor1 += TIMER_COUNTER_MOTOR1->TC;
  
  TIMER_COUNTER_MOTOR1->TCR = 0x02;
  TIMER_COUNTER_MOTOR1->TCR = 0x01;
  
  counterMotor2 += TIMER_COUNTER_MOTOR2->TC;
  
  TIMER_COUNTER_MOTOR2->TCR = 0x02;
  TIMER_COUNTER_MOTOR2->TCR = 0x01;
  
  return;
}

/****************************************************************************************
 * FIM DE ARQUIVO
 ****************************************************************************************/
