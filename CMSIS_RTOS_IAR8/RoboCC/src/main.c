/**
 *
 */

#include "control.h"
#include "encoder.h"
#include "gui.h"
#include "pwm.h"
#include "timer.h"
#include "gpio.h"

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

static void SystemStart(void);

/**
 *
 */
int main()
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
  /*
  thread_Control_id = osThreadCreate(osThread(thread_control), 
                                     NULL);
  
  thread_PWM_id = osThreadCreate(osThread(thread_pwm), 
                                 NULL);
  */
  
  thread_GPIO_id = osThreadCreate(osThread(thread_gpio), 
                                  NULL);
  
  osKernelStart();
  osDelay(osWaitForever);
  
  return 0;
}

void SystemStart(void)
{
  //
  SystemCoreClockUpdate();
  
  // Inicializa General I/O
  GPIOInit();
  
  // Inicializa SSP (necessario para oled)
  SSPInit();
  
  // Inicializa o Timer 0 (LPC_CT32B0_BASE)
  /*timer_inicializarTimer(TIMER_INTERRUPCAO,
                         1,
                         0,
                         0);

  // Inicializa o Timer 0 (LPC_CT32B0_BASE)
  timer_inicializarTimer(TIMER_COUNTER,
                         0,
                         0,
                         0);*/
  
  GPIOSetInterrupt(PORT2,
                   9,
                   1,
                   0,
                   0);
  
  GPIOIntEnable(PORT2, 
                9);
  
  return;
}
