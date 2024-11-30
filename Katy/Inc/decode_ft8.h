/*
 * decode_ft8.h
 *
 *  Created on: Nov 2, 2019
 *      Author: user
 */

#ifndef DECODE_FT8_H_
#define DECODE_FT8_H_

int 	num_CQ_calls;
int num_calls_to_CQ_station;

typedef struct
{
    char field1[14];
    char field2[14];
    char field3[7];
    int  freq_hz;
    int  sync_score;
    int  snr;
    char target[5];
} Decode;

typedef struct
{
    char message[20];
    int  text_color;
} display_message;


typedef struct
{

	int number_times_called;
	char call[7];
	char locator[4];
	//char freq_hz[7];
	int  RSL;
	int  RR73;

} Calling_Station;

typedef struct
{
	char decode_time[10];
	char call[7];
	int  distance;
	int  snr;
	int  freq_hz;
} CQ_Station;


int Check_Calling_Stations(int num_decoded , int reply_state);
void Check_CQ_Stations(int num_decoded);
void clear_CQ_List_box(void);
void display_messages(int decoded_messages);
int Check_CQ_Calling_Stations(int num_decoded, int reply_state);
void clear_CQ_List_box(void);
void clear_messages(void);
int strindex(char s[],char t[]);
void process_selected_Station(int stations_decoded, int TouchIndex);
int Check_QSO_Calling_Stations(int num_decoded, int reply_state);
void clear_log_stored_data(void);



#endif /* DECODE_FT8_H_ */



