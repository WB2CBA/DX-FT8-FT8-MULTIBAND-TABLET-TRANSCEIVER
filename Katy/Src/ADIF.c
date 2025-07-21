/*
 * ADIF.c
 *
 *  Created on: Jun 18, 2023
 *      Author: Charley
 */
#include "ADIF.h"
#include "gen_ft8.h"
#include "DS3231.h"
#include "decode_ft8.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "log_file.h"
#include "button.h"


extern char display_frequency[];


char log_line[180];


		void write_ADIF_Log(void) {




			make_Real_Time();
			make_Real_Date();


			// sprintf(log_line,"<call:7>%7s<gridsquare:4>%4s<mode:3>FT8<qso_date:8>%8s <time_on:6>%6s<band:3>%3s <freq:9>%9s<station_callsign:7>%7s<my_gridsquare:4>%4s <eor>",
					// Answer_CQ[index].call, Answer_CQ[index].locator,  log_rtc_date_string, log_rtc_time_string, band,display_frequency, Station_Call, Locator);
			// Target_Call, Target_Locator,  log_rtc_date_string, log_rtc_time_string, band,display_frequency, Station_Call, Locator);

			 sprintf(log_line,"<call:7>%7s<gridsquare:4>%4s<mode:3>FT8<qso_date:8>%8s <time_on:6>%6s<freq:9>%9s<station_callsign:7>%7s<my_gridsquare:4>%4s <eor>",
			 Target_Call, Target_Locator,  log_rtc_date_string, log_rtc_time_string, display_frequency, Station_Call, Locator);


			  Write_Log_Data(log_line);
	}







