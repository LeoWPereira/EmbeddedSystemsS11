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

/****************************************************************************************
 * DEFINICOES DE TIPOS E ESTRUTURAS
 ****************************************************************************************/

#define TIMER_INTERRUPCAO               LPC_TMR32B0
#define TIMER_COUNTER                   LPC_TMR16B1
  
#define PERIODO_INTERRUPCAO_KHERZ       1000 - 1 // 1000 vezes entrando na interrupcao

/****************************************************************************************
 * VARIAVEIS EXTERNAVEIS
 ****************************************************************************************/

extern uint32_t frequencyCounter;

/****************************************************************************************
 * DEFINICOES DE FUNCOES EXTERNAVEIS
 ****************************************************************************************/

extern uint8_t timer_inicializarTimer(LPC_TMR_TypeDef* timer,
                                      uint16_t periodSeg,
                                      uint16_t periodMs,
                                      uint16_t periodUs);

extern uint8_t timer_habilitaTimer(LPC_TMR_TypeDef* timer);

extern uint8_t timer_desabilitaTimer(LPC_TMR_TypeDef* timer);

#endif