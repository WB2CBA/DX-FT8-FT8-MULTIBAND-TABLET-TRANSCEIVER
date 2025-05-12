/*
 * decode_ft8.c
 *
 *  Created on: Sep 16, 2019
 *      Author: user
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <gen_ft8.h>

#include "unpack.h"
#include "ldpc.h"
#include "decode.h"
#include "constants.h"
#include "encode.h"
#include "button.h"

#include "Process_DSP.h"
#include "display.h"
#include "stm32746g_discovery_lcd.h"
#include "log_file.h"
#include "decode_ft8.h"
#include "traffic_manager.h"
#include "ADIF.h"
#include "DS3231.h"

//char erase[] = "                   ";

const int kLDPC_iterations = 20;
const int kMax_candidates = 20;
const int kMax_decoded_messages = 20;  //chhh 27 feb
const int kMax_message_length = 20;
const int kMin_score = 40;		// Minimum sync score threshold for candidates

int validate_locator(char locator[]);
int strindex(char s[],char t[]);

extern FreqStruct sBand_Data[];

extern uint32_t ft8_time;

Decode new_decoded[20];  //chh 27 Feb

extern char current_QSO_receive_message[];
display_message display[10];

Calling_Station Answer_CQ[50];  //
int log_size = 50;
//CQ_Station Calling_CQ[8];

int 	num_calls;  // number of unique calling stations
//int max_displayed_CQ = 5;
int message_limit = 10;
int ft8_decode(void) {


	//int  store_hz;
	//char store_frequency[14];
    // Find top candidates by Costas sync score and localize them in time and frequency
    Candidate candidate_list[kMax_candidates];

    int num_candidates = find_sync(export_fft_power, ft8_msg_samples, ft8_buffer, kCostas_map, kMax_candidates, candidate_list, kMin_score);
    char    decoded[kMax_decoded_messages][kMax_message_length];

    const float fsk_dev = 6.25f;    // tone deviation in Hz and symbol rate

    // Go over candidates and attempt to decode messages
    int     num_decoded = 0;

    for (int idx = 0; idx < num_candidates; ++idx) {
        Candidate cand = candidate_list[idx];
        float freq_hz  = (  (float)    cand.freq_offset +  (float)    cand.freq_sub / 2.0f) * fsk_dev;

        float   log174[N];
        extract_likelihood(export_fft_power, ft8_buffer, cand, kGray_map, log174);

        // bp_decode() produces better decodes, uses way less memory
        uint8_t plain[N];
        int     n_errors = 0;
        bp_decode(log174, kLDPC_iterations, plain, &n_errors);

        if (n_errors > 0)    continue;

        // Extract payload + CRC (first K bits)
        uint8_t a91[K_BYTES];
        pack_bits(plain, K, a91);

        // Extract CRC and check it
        uint16_t chksum = ((a91[9] & 0x07) << 11) | (a91[10] << 3) | (a91[11] >> 5);
        a91[9] &= 0xF8;
        a91[10] = 0;
        a91[11] = 0;
        uint16_t chksum2 = crc(a91, 96 - 14);
        if (chksum != chksum2)   continue;

        char message[kMax_message_length];

        char field1[14];
        char field2[14];
        char field3[7];
        int rc = unpack77_fields(a91, field1, field2, field3);
        if (rc < 0) continue;

        sprintf(message,"%s %s %s ",field1, field2, field3);

        _Bool found = false;

        for (int i = 0; i < num_decoded; ++i) {
            if (0 == strcmp(decoded[i], message)) {
                found = true;
                break;
            }
        }


		float raw_RSL;
		int display_RSL;


        if (!found && num_decoded < kMax_decoded_messages) {
        	if(strlen(message) < kMax_message_length) {
            strcpy(decoded[num_decoded], message);

            new_decoded[num_decoded].sync_score = cand.score;
            new_decoded[num_decoded].freq_hz = (int)freq_hz;

            strcpy(new_decoded[num_decoded].field1, field1);
            strcpy(new_decoded[num_decoded].field2, field2);
            strcpy(new_decoded[num_decoded].field3, field3);


			raw_RSL = (float)new_decoded[num_decoded].sync_score;
			display_RSL =(int)( (raw_RSL - 160 )) / 6;
			new_decoded[num_decoded].snr = display_RSL;

			char Target_Locator[] = "    ";

			strcpy(Target_Locator, new_decoded[num_decoded].field3);

			if (validate_locator(Target_Locator)  == 1) {
				strcpy(new_decoded[num_decoded].target,Target_Locator );
			}
			else {
				strcpy(new_decoded[num_decoded].target,"    " );
			}

            ++num_decoded;

        	}
        }
    }  //End of big decode loop


    return num_decoded;
}

void display_messages(int decoded_messages){

	char message[kMax_message_length];
	char CQ[] = "CQ";

	    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	    BSP_LCD_FillRect(0, FFT_H, 240, 200);
		BSP_LCD_SetFont (&Font16);

		for (int i = 0; i<decoded_messages && i<message_limit; i++ ){
		sprintf(message,"%s %s %s",new_decoded[i].field1, new_decoded[i].field2, new_decoded[i].field3);

		strcpy(display[i].message, message);


		if(strcmp(CQ, new_decoded[i].field1) == 0 )
		display[i].text_color = (int)1;
		else
		display[i].text_color = (int) 0;

		 }

		for (int j = 0; j<decoded_messages && j<message_limit; j++){
		if(display[j].text_color == 0)
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		else
		BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
		BSP_LCD_DisplayStringAt(0, 40+j*20, display[j].message,0x03);

		}
}


void clear_messages(void) {
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_FillRect(0, FFT_H, 240, 201);
}


int validate_locator(char locator[]) {

	uint8_t A1, A2, N1, N2;
	uint8_t test = 0;

	A1 = locator[0] - 65;
	A2 = locator[1] - 65;
	N1 = locator[2] - 48;
	N2= locator [3] - 48;

	if (A1 >= 0 && A1 <= 17) test++;
	if (A2 > 0 && A2 < 17) test++; //block RR73 Artic and Anartica
	if (N1 >= 0 && N1 <= 9) test++;
	if (N2 >= 0 && N2 <= 9) test++;

	if (test == 4) return 1;
	else
	return 0;
}


void clear_log_stored_data(void){

	char call_blank[] = "       ";
	char locator_blank[] = "    ";
	//char freq_blank[] = "    ";

	for(int i = 0; i < log_size; i++){
		Answer_CQ[i].number_times_called = 0;
		strcpy(Answer_CQ[i].call,call_blank);
		strcpy(Answer_CQ[i].locator,locator_blank);
		Answer_CQ[i].RSL = 0 ;
		Answer_CQ[i].RR73 = 0;
	}
}





extern char current_Beacon_receive_message[20];

int Check_Calling_Stations(int num_decoded , int reply_state) {

	int Beacon_Reply_Status = 0;
	//char Rcv_freq[] = "00000";

	for(int i = 0; i < num_decoded ; i++) {  //check to see if being called
	char little_gulp[20];
	int old_call;
	int old_call_address;

	if(strindex(new_decoded[i].field1, Station_Call)  >= 0 )	{
	old_call = 0;

	for (int j = 0; j<num_calls; j++) {
	if(strcmp(Answer_CQ[j].call,new_decoded[i].field2)  == 0 ) {
	old_call = 	Answer_CQ[j].number_times_called;
	old_call ++;
	Answer_CQ[j].number_times_called = old_call;
	old_call_address = j;
	}

	}

	if(old_call == 0) {

    sprintf(little_gulp," %s %s %s", new_decoded[i].field1, new_decoded[i].field2, new_decoded[i].field3);
    strcpy(current_Beacon_receive_message,little_gulp);
    update_Beacon_log_display(0);

	strcpy(Target_Call, new_decoded[i].field2);
	Target_RSL = new_decoded[i].snr;

	//set_reply(0, i);
	set_reply(0);

	Beacon_Reply_Status = 1;

	strcpy(Answer_CQ[num_calls].call, new_decoded[i].field2);
	strcpy(Answer_CQ[num_calls].locator, new_decoded[i].target);
	Answer_CQ[num_calls].RSL = Target_RSL;


	//itoa(new_decoded[i].freq_hz,Rcv_freq,10);
	//strcpy(Answer_CQ[num_calls].freq_hz, Rcv_freq);
	//Answer_CQ[num_calls].freq_hz = new_decoded[i].freq_hz;

	num_calls++;

	break;

	}


	if(old_call >= 1) {


		sprintf(little_gulp," %s %s %s", new_decoded[i].field1, new_decoded[i].field2, new_decoded[i].field3);
	    strcpy(current_Beacon_receive_message,little_gulp);
	    update_Beacon_log_display(0);


		if(Answer_CQ[old_call_address].RR73 == 0){

		strcpy(Target_Call, Answer_CQ[old_call_address].call);
		strcpy(Target_Locator, Answer_CQ[old_call_address].locator);

		Target_RSL = Answer_CQ[old_call_address].RSL;

		set_reply(1);

		Answer_CQ[old_call_address].RR73 = 1;

		Beacon_Reply_Status = 1;

		}

		//write_ADIF_Log(i);
	}



	//break;

	}   //check for station call

	} //check to see if being called


	return Beacon_Reply_Status;

}


void process_selected_Station(int stations_decoded, int TouchIndex){


	if(stations_decoded > 0 && TouchIndex <= stations_decoded ){
	strcpy(Target_Call, new_decoded[TouchIndex].field2);
	strcpy(Target_Locator, new_decoded[TouchIndex].target);
	Target_RSL = new_decoded[TouchIndex].snr;

	compose_messages();
	}

	FT8_Touch_Flag = 0;

}


void clear_CQ_List_box(void) {

	    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	    BSP_LCD_FillRect(240, 40, 240, 200);
	    num_CQ_calls = 0;
}



int Check_QSO_Calling_Stations(int num_decoded, int reply_state) {

	int QSO_Status = 0;

	for(int i = 0; i < num_decoded ; i++) {  //check to see if being called
		char little_gulp[20];
		//char blank[] = "                      ";

	if(strindex(new_decoded[i].field1, Station_Call)  >= 0 )	{

	sprintf(little_gulp," %s %s %s", new_decoded[i].field1, new_decoded[i].field2, new_decoded[i].field3);

    strcpy(current_QSO_receive_message, little_gulp);

    update_log_display(0);

    QSO_Status = 1; //we already have a reply!!

  //  write_ADIF_Log(i);

    break;
	} //check for station call

	else {

		QSO_Status = 0;

	} //check to see if being called

	}

	return QSO_Status;

}


int strindex(char s[],char t[])
{
    int i,j,k, result;

    result = -1;

    for(i=0;s[i]!='\0';i++)
    {
        for(j=i,k=0;t[k]!='\0' && s[j]==t[k];j++,k++)
            ;
        if(k>0 && t[k] == '\0')
            result = i;
    }
    return result;
}
