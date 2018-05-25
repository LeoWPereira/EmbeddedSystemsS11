osThreadId thread_Timer_id;
osThreadId thread_GUI_id;
osThreadId thread_Encoder_id;
osThreadId thread_Control_id;
osThreadId thread_PWM_id;

int main()
{
  osKernelInitialize();
  SystemInit();
  
  // System thread initialization
  
  osKernelStart();
  osDelay(osWaitForever);
  
  return 0;
}
