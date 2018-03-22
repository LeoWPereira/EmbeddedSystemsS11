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
   //PUSH 
   
   bx lr

   END