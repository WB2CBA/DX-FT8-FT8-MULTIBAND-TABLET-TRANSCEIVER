/*
 * Display.h
 *
 *  Created on: Feb 8, 2016
 *      Author: user
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include	"arm_math.h"


#define FFT_H  40

#define FFT_Resolution 6.25  //8000/2/1280

int FT_8_TouchIndex;
int FT_8_MessageIndex;

//uint16_t ft8_scale;

uint16_t cursor;
//char ft8_time_string[9];
char rtc_date_string[9];
char rtc_time_string[9];
//char date_time_string[25];
int decode_flag;
//int display_flag;

int FT8_Touch_Flag;
int FT8_Message_Touch;


void show_variable(uint16_t x, uint16_t y,int variable);

void show_short(uint16_t x, uint16_t y,uint8_t variable);

void show_wide(uint16_t x, uint16_t y,int variable);


void show_UTC_time(uint16_t x, uint16_t y,int utc_hours,int utc_minutes,int utc_seconds, int color);

void show_Real_Date(uint16_t x, uint16_t y,int date,int month,int year);

//void show_hz(uint16_t x, uint16_t y,uint32_t variable);


void setup_display(void);

//void Display_FFT(void);

void Process_Touch (void);

uint16_t FFT_Touch(void);

int FT8_Touch(void);


void Init_Waterfall (void);

void Display_WF(void);

int Xmit_message_Touch(void);

void Set_Cursor_Frequency(uint16_t cursor_pos);

void update_log_display(int mode);

void update_Beacon_log_display(int mode);


#endif /* DISPLAY_H_ */
