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

#define MASK_SIZE                                           3

/* Externable Variables ------------------------------------------------------*/



/* Externable Functions Definition -------------------------------------------*/

extern uint32_t meanfilter3(uint16_t dim_x,
                            uint16_t dim_y,
                            uint8_t  img_in[],
                            uint8_t  img_out[]);

#endif /* __MAIN_H */
