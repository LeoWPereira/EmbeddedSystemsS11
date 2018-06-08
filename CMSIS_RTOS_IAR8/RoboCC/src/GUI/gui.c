#include "gui.h"
#include "oled.h"

// Declare a message queue
osMessageQDef(guiMessage_q,
              5,
              GUI_MESSAGES);

osMessageQId guiMessage_q;

static void guiInit(void);

static void guiChangeScreen(void);

static void guiDrawMainScreen(void);

static void guiDrawInstructionScreen(void);

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
  static GUI_SCREEN_ENUM currentScreen = MAIN_SCREEN;
  
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
  //
  oled_clearScreen(OLED_COLOR_WHITE);
  
  //
  oled_putString(5,
                 1,
                 (uint8_t*)"Laboratorio 03",
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

void thread_gui_writeMessage(GUI_MESSAGES message)
{
  osMessagePut(guiMessage_q,
               (uint32_t)message,
               osWaitForever);
  
  return;
}