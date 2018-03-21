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

//#define PGM_FILENAME           "teste5x5.pgm"
//#define PGM_FILENAME_OUT       "teste5x5_FILTERED.pgm"
#define PGM_FILENAME             "lena512.pgm"
#define PGM_FILENAME_OUT         "lena512_FILTERED.pgm"

#define ERROR_FOPEN                    "ERROR: File could not be opened"
#define ERROR_FGETS                    "ERROR: File could not be read"
#define ERROR_TYPE_NOT_SUPPORTED       "ERROR: File format not supported"
#define ERROR_TYPE_SIZE_NOT_READ       "ERROR: Could not read image size"
#define ERROR_TYPE_MAX_GRAY_VALUE      "ERROR: Could not read max. gray value"

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
       
   memset(pgmImage, 
          0x00,
          sizeof(PGMImage));
   
   myFile = fopen(PGM_FILENAME, 
                  "r");
   
   outFile = fopen(PGM_FILENAME_OUT, 
                   "w");
    
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
      fscanf(myFile, "%c", &pgmImage->data[i]);
   }
    
   fclose(myFile);
      
   totalPixelsImagemSaida = meanfilter3(pgmImage->width, 
                                        pgmImage->height, 
                                        pgmImage->data, 
                                        filteredImage);
   
   //////////////////////////////////
   /// Save filteredImage to file ///
   //////////////////////////////////
   
   fprintf(outFile, "P5\n# Created by Leonardo Winter Pereira\n509 509\n255\n%s", filteredImage);
   
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
   
   memset(&buffer, 
          0x00,
          sizeof(buffer));
   
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

uint32_t meanfilter3(uint16_t dim_x,
                     uint16_t dim_y,
                     uint8_t  img_in[],
                     uint8_t  img_out[])
{
   /////////////////////
   /// Variable Init ///
   /////////////////////
  
   uint32_t totalPixelsImagemSaida = 0;
   
   uint16_t dim_x_imagem_saida = (dim_x - MASK_SIZE + 1);
   uint16_t dim_y_imagem_saida = (dim_y - MASK_SIZE + 1);
   
   uint32_t posicaoAtualEntrada = 0;
   uint32_t posicaoAtualSaida = 0;
   
   uint16_t linha1;
   uint16_t linha2;
   uint16_t linha3;
   
   uint16_t colunas = 0;
   uint16_t linhas = 0;
   
   ////////////
   /// Code ///
   ////////////
   
   for(; colunas < dim_x_imagem_saida; colunas++)
   {
      // init first two column sums
      posicaoAtualEntrada = colunas + (linhas * dim_x);
      linha1 = img_in[posicaoAtualEntrada] + img_in[posicaoAtualEntrada + 1] + img_in[posicaoAtualEntrada + 2]; // 11 ciclos de clock
      
      posicaoAtualEntrada += dim_x;
      linha2 = img_in[posicaoAtualEntrada] + img_in[posicaoAtualEntrada + 1] + img_in[posicaoAtualEntrada + 2];
         
      for(; linhas < dim_y_imagem_saida; linhas++)
      {   
         posicaoAtualEntrada += dim_x;
         linha3 = img_in[posicaoAtualEntrada] + img_in[posicaoAtualEntrada + 1] + img_in[posicaoAtualEntrada + 2];
         
         img_out[posicaoAtualSaida] = (((linha1 + linha2 + linha3) * (uint32_t)0x7200) >> 16) >> 2;
         //img_out[posicaoAtualSaida] = (linha1 + linha2 + linha3) / 9;
         
         totalPixelsImagemSaida++;
         
         /////////////////////////////////
         /// Apenas Incrementa valores ///
         /////////////////////////////////
         
         if(linhas < (dim_y_imagem_saida - 1))
         {
            posicaoAtualSaida += dim_x_imagem_saida;
            
            //////////////////////////////////////////////////////////
            /// Por fim, apenas faz o shuffle das somas das linhas ///
            //////////////////////////////////////////////////////////
            linha1 = linha2;
            linha2 = linha3;
         }
      }
      
      linhas = 0;
      posicaoAtualSaida = (colunas + 1);
   }
   
   return totalPixelsImagemSaida;
}
