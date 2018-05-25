#include "gui.h"

// Declare a message queue
osMessageQDef(guiMessage_q,
              5,
              GUI_MESSAGES);

// Declare an ID for the message queue
osMessageQId(guiMessage_q_id);

static void guiInit(void);

static void guiChangeScreen(void);

/**
 *
 */
void thread_gui(void const *argument)
{
  osEvent event;
  
  // create the message queue inside the thread
  guiMessage_q_id = osMessageCreate(osMessageQ(guiMessage_q),
                                    NULL);
  
  osMessagePut(guiMessage_q_id,
               (uint32_t)INIT_DISPLAY,
               osWaitForever);
  
  while(DEF_TRUE)
  {
    event = osMessageGet(guiMessage_q_id, 
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
  oled_clearScreen(OLED_COLOR_WHITE);
  
  //
  oled_putString(5,
                 1,
                 (uint8_t*)"Laboratorio 03",
                 OLED_COLOR_BLACK, 
                 OLED_COLOR_WHITE);
  
  return;
}

/**
 *
 */
void guiChangeScreen(void)
{
  oled_putString(5,
                 1,
                 (uint8_t*)"Leo Boboca",
                 OLED_COLOR_BLACK, 
                 OLED_COLOR_WHITE);
  
  return;
}