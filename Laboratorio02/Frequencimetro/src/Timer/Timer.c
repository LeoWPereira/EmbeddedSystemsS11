/**
 *
 */    
 
#define __TIMER_C__

/****************************************************************************************
 * DEPENDENCIAS
 ****************************************************************************************/

#include "Timer.h"

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

 /**
 * 
 */
void TIMER32_0_IRQHandler(void)
{
    frequencyCounter = TIMER_COUNTER->TC;
     
    TIMER_COUNTER->TCR = 0x02;
    TIMER_COUNTER->TCR = 0x01;
  
    // clear interrupt flag
    LPC_TMR32B0->IR = 1;	
    
    if((frequencyScale == HERTZ) || (printCounterKHz == PERIODO_INTERRUPCAO_KHERZ))
    {
      ucFlagPrintFrequency = DEF_TRUE;
      
      printCounterKHz = 0;
    }
    
    else if(frequencyScale == KILO_HERTZ)
    {
        printCounterKHz++;
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
