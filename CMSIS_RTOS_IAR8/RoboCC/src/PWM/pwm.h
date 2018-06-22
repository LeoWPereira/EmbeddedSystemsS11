/**
 *
 */

#ifndef __PWM_H__
#define __PWM_H__

/****************************************************************************************
 * DEPENDENCIAS
 ****************************************************************************************/

/****************************************************************************************
 * CONSTANTES E MACROS
 ****************************************************************************************/

#define REGISTER_PWM_CYCLE_BASE         LPC_IOCON->R_PIO0_11       

#define REGISTER_H_BRIDGE_MOTOR_1       LPC_IOCON->PIO1_4
#define REGISTER_H_BRIDGE_MOTOR_2       LPC_IOCON->PIO1_5
   
#define REGISTER_PWM_MOTOR_1            LPC_IOCON->PIO1_6
#define REGISTER_PWM_MOTOR_2            LPC_IOCON->PIO1_7
   
#define REGISTER_TCR_PWM_MOTORES        LPC_TMR32B0->TCR
#define REGISTER_CONTROL_PWM_MOTORES    LPC_TMR32B0->PWMC
#define REGISTER_MCR_PWM_MOTORES        LPC_TMR32B0->MCR
#define REGISTER_MR3_PWM_MOTORES        LPC_TMR32B0->MR3
#define REGISTER_MR0_MOTOR_1            LPC_TMR32B0->MR0
#define REGISTER_MR1_MOTOR_2            LPC_TMR32B0->MR1

#define REGISTER_PWM_CYCLE_LENGTH       4096 //(17.8 kHz)
#define PWM_PACE                        30
#define MINIMUM_PWM_VALUE               PWM_PACE

/****************************************************************************************
 * DEFINICOES DE TIPOS E ESTRUTURAS
 ****************************************************************************************/

extern uint32_t pwmMotor1;
extern uint32_t pwmMotor2;
   
typedef enum 
{
  INIT_PWM,
  INC_PWM_1_VALUE,
  INC_PWM_2_VALUE,
  DEC_PWM_1_VALUE,
  DEC_PWM_2_VALUE,
  HB_FORWARD,
  HB_BACK,
  HB_ROTATE_LEFT,
  HB_ROTATE_RIGHT
} PWM_MESSAGES;

typedef enum
{
  MOTOR_1,
  MOTOR_2
} PWM_MOTORS;

typedef enum
{
  H_BRIDGE_FORWARD,
  H_BRIDGE_BACK,
  H_BRIDGE_ROTATE_LEFT,
  H_BRIDGE_ROTATE_RIGHT
} H_BRIDGE_STATE;

/****************************************************************************************
 * DEFINICOES DE FUNCOES
 ****************************************************************************************/

extern void thread_pwm(void const *argument);

extern void thread_pwm_writeMessage(PWM_MESSAGES message);

extern void thread_pwm_setDirection(H_BRIDGE_STATE _state);

#endif