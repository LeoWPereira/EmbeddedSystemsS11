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
   MOV          R0, R1 // porque?
   
   //
   // uint32_t totalPixelsImagemSaida = 0
   //
   MOVS         R1, #0 // porque?
   
   //
   //uint16_t dim_x_imagem_saida = (dim_x - MASK_SIZE + 1);
   //
   
   
   //
   //uint16_t dim_y_imagem_saida = (dim_y - MASK_SIZE + 1);
   //
   
   //
   //uint32_t posicaoAtualEntrada = 0;
   //
   
   //
   //uint32_t posicaoAtualSaida = 0;
   //
   
   //
   //uint16_t linha1;
   //
   
   //
   //uint16_t linha2;
   //
   
   //
   //uint16_t linha3;
   //
   
   //
   //uint16_t colunas = 0;
   //
   
   //
   //uint16_t linhas = 0;
   //
   
   
   bx lr

   END