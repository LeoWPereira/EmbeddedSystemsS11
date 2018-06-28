/**
 *
 */

#ifndef __ENCODER_H__
#define __ENCODER_H__

/****************************************************************************************
 * DEPENDENCIAS
 ****************************************************************************************/

/****************************************************************************************
 * CONSTANTES E MACROS
 ****************************************************************************************/

#define TIMER_COUNTER_MOTOR1                   LPC_TMR16B0
#define TIMER_COUNTER_MOTOR2                   LPC_TMR16B1

/****************************************************************************************
 * DEFINICOES DE TIPOS E ESTRUTURAS
 ****************************************************************************************/

extern uint32_t counterMotor1;
extern uint32_t counterMotor2;

typedef enum 
{
  INIT_ENCODER,
  READ_ENCODER
} ENCODER_MESSAGES;

/****************************************************************************************
 * DEFINICOES DE FUNCOES
 ****************************************************************************************/

extern void thread_encoder(void const *argument);

extern void thread_encoder_writeMessage(ENCODER_MESSAGES message);

extern uint8_t timer_inicializarEncoderTimer(LPC_TMR_TypeDef* timer);

#endif