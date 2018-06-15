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
  uint8_t pwmMotor1String[5];
  uint8_t pwmMotor2String[5]; 
  
  intToString(counterMotor1/*pwmMotor1*/, 
              pwmMotor1String, 
              3,
              10); 
  
  intToString(counterMotor2/*pwmMotor2*/, 
              pwmMotor2String, 
              3,
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
                 25,
                 (uint8_t*)"PWM 1: ",
                 OLED_COLOR_BLACK, 
                 OLED_COLOR_WHITE);

  oled_putString(60,
                 25,
                 pwmMotor1String,
                 OLED_COLOR_BLACK, 
                 OLED_COLOR_WHITE);
  
  oled_putString(75,
                 25,
                 (uint8_t*)"%",
                 OLED_COLOR_BLACK, 
                 OLED_COLOR_WHITE);
  
  return;
}

void guiDrawInstructionScreen(void)
{
  //
  oled_clearScreen(OLED_COLOR_WHITE);
  
  oled_putString(5,
                 1,
                 (uint8_t*)"Leo Boboca",
                 OLED_COLOR_BLACK, 
                 OLED_COLOR_WHITE);

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