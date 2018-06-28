#include "gui.h"
#include "oled.h"
#include "pwm.h"
#include "Auxiliar.h"
#include "encoder.h"

// Declare a message queue
osMessageQDef(guiMessage_q,
              5,
              GUI_MESSAGES);

osMessageQId guiMessage_q;

static void guiInit(void);

static void guiChangeScreen(void);

static void guiUpdateScreen(void);

static void guiDrawMainScreen(void);

static void guiDrawInstructionScreen(void);

static GUI_SCREEN_ENUM currentScreen = MAIN_SCREEN;

/**
 *
 */
void thread_gui(void const *argument)
{
  osEvent event;
  
  // create the message queue inside the thread
  guiMessage_q = osMessageCreate(osMessageQ(guiMessage_q),
                                 NULL);
  
  thread_gui_writeMessage(INIT_DISPLAY);
  
  while(DEF_TRUE)
  {
    event = osMessageGet(guiMessage_q, 
                         osWaitForever);
    
    if(event.status == osEventMessage)
    {
      switch(event.value.v)
      {
        case INIT_DISPLAY:
          guiInit();
         
          break;
          
        case CHANGE_SCREEN:
          guiChangeScreen();
          break;
          
        case UPDATE_SCREEN:
          guiUpdateScreen();
          break;
            
        default:
          break;
      }
    }
  }
  
  return;
}

/**
 *
 */
void guiInit(void)
{
  // Inicializa o display
  oled_init();
  
  //
  guiDrawMainScreen();
  
  return;
}

/**
 *
 */
void guiChangeScreen(void)
{
  if(currentScreen == MAIN_SCREEN)
  {
    guiDrawInstructionScreen();
    
    currentScreen = INSTRUCTION_SCREEN;
  }
  
  else if(currentScreen == INSTRUCTION_SCREEN)
  {
    guiDrawMainScreen();
    
    currentScreen = MAIN_SCREEN;
  }
  
  return;
}

void guiDrawMainScreen(void)
{
  static uint32_t lastValuePWMMotor1 = 0;
  static uint32_t lastValuePWMMotor2 = 0;
  
  if((currentScreen == MAIN_SCREEN) && ((lastValuePWMMotor1 == pwmMotor1) && (lastValuePWMMotor2 == pwmMotor2)))
  {
    osThreadYield();
  }
  
  else
  {
    uint8_t pwmMotor1String[10];
    uint8_t pwmMotor2String[10]; 
    
    intToString(pwmMotor1, 
                pwmMotor1String, 
                6,
                10); 
    
    intToString(pwmMotor2, 
                pwmMotor2String, 
                6,
                10);
    
    //
    oled_clearScreen(OLED_COLOR_WHITE);
    
    //
    oled_putString(5,
                   1,
                   (uint8_t*)"Laboratorio 03",
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);
    
    oled_putString(10,
                   20,
                   (uint8_t*)"PWM 1: ",
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);

    oled_putString(60,
                   20,
                   pwmMotor1String,
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);
    
    oled_putString(75,
                   20,
                   (uint8_t*)"%",
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);
    
    oled_putString(10,
                   40,
                   (uint8_t*)"PWM 2: ",
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);

    oled_putString(60,
                   40,
                   pwmMotor2String,
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);
    
    oled_putString(75,
                   40,
                   (uint8_t*)"%",
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);
    
    lastValuePWMMotor1 = pwmMotor1;
    
    lastValuePWMMotor2 = pwmMotor2;
  }
  
  return;
}

void guiDrawInstructionScreen(void)
{
  if(currentScreen == INSTRUCTION_SCREEN)
  {
    osThreadYield();
  }
  
  else
  {
    oled_clearScreen(OLED_COLOR_WHITE);
    
    oled_putString(15,
                   1,
                   (uint8_t*)"Instrucoes",
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);
    
    oled_putString(1,
                   15,
                   (uint8_t*)"2/8: Acel/Freia",
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);
    
    oled_putString(1,
                   25,
                   (uint8_t*)"5: Para",
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);
    
    oled_putString(1,
                   35,
                   (uint8_t*)"4/6: Rot D/E",
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);
    
    oled_putString(1,
                   45,
                   (uint8_t*)"1/3: Frente D/E",
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);
    
    oled_putString(1,
                   55,
                   (uint8_t*)"7/9: Re D/E",
                   OLED_COLOR_BLACK, 
                   OLED_COLOR_WHITE);
  }

  return;
}

void guiUpdateScreen(void)
{
  if(currentScreen == MAIN_SCREEN)
  {
    guiDrawMainScreen();
  }
  
  else if(currentScreen == INSTRUCTION_SCREEN)
  {
    guiDrawInstructionScreen();
  }
  
  return;
}

void thread_gui_writeMessage(GUI_MESSAGES message)
{
  osMessagePut(guiMessage_q,
               (uint32_t)message,
               osWaitForever);
  
  return;
}