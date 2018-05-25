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

/****************************************************************************************
 * DEFINICOES DE TIPOS E ESTRUTURAS
 ****************************************************************************************/

extern osMessageQId encoderMessage_q_id;
   
typedef enum 
{
  INIT_ENCODER
} ENCODER_MESSAGES;

/****************************************************************************************
 * DEFINICOES DE FUNCOES
 ****************************************************************************************/

extern void thread_encoder(void const *argument);

#endif