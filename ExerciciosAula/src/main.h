/**
 *  @file    main.h
 *  @author: leonardo.pereira
 *  @author: rodrigo.endo
 *  @author: juliano.eloi
 *  @version v1.0
 *  @date    14 de mar de 2018
 *  @brief
 */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>

/* Externable defines --------------------------------------------------------*/

/* Externable Variables ------------------------------------------------------*/

/* Externable Functions Definition -------------------------------------------*/

extern void Aula03_Ex01(void);
extern void Aula03_Ex02(void);

extern unsigned long long Aula03_Ex03(uint32_t valorASerMultiplicado,
                                      uint32_t numeroDeVezes);

extern void soma_vet(int m, int A[], int B[], int S[]);

#endif /* __MAIN_H */
