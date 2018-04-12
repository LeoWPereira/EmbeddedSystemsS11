/**
 *
 */
 
  public Aula03_Ex01
  public Aula03_Ex02
  
  section .text : CODE (2)
  thumb
  
/**
 * @brief   
 * @param   R0 : 
 * @param   R1 : 
 * @param   R2 : 
 * @retval  R0 : 
 */
Aula03_Ex01:
  push          {R4-R11, LR}

  // R0 <= 0
  MOV           R0, #0x0
  
  // R1 <= 200
  MOV           R1, #0xC8
  
  // R2 <= 0x1234
  MOV           R2, #0x1234
  
  // R3 <= 0xFFFFFF00
  
  
  // R4 <= 0xABCDEF00
  

  pop           {R4-R11, PC}

/**
 * @brief   
 * @param   R0 : 
 * @param   R1 : 
 * @param   R2 : 
 * @retval  R0 : 
 */
Aula03_Ex02:
  push          {R4-R11, LR}

  mov           R1, #0x3
  mov           R2, #0x5
  movs          R3, #-6
  
  add           R0, R2, R3
  adds          R0, R2, R3
  adds          R0, #0x9
  
  cmp           R0, #0x8
  
  subs          R0, #0xA
  subs          R0, R0, #0x100
  
  mov           R4, #0xBB8
  subs          R0, R0, R4
  
  asr           R0, R0, #0x5

  pop           {R4-R11, PC}
  
  end
