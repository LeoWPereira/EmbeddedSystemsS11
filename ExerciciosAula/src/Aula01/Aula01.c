/**
 *      .text   -> c�digo-objeto (fun��es)                                                      -> FLASH
 *      .rodata -> constantes                                                                   -> FLASH
 *      .data   -> vari�veis inicializadas com valores espec�ficos (vari�veis globais/est�ticas)-> RAM
 *      .bss    -> vari�veis n�o inicializadas (zeradas, mas apenas globais/est�ticas)          -> RAM
 *      CSTACK  -> fun��es (passagem de par�metro e vari�veis dentro de fun��es)                -> RAM
 *      HEAP    -> aloca��o din�mica de mem�ria (malloc / free)                                 -> RAM
 */

/**
 *      - Qual a diferen�a entre declara��o e defini��o de vari�vel?
 *         . Declara��o n�o ocupa espa�o em mem�ria, enquanto defini��o sim!
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