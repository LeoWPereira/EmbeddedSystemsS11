/**
 *
 */

#ifndef __CONTROL_H__
#define __CONTROL_H__

/****************************************************************************************
 * DEPENDENCIAS
 ****************************************************************************************/

/****************************************************************************************
 * CONSTANTES E MACROS
 ****************************************************************************************/

/****************************************************************************************
 * DEFINICOES DE TIPOS E ESTRUTURAS
 ****************************************************************************************/

typedef enum 
{
  INIT_CONTROL,
  APLLY_PWM,
  COMMAND_FORWARD,
  COMMAND_BACK,
  COMMAND_STOP,
  COMMAND_ROTATE_LEFT,
  COMMAND_ROTATE_RIGHT,
  COMMAND_TURN_LEFT,
  COMMAND_TURN_RIGHT,
  COMMAND_ROTATE_LEFT_BACK,
  COMMAND_ROTATE_RIGHT_BACK
} CONTROL_MESSAGES;

/****************************************************************************************
 * DEFINICOES DE FUNCOES
 ****************************************************************************************/

extern uint32_t variavelGlobal;

extern void thread_control(void const *argument);

extern void thread_control_writeMessage(CONTROL_MESSAGES message);

#endif