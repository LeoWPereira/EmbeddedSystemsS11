/**
 *
 */    
 
#define __TIMER_C__

/****************************************************************************************
 * DEPENDENCIAS
 ****************************************************************************************/

#include "Timer.h"
#include "gui.h"
#include "rt_TypeDef.h"
#include "rt_Time.h"
#include "control.h"
#include "encoder.h"

/****************************************************************************************
 * CONSTANTES E MACROS
 ****************************************************************************************/

/****************************************************************************************
 * DEFINICOES DE TIPOS E ESTRUTURAS
 ****************************************************************************************/

/***************************************************************************************
 * PROTOTIPOS DE FUNCOES LOCAIS
 ***************************************************************************************/

void timer_ManipularInterrupcaoTimer32B1(void);

/****************************************************************************************
 * VARIAVEIS EXTERNAVEIS
 ****************************************************************************************/

uint32_t frequencyCounter = 0;

/****************************************************************************************
 * VARIAVEIS GLOBAIS
 ****************************************************************************************/

static uint16_t printCounterKHz = 0;

/****************************************************************************************
 * DEFINICOES DE FUNCOES EXTERNAVEIS
 ****************************************************************************************/

void thread_timer(void const *argument)
{
  // Inicializa o Timer 0 (LPC_CT32B0_BASE)
  timer_inicializarTimer(TIMER_COUNTER,
                         0,
                         0,
                         0);
  
  while(DEF_TRUE)
  {
    if((rt_time_get() % TIMER_READ_KEYBOARD) == 0)
    {
      thread_gpio_writeMessage(READ_KEYBOARD);
    }
    
    if((rt_time_get() % TIMER_READ_INTERRUPT_BUTTON) == 0)
    {
      thread_gpio_writeMessage(READ_INTERRUPT_BUTTON);
    }
    
    if((rt_time_get() % TIMER_UPDATE_SCREEN) == 0)
    {
      thread_gui_writeMessage(UPDATE_SCREEN);
    }
    
    if((rt_time_get() % TIMER_EXECUTE_PID) == 0)
    {
      thread_control_writeMessage(EXECUTE_PID_CONTROL);
    }
    
    if((rt_time_get() % TIMER_READ_ENCODER) == 0)
    {
      thread_encoder_writeMessage(READ_ENCODER);
    }
  }
  
  return;
}

/**
 *
 */
uint8_t timer_inicializarTimer(LPC_TMR_TypeDef* timer,
                               uint16_t periodSeg,
                               uint16_t periodMs,
                               uint16_t periodUs)
{  
  uint32_t intNum = 0;
  
  uint32_t interruptPeriod = ((periodSeg * 1000000) + (periodMs * 1000) + (periodUs));
  
  if(timer == LPC_TMR32B0)
  {
    //Libera o clock para o Timer
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9);

    //Seleciona o CT32B0_MAT0
    LPC_IOCON->PIO1_6 |= 0x02;
    
    intNum = TIMER_32_0_IRQn;
    
    //Coloca o valor do Match0 em 'interruptPeriod' uS
    //Como o output é alternado a cada vez que o timer chega no match, devemos configurar o timer
    //para numa frequencia 2x mais rapida do que a desejada. 
    timer->MR0 = interruptPeriod * ((SystemCoreClock / LPC_SYSCON->SYSAHBCLKDIV) / 1000000);

    //Reseta em modo interrupcao o MR0
    timer->MCR = 0x03; 
    
    //Toggle no bit do match externo
    timer->EMR |= (0x03 << 4);
    
    //Sem prescale
    timer->PR = 0x00;
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
  
  // Enable the TIMER0 Interrupt
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

/****************************************************************************************
 * FIM DE ARQUIVO
 ****************************************************************************************/
