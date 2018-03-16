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

typedef struct {
     uint8_t fileType;
       
     uint16_t width;
     uint16_t height;
     
     uint16_t maxGrayValue;
     
     uint8_t *data;
} PGMImage;

/* Private define ------------------------------------------------------------*/

#define P2                    2
#define P5                    5

#define PGM_FILENAME          "teste24x7.pgm"

#define ERROR_FOPEN           "File could not be opened"

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private Function Prototypes -----------------------------------------------*/

void informError(uint8_t* str);

uint8_t readPGM(FILE *fp,
                PGMImage *stPGM);

/* Private Functions Declaration ---------------------------------------------*/

int main()
{
   FILE *myFile;
   
   PGMImage *pgmImage;
   
   myFile = fopen(PGM_FILENAME, 
                  "r");
    
   if(!myFile)
   {
      informError(ERROR_FOPEN);
     
      return 1;
   }
   
   readPGM(myFile,
           pgmImage);
   
   /*int i;  
   
   i = meanfilter3(4, 9, 0, 0);*/
   
   return 0;
}

/**
 * @brief
 */
void informError(uint8_t* str)
{
   printf((char *)str);
  
   return;
}

uint8_t readPGM(FILE *fp,
                PGMImage *stPGM)
{
   char buffer[128];
   
   //read image format
   if (!fgets(buffer, sizeof(buffer), fp)) 
   {
      return 1;
   }
  
   //check the image format
   if(buffer[0] != 'P')
   { 
      return 1;
   }
   
   if(buffer[1] == '2')
   {
      stPGM->fileType = P2;
   }
   
   else if(buffer[1] == '5')
   {
      stPGM->fileType = P5;
   }
   
   return 0;
}
