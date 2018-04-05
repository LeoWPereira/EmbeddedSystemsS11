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
   FILE *outFile;
   
   PGMImage *pgmImage;
   
   uint8_t *filteredImage;
   
   uint32_t sizeOriginalImage = 0;
   uint32_t sizeFilteredImage = 0;
   
   uint32_t totalPixelsImagemSaida = 0;
   
   myFile = fopen(PGM_FILENAME, 
                  "rb");
   
   outFile = fopen(PGM_FILENAME_OUT, 
                   "wb");
    
   if(!myFile)
   {
      informError(ERROR_FOPEN);
     
      return 1;
   }
   
   if(!readPGM(myFile,
               pgmImage))
   {
      return 1;
   }
   
   /////////////////////////////////////////////
   /// Agora, alocar memoria para as imagens ///
   /////////////////////////////////////////////
   
   sizeOriginalImage = (pgmImage->width * pgmImage->height * sizeof(uint8_t));
   sizeFilteredImage = ((pgmImage->width - MASK_SIZE + 1) * (pgmImage->height - MASK_SIZE + 1) * sizeof(uint8_t));
   
   pgmImage->data = (uint8_t *)malloc(sizeOriginalImage);
   
   filteredImage  = (uint8_t *)malloc(sizeFilteredImage);
   
   //////////////////////////////////////////////////////
   ///   Depois de alocado corretamente os buffers,   ///
   /// preencher a imagem original e aplicar o filtro ///
   //////////////////////////////////////////////////////
    
   for(uint32_t i = 0; i < sizeOriginalImage; i++)
   {
      pgmImage->data[i] = getc(myFile);
   }
    
   fclose(myFile);
      
   totalPixelsImagemSaida = meanfilter3(pgmImage->width, 
                                        pgmImage->height, 
                                        pgmImage->data, 
                                        filteredImage);
   
   //////////////////////////////////
   /// Save filteredImage to file ///
   //////////////////////////////////
   
   fprintf(outFile, "P5\n# Created by Leonardo Winter Pereira\n%d %d\n%d\n", (pgmImage->width - MASK_SIZE + 1), (pgmImage->height - MASK_SIZE + 1), pgmImage->maxGrayValue);
   
   for(uint32_t i = 0; i < sizeFilteredImage; i++)
   {
      putc(filteredImage[i], outFile);
   }
   
   fclose(outFile);
   
   free(pgmImage->data);
   free(filteredImage);
   
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
   char buffer[4];
   
   //////////////////////////
   ///  Read Image Format ///
   //////////////////////////
   
   // will read til the first new line character
   if (!fgets(buffer, sizeof(buffer), fp)) 
   {
      informError(ERROR_FGETS);
      
      return 0;
   }
  
   //check the image format
   if(buffer[0] != 'P')
   { 
      informError(ERROR_TYPE_NOT_SUPPORTED);
      
      return 0;
   }
   
   if(buffer[1] == '2')
   {
      stPGM->fileType = P2;
   }
   
   else if(buffer[1] == '5')
   {
      stPGM->fileType = P5;
   }
   
   ///////////////////////
   /// Read Commentary ///
   ///////////////////////
   
   //check for comments
   uint8_t c = getc(fp);
   
   if(c != '#')
   {
      c = getc(fp);
   }
   
   while (c == '#') 
   {
      while (getc(fp) != '\n');
      
      c = getc(fp);
   }
   
   ungetc(c, fp);
   
   //read image size information
   if (fscanf(fp, "%d %d", &stPGM->width, &stPGM->height) != 2) 
   {
      informError(ERROR_TYPE_SIZE_NOT_READ);
      
      return 0;
   }

   //read rgb component
   if (fscanf(fp, "%d", &stPGM->maxGrayValue) != 1) 
   {
      informError(ERROR_TYPE_MAX_GRAY_VALUE);
      
      return 0;
   }
   
   while (getc(fp) != '\n');
   
   return 1;
}
