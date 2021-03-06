/**
 *  @file    main.c
 *  @author: leonardo.pereira
 *  @author: rodrigo.endo
 *  @author: juliano.eloi
 *  @version v1.0
 *  @date    14 de mar de 2018
 *  @brief   References:
 *             - http://dainf.ct.utfpr.edu.br/~hvieir/download/pdi99.pdf (secao 4.2.2)
 *             - http://netpbm.sourceforge.net/doc/pgm.html
 *             - http://infocenter.arm.com/help/topic/com.arm.doc.espc0002/ATPCS.pdf
 *             - https://homepages.inf.ed.ac.uk/rbf/HIPR2/mean.htm
 *             - https://homepages.inf.ed.ac.uk/rbf/HIPR2/median.htm
 *          
 *           Ideas for maximum performance:
 *             - The basic 2D convolution algorithm is pretty bad, we could optimize it by following this link:
 *                . https://stackoverflow.com/questions/5923696/efficient-2d-mean-filter-implementation-that-minimises-redundant-memory-loads
 *
 *             - As ARM Cortex M3 uses 32 bits alignment, let's use it for reading the entire mask at once
 *                .
 *
 *             - Division is way slower than ohter arithmetic operations, let's use it in our favor
 *                . "Division by Invariant Multiplication"
 *                . https://embeddedgurus.com/stack-overflow/2009/06/division-of-integers-by-constants/
 *                . https://stackoverflow.com/questions/41183935/why-does-gcc-use-multiplication-by-a-strange-number-in-implementing-integer-divi
 *                . https://stackoverflow.com/questions/19844575/arm-division-how-to-do-it
 *
 *          Diagramas de Atividades (UML) :   
 *             - https://creately.com/app?diagid=jesh3c0z1
 *             - https://creately.com/app?diagid=jesjme8s1
 *             - https://creately.com/app?diagid=jesjme8s2
 */

#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private Function Prototypes -----------------------------------------------*/

/* Private Functions Declaration ---------------------------------------------*/

int main()
{  
    //Aula03_Ex01();
    //Aula03_Ex02();
    
    //unsigned long long valor = Aula03_Ex03(0xFFFFFFFF,
    //                                       9);
  
    /*int m = 5;
    int A[5] = {1, 2, 3, 4, 5};
    int B[5] = {1, -1, 1, -1, 1};
    int S[5];
  
    soma_vet(m, 
             A,
             B,
             S);*/
    
    return 0;
}