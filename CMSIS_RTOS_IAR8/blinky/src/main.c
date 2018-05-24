#include "LPC13xx.h" // CMSIS-Core
#include "gpio.h" // Lib_EABaseBoard
#include "cmsis_os.h" // CMSIS-RTOS

osThreadId thread1_id;

void thread1(void const *argument);

osThreadDef(thread1, osPriorityNormal, 1, 0);

void thread1(void const *argument)
{
   while(1)
   {
      GPIOSetValue(0, 7, 0); // apaga LED2
      
      osDelay(500);
      
      GPIOSetValue(0, 7, 1); // acende LED2
      
      osDelay(500);
   } // while
} // thread1

void main()
{
   osKernelInitialize();
   SystemInit();
   GPIOInit();
   GPIOSetDir(0, 7, 1); // LED2 como saída

   thread1_id = osThreadCreate(osThread(thread1), NULL);

   osKernelStart();
   osDelay(osWaitForever);
} // main