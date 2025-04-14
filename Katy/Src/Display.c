
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"
#include "Process_DSP.h"
#include "button.h"
#include "Display.h"
#include "gen_ft8.h"
#include "main.h"
#include "stdio.h"
#include "decode_ft8.h"

#include "WF_Table.h"

#define FFT_X  0
#define FFT_Y  1
#define FFT_W  2 * (ft8_buffer - ft8_min_bin )
#define FT8_X  48
#define FT8_Y  93
#define FT8_W  ft8_buffer

#define wf_offset 0

TS_StateTypeDef  TS_State = {0};

#define LEFT_MODE  3

extern TS_StateTypeDef  TS_State;
extern int RSL;
extern int Gadc;
extern int Gdac;

int		WF_Line0;
int		WF_Count = 0;
uint8_t	*pWFBfr;

uint8_t WF_Bfr[FFT_H  * (ft8_buffer - ft8_min_bin) *2 ];
uint32_t cursor_line[FFT_W];

int power_waterfall_top = 94;
uint16_t valx,valy;
uint8_t test;
int count;
double Touch_Frequency;

char current_QSO_receive_message[20];
char current_QSO_xmit_message[20];
int max_log_messages = 4;
display_message log_messages[4];

extern void set_RTC_to_GPS(void);


void update_log_display(int mode){

	for (int i = 0; i<max_log_messages -1; i++ ) {
		strcpy(log_messages[i].message , log_messages[i+1].message);
		log_messages[i].text_color = log_messages[i+1].text_color;
	}

	if (mode == 0) {
		strcpy(log_messages[max_log_messages -1].message,current_QSO_receive_message);
		log_messages[max_log_messages -1].text_color = 0;
	}

	if (mode == 1) {
		strcpy(log_messages[max_log_messages -1].message,current_QSO_xmit_message);
		log_messages[max_log_messages -1].text_color = 1;
	}

    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillRect(240, 40, 240, 80);
	BSP_LCD_SetFont (&Font16);
	//BSP_LCD_SetTextColor(LCD_COLOR_GREEN);

	for (int i = 0; i<max_log_messages; i++ ) {

		if(log_messages[i].text_color == 0 )  BSP_LCD_SetTextColor(LCD_COLOR_RED);
		if(log_messages[i].text_color == 1 )  BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);

		BSP_LCD_DisplayStringAt(240, 40 + i*20, log_messages[i].message, LEFT_MODE);
	}

}




char current_Beacon_receive_message[20];
char current_Beacon_xmit_message[20];
int max_Beacon_log_messages = 10;
display_message Beacon_log_messages[10];

void update_Beacon_log_display(int mode){

	for (int i = 0; i<max_Beacon_log_messages -1; i++ ) {
		strcpy(Beacon_log_messages[i].message , Beacon_log_messages[i+1].message);
		Beacon_log_messages[i].text_color = Beacon_log_messages[i+1].text_color;
	}


	if (mode == 0) {
		strcpy(Beacon_log_messages[max_Beacon_log_messages -1].message,current_Beacon_receive_message);
		Beacon_log_messages[max_Beacon_log_messages -1].text_color = 0;
	}

	if (mode == 1) {
		strcpy(Beacon_log_messages[max_Beacon_log_messages -1].message,current_Beacon_xmit_message);
		Beacon_log_messages[max_Beacon_log_messages -1].text_color = 1;
	}


    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillRect(240, 40, 240, 200);
	BSP_LCD_SetFont (&Font16);

	for (int i = 0; i<max_Beacon_log_messages; i++ ) {

		if(Beacon_log_messages[i].text_color == 0 )  BSP_LCD_SetTextColor(LCD_COLOR_RED);
		if(Beacon_log_messages[i].text_color == 1 )  BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);

		BSP_LCD_DisplayStringAt(240, 40 + i*20, Beacon_log_messages[i].message, LEFT_MODE);
	}

}

/*
void show_hz(uint16_t x, uint16_t y,uint32_t variable) {
	uint8_t string[10];   // print format stuff
    sprintf(string,"%8i",variable);
    BSP_LCD_SetFont (&Font16);
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_DisplayStringAt(x, y, string, LEFT_MODE);
}
*/

void show_wide(uint16_t x, uint16_t y,int variable) {
	uint8_t string[7];   // print format stuff
    sprintf(string,"%6i",variable);
    BSP_LCD_SetFont (&Font16);
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_DisplayStringAt(x, y, string, LEFT_MODE);
}


void show_variable(uint16_t x, uint16_t y,int variable) {
	uint8_t string[5];   // print format stuff
    sprintf(string,"%4i",variable);
    BSP_LCD_SetFont (&Font16);
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_DisplayStringAt(x, y, string, LEFT_MODE);
}

void show_short(uint16_t x, uint16_t y,uint8_t variable) {
	char string[4];   // print format stuff
    sprintf(string,"%2i",variable);
    BSP_LCD_SetFont (&Font16);
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_DisplayStringAt(x, y, string, LEFT_MODE);
}


void show_UTC_time(uint16_t x, uint16_t y,int utc_hours,int utc_minutes,int utc_seconds, int color) {
	sprintf((char *)rtc_time_string,"%2i:%2i:%2i",utc_hours,utc_minutes,utc_seconds);
	for (int i=0; i<9; i++) if (rtc_time_string[i] == 32) rtc_time_string[i] = 48;  //blank remover


    BSP_LCD_SetFont (&Font16);

    if(color == 0)BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    if(color == 1)BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);

    BSP_LCD_DisplayStringAt(x, y, rtc_time_string, LEFT_MODE);
}


void show_Real_Date(uint16_t x, uint16_t y,int date,int month,int year) {
	sprintf((char *)rtc_date_string,"%2i:%2i:%2i",date,month,year);
    BSP_LCD_SetFont (&Font16);
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    BSP_LCD_DisplayStringAt(x, y, rtc_date_string, LEFT_MODE);
}


void setup_display(void) {

    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillRect(0, 0, 480, 272);

    BSP_LCD_SetFont (&Font16);

    drawButton(0);
    drawButton(1);
    drawButton(2);
    drawButton(3);
    drawButton(4);
    drawButton(5);
    drawButton(6);
    drawButton(7);
   // Monitor_Only = 1;
    drawButton(8);
    drawButton(9);



    //BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
   // BSP_LCD_DisplayStringAt(320, 0, "Gain",0x03);

}




void Set_Cursor_Frequency(uint16_t cursor_pos){
	  NCO_Frequency = (double) ((float)cursor * FFT_Resolution + ft8_min_freq);
     }

void Process_Touch (void) {

	    if(!Tune_On && !xmit_flag && !Beacon_On) sButtonData[5].state = 0;
	    else
	    sButtonData[5].state = 1;

		test = BSP_TS_GetState(&TS_State);

		if(TS_State.touchDetected > 0) {

			valx = (uint16_t)TS_State.touchX[0];
			valy = (uint16_t)TS_State.touchY[0];

		    do
		    {
		      BSP_TS_GetState(&TS_State);
		    }while(TS_State.touchDetected > 0);

			if (FFT_Touch() == 1)    {
			cursor = ( valx - FFT_X);
			NCO_Frequency = (double) (cursor+ ft8_min_bin) * FFT_Resolution;
			show_variable(400, 25,(int)  NCO_Frequency );
			}
			else
			{
			  checkButton();

			}


			FT8_Touch_Flag = FT8_Touch();
			FT8_Message_Touch = Xmit_message_Touch();

		}

}


uint16_t FFT_Touch(void) {

 // if  ((valx > FFT_X  && valx < FFT_X + FFT_W/2 ) && (valy > FFT_Y && valy < FFT_Y + 2 * FFT_H))
	if  ((valx > FFT_X  && valx < FFT_X + FFT_W/2 ) && (valy > FFT_Y && valy < 30))
  return 1;
  else
  return 0;
}

int FT8_Touch(void) {

	  int y_test;
	  if  ((valx > 0  && valx < 240 ) && (valy > 40 && valy < 240)){
	  y_test = valy - 40;

	  FT_8_TouchIndex = y_test /20;
	  //show_variable(300,100,valx);
	 // show_variable(340,100,valy);
	 // show_variable(380,100,FT_8_TouchIndex);

	  return 1;
  }

	  else
	  return 0;
}

int Xmit_message_Touch(void) {

	  int y_test;
	  if  ((valx > 240  && valx < 480 ) && (valy > 160 && valy < 240)){
	  y_test = valy - 160;

	  FT_8_MessageIndex = y_test /20;
	  //show_variable(300,80,valx);
	  //show_variable(340,80,valy);
	  //show_variable(380,80,FT_8_MessageIndex);

	  return 1;
  }

	  else
	  return 0;
}


void Init_Waterfall (void)
{

	pWFBfr = &WF_Bfr[0];
	WF_Count = 0;
	WF_Line0 = FFT_H - 1;

}

int null_count, FFT_Line_Delay;

void Display_WF(void)	{

		if(ft8_marker ==1) {

		for (int x = 0; x < (FFT_W ); x++) *(pWFBfr + (FFT_W*WF_Line0) + x) = 63;
		ft8_marker = 0;

		}
		else {

			for (int x = 0; x < FFT_W; x++) {
				if(FFT_Buffer[x + 2*ft8_min_bin]>=0 && FFT_Buffer[x + 2*ft8_min_bin]<64)
				*(pWFBfr + (FFT_W*WF_Line0) + x) = (uint8_t)FFT_Buffer[x + 2*ft8_min_bin];
				else
				*(pWFBfr + (FFT_W*WF_Line0) + x) = 63;
			}
		}

		//shift data in memory by one time stepft8_buffer
		for (int y = 0; y < WF_Line0 ; y++){
			for (int x = 0; x <FFT_W ; x++) {

				*(pWFBfr + (FFT_W*y) + x) = *(pWFBfr + (FFT_W*(y+1)) + x);
				}
			}

		for ( int y = 0; y < FFT_H; y++){
			for (int x = 0; x < ft8_buffer -ft8_min_bin; x++){
			BSP_LCD_DrawPixel(x, y,WFPalette[ (*(pWFBfr + y*FFT_W + 2*x)) ] );
				}
			}


		if (Auto_Sync) {
		for (int x = 0; x < ft8_buffer -ft8_min_bin; x++){
		//	if ((*(pWFBfr + 37*FFT_W + 2*x))  > 0) null_count++;
		//	if ((*(pWFBfr + 38*FFT_W + 2*x))  > 0) null_count++;
			if ((*(pWFBfr + 39*FFT_W + 2*x))  > 0) null_count++;

		}
		//show_variable(0,220, null_count) ;

		if(null_count<3){

			FFT_Line_Delay ++;

			if (FFT_Line_Delay >= 2) {
		    FT8_Sync();
			//set_RTC_to_GPS();
			Auto_Sync = 0;
			FFT_Line_Delay = 0;
	        sButtonData[5].state = 0;
	        drawButton(5);
			}
		}



		null_count = 0;
		}


		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_DrawLine(FFT_X+ cursor,FFT_H,FFT_X+cursor,0);

		}














