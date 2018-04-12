/**
 *
 */
 
  public Aula03_Ex01
  public Aula03_Ex02
  public Aula03_Ex03
  
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
  
  //R3 <= 0xFFFFFF00
  MOV           R3, #0xFF00
  MOVT          R3, #0xFFFF
  
  // R4 <= 0xABCDEF00
  MOV           R3, #0xEF00
  MOVT          R3, #0xABCD

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

/**
 * Exercicio 03 ->      Analise o valor do registrador PC enquanto uma instru��o no endere�o i est� sendo executada
 *                      Explique o que descobriu, lembrando que o Cortex-M3 possui um pipeline de 3 est�gios
 *
 *                      The original ARM design had a 3-stage pipeline (fetch-decode-execute). 
 *                      To simplify the design they chose to have the PC read as the value currently on the instruction fetch address lines, 
 *                      rather than that of the currently executing instruction from 2 cycles ago. 
 *                      Since most PC-relative addresses are calculated at link time, it's easier to have the assembler/linker compensate for that 2-instruction 
 *                      offset than to design all the logic to 'correct' the PC register.
 */
 
 /**
 * @brief   
 * @param   R0 : 
 * @param   R1 : 
 * @param   R2 : 
 * @retval  R0 : 
 */
Aula03_Ex03:
  push          {R4-R11, LR}

  // Multiplica valor em R3(32 bits) por 9 
  // Lembrando que a multiplica��o pode causar overflow
  // precisamos usar UMULL
  mov           R3, #0xFFFFFFFF
  mov           R2, #0x9
  umull         R0, R1, R3, R2
  
  // usando um loop de somas
  mov           R3, #0xFFFFFFFF
  mov           R2, #0x9
  mov           R4, #0x0 // armazena a quantidade de vezes que ja somou (para cmp do loop)
  
  mov           R1, #0x0 // armazena a soma (Lowest 32 bits)
  mov           R0, #0x0 // armazena a soma (highest 32 bits)
REALIZA_SOMA:
  adds          R1, R1, R3
  
  
  
  add           R4, R4, #0x1
  cmp           R4, R2
  bneq          REALIZA_SOMA
  
  pop           {R4-R11, PC}
      
  end
