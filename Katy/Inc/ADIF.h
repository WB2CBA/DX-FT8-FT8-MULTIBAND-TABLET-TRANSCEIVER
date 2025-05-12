/*
 * ADIF.h
 *
 *  Created on: Jun 18, 2023
 *      Author: Charley
 */

#ifndef ADIF_H_
#define ADIF_H_


typedef struct
{
    char text[24];
    char data[24];
    char log_item[24];
    int  fixed;
    int  length;
} ADIF_Label;

//void write_ADIF_Log(int index);
void write_ADIF_Log(void);
#endif /* ADIF_H_ */
