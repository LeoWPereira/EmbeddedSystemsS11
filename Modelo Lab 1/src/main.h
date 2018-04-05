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

#define P2                    2
#define P5                    5

//#define PGM_FILENAME           "teste5x5.pgm"
//#define PGM_FILENAME_OUT       "teste5x5_FILTERED.pgm"
//#define PGM_FILENAME           "teste24x7.pgm"
//#define PGM_FILENAME_OUT       "teste24x7_FILTERED.pgm"
#define PGM_FILENAME             "binary.pgm"
#define PGM_FILENAME_OUT         "binary_FILTERED.pgm"
//#define PGM_FILENAME             "lena512.pgm"
//#define PGM_FILENAME_OUT         "lena512_FILTERED.pgm"

#define ERROR_FOPEN                    "ERROR: File could not be opened"
#define ERROR_FGETS                    "ERROR: File could not be read"
#define ERROR_TYPE_NOT_SUPPORTED       "ERROR: File format not supported"
#define ERROR_TYPE_SIZE_NOT_READ       "ERROR: Could not read image size"
#define ERROR_TYPE_MAX_GRAY_VALUE      "ERROR: Could not read max. gray value"

/* Externable Variables ------------------------------------------------------*/



/* Externable Functions Definition -------------------------------------------*/

extern uint32_t meanfilter3(uint16_t dim_x,
                            uint16_t dim_y,
                            uint8_t  img_in[],
                            uint8_t  img_out[]);

#endif /* __MAIN_H */
