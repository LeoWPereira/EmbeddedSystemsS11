/**
 * Laboratorio02
 * Juliano
 * Leonardo Winter Pereira
 * Rodrigo Yudi Endo
 */

#include "control.h"
#include "encoder.h"
#include "gui.h"
#include "pwm.h"
#include "gpio.h"
   
#include "Timer.h"
#include "Auxiliar.h"

/****************************************************************************************
* VARIAVEIS EXTERNAVEIS
****************************************************************************************/

uint8_t frequencyScale = HERTZ;

uint8_t ucFlagPrintFrequency = DEF_TRUE;

uint8_t ucFlagPrintFrequencyScale = DEF_TRUE;

osThreadId thread_Timer_id;
osThreadId thread_GUI_id;
osThreadId thread_Encoder_id;
osThreadId thread_Control_id;
osThreadId thread_PWM_id;
osThreadId thread_GPIO_id;

osThreadDef(thread_timer, 
            osPriorityNormal, 
            1, 
            0);

osThreadDef(thread_pwm, 
            osPriorityNormal, 
            1, 
            0);

osThreadDef(thread_gui, 
            osPriorityNormal, 
            1, 
            0);

osThreadDef(thread_encoder, 
            osPriorityNormal, 
            1, 
            0);

osThreadDef(thread_control, 
            osPriorityNormal, 
            1, 
            0);

osThreadDef(thread_gpio, 
            osPriorityNormal, 
            1, 
            0);

/****************************************************************************************
 * DEFINICOES DE FUNCOES EXTERNAVEIS
 ****************************************************************************************/

static void SystemStart(void);

void main(void)
{
  osKernelInitialize();
  
  SystemInit();
  
  //
  SystemStart();
  
  // System thread initialization
  thread_Timer_id = osThreadCreate(osThread(thread_timer), 
                                   NULL);
  
  thread_GUI_id = osThreadCreate(osThread(thread_gui), 
                                 NULL);
  
  thread_Encoder_id = osThreadCreate(osThread(thread_encoder), 
                                     NULL);
  
  thread_Control_id = osThreadCreate(osThread(thread_control), 
                                     NULL);
  
  thread_PWM_id = osThreadCreate(osThread(thread_pwm), 
                                 NULL);
  
  thread_GPIO_id = osThreadCreate(osThread(thread_gpio), 
                                  NULL);
  
  osKernelStart();
  
  osDelay(osWaitForever);
  
  return;
}

void SystemStart(void)
{
  //
  SystemCoreClockUpdate();
  
  // Inicializa General I/O
  GPIOInit();
  
  // Inicializa SSP (necessario para oled)
  SSPInit();
  
  // Inicializa o display
  oled_init();  
   
  return;
}