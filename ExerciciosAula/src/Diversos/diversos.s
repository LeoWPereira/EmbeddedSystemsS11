/**
 *
 */
 
  public soma_vet
  
  section .text : CODE (2)
  thumb
  
/**
 * @brief   void soma_vet(int m, int A[], int B[], int S[])
 * @param   R0 : m (32 bits)
 * @param   R1 : A (32 bits pointer)
 * @param   R2 : B (32 bits pointer)
 * @param   R3 : S (32 bits pointer)
 */
soma_vet:
  push          {R4-R11, LR}

  // Primeiro, fazemos um loop m vezes
  // R4 ira armazenar quantas vezes ja foi percorrido
  mov           R4, #0x0
  
INICIO_LOOP:
  cmp           R4, R0
  beq           FIM_LOOP
  
  // agora armazena em R5 o valor de A[R4]
  ldr           R5, [R1], #0x4
  
  // e em R6 o valor de B[R4]
  ldr           R6, [R2], #0x4
  
  // armazena a soma de R5 e R6 em R5
  add           R5, R5, R6
  
  // realiza um store do valor de R5 no vetor de saida S
  str           R5, [R3], #0x4
  
  // por fim, incrementa o valor de R4
  add           R4, R4, #0x1
  
  b             INICIO_LOOP
  
FIM_LOOP:
  ///////////////////////////////////////////////////////////////////////////////
  /// Apenas carrega o valor dos registradores para voltar a funcao chamadora ///
  ///////////////////////////////////////////////////////////////////////////////
  
  pop           {R4-R11, PC}
      
  end