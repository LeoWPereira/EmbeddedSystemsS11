 /**
 *  @file    asm.s
 *  @author: leonardo.pereira
 *  @author: rodrigo.endo
 *  @author: juliano.eloi
 *  @version v1.0
 *  @date    14 de mar de 2018
 *  @brief
 */
 
 PUBLIC meanfilter3

   SECTION .text : CODE (2)
   THUMB


/**
 * @brief   
 * @param   R0 : dim_x
 * @param   R1 : dim_y
 * @param   R2 : img_in[]
 * @param   R3 : img_out[]
 * @retval  R0 : total pixels written on img_out[]
 */
meanfilter3:
   PUSH         {R0, R3-R11, LR}
   SUB          SP, SP, #0x8

   // R3[0..1] vai armazenar dim_x_imagem_saida (dim_x - MASK_SIZE + 1)
   // R3[3..2] vai armazenar dim_y_imagem_saida (dim_y - MASK_SIZE + 1)
   SUBS         R3, R0, #0x2 // 0x2 = MASK_SIZE - 1
   SUBS         R10, R1, #0x2
   ADD          R3, R3, R10, LSL #0x10
   
   MOV          R0, R1
   
   //
   // uint32_t totalPixelsImagemSaida = 0
   //
   MOVS         R1, #0
   
   //
   // uint32_t posicaoAtualSaida = 0
   //
   MOV          R8, R1
   
   //
   // uint16_t colunas = 0
   //
   MOVS         R0, #0x0
   
   //
   // uint16_t linhas = 0
   //
   MOV          R5, R0
   
   // compara dim_x_imagem_saida
   UBFX         R6, R3, #0x0, #0x10
   CMP          R6, #0x1
   BLT          ACABA_FILTRO
   
   MOV          R10, #0x1
   RSB          R4, R10, R3, LSR #0x10
   
   LDRH         R10, [SP, #0x8]
   
   STR          R4, [SP, #0x4]
   
  //
  // for(; colunas < dim_x_imagem_saida; colunas++)
  //
LOOP_COLUNAS_IMAGEM_SAIDA:

    //
    // linha1 = img_in[posicaoAtualEntrada] + img_in[posicaoAtualEntrada + 1] + img_in[posicaoAtualEntrada + 2] 
    //
    LDR         R12, [R2]
    UBFX        R4, R12, #0x8, #0x8
    UBFX        R9, R12, #0x10, #0x8
    BFC         R12, #0x8, #0x18
    ADD         R12, R12, R4
    ADD         R12, R12, R9
      
    //
    // posicaoAtualEntrada += dim_x
    //
    
    //
    // linha2 = img_in[posicaoAtualEntrada] + img_in[posicaoAtualEntrada + 1] + img_in[posicaoAtualEntrada + 2]
    //
    
    LDR         R9, [R10, R2]
    UBFX        R7, R9, #0x8, #0x8
    UBFX        R4, R9, #0x10, #0x8
    BFC         R9, #0x8, #0x18
    ADD         R9, R9, R7
    ADD         R4, R4, R9
    
    // Compara dim_y_imagem_saida com 0x1
    UBFX        R7, R3, #0x10, #0x10
    CMP         R7, #0x1
    BLT         FIM_LOOP_LINHAS_IMAGEM_SAIDA

    // Compara linhas (R5) com dim_y_imagem_saida
    CMP         R5, R3, LSR #0x10
    BGE         FIM_LOOP_LINHAS_IMAGEM_SAIDA
    
    //
    // for(; linhas < dim_y_imagem_saida; linhas++)
    // 
LOOP_LINHAS_IMAGEM_SAIDA:
    
    //
    // posicaoAtualEntrada += dim_x
    //
    LDRH        R7, [SP, #0x8]
    ADD         R10, R10, R7
    
    //
    // linha3 = img_in[posicaoAtualEntrada] + img_in[posicaoAtualEntrada + 1] + img_in[posicaoAtualEntrada + 2]
    //
    
    LDR         R7, [R10, R2]
    UBFX        R11, R7, #0x8, #0x8
    UBFX        R9, R7, #0x10, #0x8
    BFC         R7, #0x8, #0x18
    ADD         R7, R7, R11
    ADD         R9, R9, R7
    
    //
    // img_out[posicaoAtualSaida] = (((linha1 + linha2 + linha3) * (uint32_t)0xE38F) >> 17) >> 2
    //
    ADD         R7, R4, R12
    ADD         R7, R7, R9
    // Realiza divisao a partir de multiplicacao e shift
    MOV         R11, #0xE38F
    MUL         R7, R7, R11
    LSRS        R7, R7, #0x13
    LDR         R11, [SP, #0xC]
    STRB        R7, [R8, R11]
    
    //
    // totalPixelsImagemSaida++
    //
    ADDS        R1, R1, #0x1
    
    //
    // if(linhas < (dim_y_imagem_saida - 1))
    //
    LDR         R7, [SP, #0x4]
    
    CMP         R5, R7
    BGE         FIM_LOOP_COLUNAS_IMAGEM_SAIDA
    
    //
    // posicaoAtualSaida += dim_x_imagem_saida
    //
    // carrega dim_x_imagem_saida em R7
    UBFX         R7, R3, #0x0, #0x10
    
    ADD         R8, R8, R7
    
    //
    // linha1 = linha2
    //
    MOV         R12, R4
    
    //
    // linha2 = linha3
    //
    MOV         R4, R9
    
FIM_LOOP_COLUNAS_IMAGEM_SAIDA:
    ADDS        R5, R5, #0x1
    
    // compara dim_y_imagem_saida
    CMP         R5, R3, LSR #0x10
    BLT         LOOP_LINHAS_IMAGEM_SAIDA
    
FIM_LOOP_LINHAS_IMAGEM_SAIDA:
    
    //
    // linhas = 0
    //
    MOVS         R5, #0x0
    
    //
    // posicaoAtualSaida = (colunas + 1)
    //
    ADD         R8, R0, #0x1
    
    //
    // verifica loop colunas
    //
    MOV         R0, R8
    MOV         R10, R0
    ADDS        R6, R6, #0x1
    
    // carrega dim_x_imagem_saida em R4
    UBFX        R4, R3, #0x0, #0x10
    
    CMP         R8, R4
    BLT         LOOP_COLUNAS_IMAGEM_SAIDA
   
ACABA_FILTRO:
    MOV         R0, R1
    ADD         SP, SP, #0x10
   
    POP         {R4-R11, PC}

    END