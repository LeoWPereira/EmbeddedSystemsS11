/**
 *      .text   -> código-objeto (funções)                                                      -> FLASH
 *      .rodata -> constantes                                                                   -> FLASH
 *      .data   -> variáveis inicializadas com valores específicos (variáveis globais/estáticas)-> RAM
 *      .bss    -> variáveis não inicializadas (zeradas, mas apenas globais/estáticas)          -> RAM
 *      CSTACK  -> funções (passagem de parâmetro e variáveis dentro de funções)                -> RAM
 *      HEAP    -> alocação dinâmica de memória (malloc / free)                                 -> RAM
 */

/**
 *      - Qual a diferença entre declaração e definição de variável?
 *         . Declaração não ocupa espaço em memória, enquanto definição sim!
 */

char                    str1[]     = "Sistemas Embarcados\n";   // .data
char                    str2[30]   = "Curso de Engenharia\n";   // .data
char*                   str3;                                   // .bss
char                    str4[30];                               // .bss
char* const             str6 = str4;                            // .rodata
const char* const       str7 = str4;                            // .rodata

void Aula01_Ex01(void)
{
    int i;                                                      // CSTACK
    
    i = sizeof(str1);                                           
    i = sizeof(str2);                                           
    i = sizeof(str3);                                           
    i = sizeof(str4);                                           
    
    str3 = str1;                                                
    
    return;
}