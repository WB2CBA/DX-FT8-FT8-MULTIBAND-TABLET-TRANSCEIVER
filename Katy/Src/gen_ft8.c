/*
 * gen_ft8.c
 *
 *  Created on: Oct 24, 2019
 *      Author: user
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


#include "pack.h"
#include "encode.h"
#include "constants.h"

#include "gen_ft8.h"

#include <stdio.h>

#include "ff.h"			/* Declarations of FatFs API */
#include "diskio.h"		/* Declarations of device I/O functions */
#include "stdio.h"
#include "stm32746g_discovery_sd.h"
#include "stm32746g_discovery.h"

#include "stm32746g_discovery_lcd.h"

#include "ff_gen_drv.h"
#include "sd_diskio.h"

#include "arm_math.h"
#include <string.h>
#include "decode_ft8.h"
#include "Display.h"
#include "log_file.h"
#include "traffic_manager.h"
#include "ADIF.h"

#include "button.h"

extern char current_Beacon_xmit_message[];
//extern uint16_t start_freq;

char Your_Call[] = "W5XXX";
char Your_Locator[] = "AA00";

char test_station[] = "W5BAA";
char test_target[] = "W5ITU";
char test_RSL[] = "R-15";

static uint8_t isInitialized = 0;

int max_displayed_messages = 8;

/* Fatfs structure */
FATFS FS;
FIL fil;

void  set_cq(void) {
	char CQ[] = "CQ";
    char message[18];
    uint8_t packed[K_BYTES];
    char blank[] = "                      ";

    sprintf(message,"%s %s %s",CQ,Station_Call,Locator);

    pack77(message, packed);
    genft8(packed, tones);

    BSP_LCD_SetFont (&Font16);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(240, 240, blank,0x03);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(240, 240, message,0x03);

}

extern char current_Beacon_xmit_message[20];

//void  set_reply(uint16_t index, uint16_t vector ) {

void  set_reply(uint16_t index ) {

	//char big_gulp[60];
    char seventy_three[] = "RR73";
    uint8_t packed[K_BYTES];
    char blank[] = "                      ";
    char RSL[] = "     ";

    itoa(Target_RSL, RSL, 10 );

    if (index == 0) sprintf(reply_message,"%s %s %R%s",Target_Call,Station_Call,RSL);


    if (index == 1) {
    sprintf(reply_message,"%s %s %s",Target_Call,Station_Call,seventy_three);
    write_ADIF_Log();
    }

	strcpy(current_Beacon_xmit_message,reply_message);
	update_Beacon_log_display(1);

    pack77(reply_message, packed);
    genft8(packed, tones);

     BSP_LCD_SetFont (&Font16);
     BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
     BSP_LCD_DisplayStringAt(240, 240, blank,0x03);
     BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
     BSP_LCD_DisplayStringAt(240, 240, reply_message,0x03);

}


char    xmit_messages[4][19];

void compose_messages(void) {
	char seventy_three[] = "RR73";
	char CQ[] = "CQ";
    char RSL[] = "     ";

    itoa(Target_RSL, RSL, 10 );


	sprintf(xmit_messages[0],"%s %s %s", Target_Call,Station_Call,Locator);
	sprintf(xmit_messages[1],"%s %s %R%s", Target_Call,Station_Call,RSL);
	sprintf(xmit_messages[2],"%s %s %3s", Target_Call,Station_Call,seventy_three);
	sprintf(xmit_messages[3],"%s %s %s", CQ,Station_Call,Locator);

    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillRect(240, 130, 240, 123);
	BSP_LCD_SetFont (&Font16);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

    BSP_LCD_DisplayStringAt(240, 160, xmit_messages[0],0x03);
    BSP_LCD_DisplayStringAt(240, 180, xmit_messages[1],0x03);
    BSP_LCD_DisplayStringAt(240, 200, xmit_messages[2],0x03);
    BSP_LCD_DisplayStringAt(240, 220, xmit_messages[3],0x03);

    }

extern char current_QSO_xmit_message[];

void que_message(int index ) {

	uint8_t packed[K_BYTES];

	char blank[] = "                      ";

    pack77(xmit_messages[index], packed);
    genft8(packed, tones);

    BSP_LCD_SetFont (&Font16);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(240, 140, blank,0x03);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_DisplayStringAt(240, 140, xmit_messages[index],0x03);

	strcpy(current_QSO_xmit_message, xmit_messages[index]);

	if(index == 2)write_ADIF_Log();

   }


void clear_qued_message(void) {

	char blank[] = "                      ";

    BSP_LCD_SetFont (&Font16);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(240, 140, blank,0x03);
}


void clear_xmit_messages(void){
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillRect(240, 130, 240, 120);
    }

char *CurrentStationName;
char StationFileName[32];

void Read_Station_File( void ){

	uint8_t i,j;
	char read_buffer[132];
	char* Station_Data;
   	strcpy(CurrentStationName,"StationData");
	sprintf(StationFileName,"%s.txt",CurrentStationName);

	f_mount(&FS, SDPath, 1);
	   	if ( f_open(&fil, StationFileName, FA_OPEN_ALWAYS | FA_READ) == FR_OK){

			for(j=0;j<64;j++)read_buffer[j]=0;
			f_lseek(&fil,0);
			f_gets(read_buffer,64,&fil);
	   		i = strlen(read_buffer);
	   		read_buffer[i] = 0;

	   		Station_Data = strtok(read_buffer,":");
	   		strcpy(Station_Call, Station_Data);
	   		Station_Data = strtok(NULL,":");
		   	strcpy(Locator, Station_Data);

   		f_close(&fil);
	   	}



}


void clear_reply_message_box(void) {

	    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	    BSP_LCD_FillRect(240, 40, 240, 201);
 }


void SD_Initialize(void)
	  {

    BSP_LCD_SetFont (&Font16);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);

	    if (isInitialized == 0)
	    {
	      if (BSP_SD_Init() == MSD_OK)
	      {
	        BSP_SD_ITConfig();
	        isInitialized = 1;
	        FATFS_LinkDriver(&SD_Driver, SDPath);
	      }
	      else
	      {
	    	 BSP_LCD_DisplayStringAt(0, 100, "Insert SD.",0x03);
	        while (BSP_SD_IsDetected() != SD_PRESENT)
	        {}
	        BSP_LCD_DisplayStringAt(0, 100, "Reboot Now.",0x03);

	      }
	    }
	  }

