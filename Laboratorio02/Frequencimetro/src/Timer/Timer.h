/**
 *
 */

#ifndef __TIMER_H__
#define __TIMER_H__

/****************************************************************************************
 * DEPENDENCIAS
 ****************************************************************************************/

/****************************************************************************************
 * CONSTANTES E MACROS
 ****************************************************************************************/

#define TIMER_READ_KEYBOARD             20
#define TIMER_UPDATE_SCREEN             100
#define TIMER_READ_INTERRUPT_BUTTON     100
#define TIMER_APPLY_PWM_CONTROL         100
#define TIMER_READ_ENCODER              100
#define TIMER_EXECUTE_PID               100

/****************************************************************************************
 * DEFINICOES DE TIPOS E ESTRUTURAS
 ****************************************************************************************/
  
#define TIMER_INTERRUPCAO               LPC_TMR32B0
#define TIMER_COUNTER                   LPC_TMR16B1

#define PERIODO_INTERRUPCAO_KHERZ       1000 - 1 // 1000 vezes entrando na interrupcao

/****************************************************************************************
 * VARIAVEIS EXTERNAVEIS
 ****************************************************************************************/

/****************************************************************************************
 * DEFINICOES DE FUNCOES EXTERNAVEIS
 ****************************************************************************************/

extern void thread_timer(void const *argument);

extern uint8_t timer_inicializarTimer(LPC_TMR_TypeDef* timer,
                                      uint16_t periodSeg,
                                      uint16_t periodMs,
                                      uint16_t periodUs);

extern uint8_t timer_habilitaTimer(LPC_TMR_TypeDef* timer);

extern uint8_t timer_desabilitaTimer(LPC_TMR_TypeDef* timer);

#endif