/*
 * log_file.h
 *
 *  Created on: Oct 29, 2019
 *      Author: user
 */

#ifndef LOG_FILE_H_
#define LOG_FILE_H_

#include "arm_math.h"


//typedef struct {
//	uint32_t Total; /*!< Total size of memory */
//	uint32_t Free;  /*!< Free size of memory */
//} TM_FATFS_Size_t;


//int FT8_Day, FT8_Month, FT8_Year;


void Write_Log_Data( char *ch );
void Close_Log_File( void);
void Open_Log_File( void );
//void set_log_file_name(void);
#endif /* LOG_FILE_H_ */
