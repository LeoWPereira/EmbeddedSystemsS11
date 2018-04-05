 /**
 *  @file    asm.s
 *  @author: leonardo.pereira
 *  @version v1.0
 *  @date    14 de mar de 2018
 *  @brief
 */
 
 PUBLIC exercicio07

   SECTION .text : CODE (2)
   THUMB


/**
 * @brief   
  */
exercicio07:
START:
   cmp R0, R1
   
   beq STOP
   
   ite HI
   subhi R0, R0, R1
   subls R1, R1, R0
   
   b START

STOP:
   
   bx lr

   END
