/*
 * button.c
 *
 *  Created on: Feb 18, 2016
 *      Author: user
 */


#include <stdlib.h>
#include "display.h"
#include "button.h"
#include "stm32746g_discovery_lcd.h"
#include "SDR_Audio.h"
#include "Codec_Gains.h"
#include "decode_ft8.h"
#include "main.h"
#include "stm32fxxx_hal.h"
#include  "Process_DSP.h"
#include "log_file.h"
#include "gen_ft8.h"
#include "traffic_manager.h"
#include "DS3231.h"
#include "SiLabs.h"
#include "options.h"

extern uint16_t valx,valy;

#define FFT_Resolution 6.25  //8000/2/1280

int AGC_Gain = 20;
int ADC_DVC_Gain = 180;
int ADC_DVC_Off = 90;
int HP_Gain = 10;
int freq_scale = 10;

char display_frequency[] = "14.075";

extern uint16_t refClock;
extern void set_RTC_to_GPS(void);
extern RTCStruct s_RTC_Data[];

#define numBands 5

FreqStruct sBand_Data[] = {
		{//20,
		14074,
		"14.075"
		},

		{//17,
		18100,
		"18.101"
		},

		{//15,
		21074,
		"21.075"
		},

		{//12,
		24915,
		"24.916"

		},

		{//10,
		28074,
		"28.075"
		}
	};


#define numButtons 28

ButtonStruct sButtonData[] = {


	{	//button 0  inhibit xmit either as beacon or answer CQ
		/*text0*/ "Clr ",
		/*text1*/ "Clr ",
		/*blank*/ "    ",
		/*Active*/ 1,
		/*Displayed*/ 1,
		/*state*/ 0,
		/*x*/ 0,
		/*y*/ line2,
		/*w*/ button_width,
		/*h*/ 30
	},

	{	//button 1 control Beaconing / CQ chasing
		/*text0*/ "QSO ",
		/*text1*/ "Becn",
		/*blank*/ "    ",
		/*Active*/1,
        /*Displayed*/1,
        /*state*/ 0,
		/*x*/ 60,
		/*y*/ line2,
		/*w*/ button_width,
		/*h*/ 30
	},

	{	//button 2 control Tune
		/*text0*/ "Tune",
		/*text1*/ "Tune",
		/*blank*/ "    ",
		/*Active*/ 1,
        /*Displayed*/ 1,
        /*state*/ 0,
		/*x*/ 120,
		/*y*/ line2,
		/*w*/ button_width,
		/*h*/ 30
	},

	{	//button 3 display R/T status
		/*text0*/ "Rcv ",
		/*text1*/ "Xmit",
		/*blank*/ "    ",
		/*Active*/ 1,
        /*Displayed*/ 1,
        /*state*/ 0,
		/*x*/ 180,
		/*y*/ line2,
		/*w*/ 0,  //setting the width and height to 0 turns off touch response , display only
		/*h*/ 0
	},

	{	//button 4 turn on logging
		/*text0*/ "Log ",
		/*text1*/ "Log ",
		/*blank*/  "   ",
		/*Active*/ 1,
        /*Displayed*/ 1,
        /*state*/ 0,
		/*x*/ 240,
		/*y*/ line2,
		/*w*/ button_width,
		/*h*/ 30
	},

	{	//button 5 Sync FT8
		/*text0*/ "Sync",
		/*text1*/ "Sync",
		/*blank*/ "    ",
		/*Active*/ 1,
        /*Displayed*/ 1,
	    /*state*/ 0,
		/*x*/ 300,
		/*y*/ line2,
		/*w*/ button_width,
		/*h*/ 30

	},

	{	//button 6 Lower Gain
		/*text0*/ " G- ",
		/*text1*/ " G- ",
		/*blank*/ "    ",
		/*Active*/ 2,
        /*Displayed*/ 1,
	    /*state*/ 0,
		/*x*/ 360,
		/*y*/ line2,
		/*w*/ button_width,
		/*h*/ 30

	},

	{	//button 7 Raise Gain
		/*text0*/ " G+ ",
		/*text1*/ " G+ ",
		/*blank*/ "    ",
		/*Active*/ 2,
        /*Displayed*/ 1,
	    /*state*/ 0,
		/*x*/ 430,
		/*y*/ line2,
		/*w*/ button_width,
		/*h*/ 30

	},

	{	//button 8 Lower Cursor
		/*text0*/ "F- ",
		/*text1*/ "F- ",
		/*blank*/ "    ",
		/*Active*/ 2,
        /*Displayed*/ 1,
	    /*state*/ 0,
		/*x*/ 360,
		/*y*/ line0,
		/*w*/ button_width,
		/*h*/ 30

	},

	{	//button 9 Raise Cursor
		/*text0*/ "F+ ",
		/*text1*/ "F+ ",
		/*blank*/ "    ",
		/*Active*/ 2,
        /*Displayed*/ 1,
	    /*state*/ 0,
		/*x*/ 450,
		/*y*/ line0,
		/*w*/ button_width,
		/*h*/ 30

	},




	{	//button 10 Band Down
		/*text0*/ "Band-",
		/*text1*/ "Band-",
		/*blank*/ "    ",
		/*Active*/ 0,
        /*Displayed*/ 1,
	    /*state*/ 0,
		/*x*/ 270,
		/*y*/ 40,
		/*w*/ button_width,
		/*h*/ 30

	},

	{	//button 11 Band Up
		/*text0*/ "Band+",
		/*text1*/ "Band+",
		/*blank*/ "     ",
		/*Active*/ 0,
        /*Displayed*/ 1,
	    /*state*/ 0,
		/*x*/ 420,
		/*y*/ 40,
		/*w*/ button_width,
		/*h*/ 30

	},



	{	//button 12 Xmit for Calibration
		/*text0*/ "Xmit",
		/*text1*/ "Xmit",
		/*blank*/ "    ",
		/*Active*/ 0,
        /*Displayed*/ 1,
	    /*state*/ 0,
		/*x*/ 360,
		/*y*/ 140,
		/*w*/ button_width,
		/*h*/ 30

	},

	{	//button 13 Save Calibration Data
		/*text0*/ "Save",
		/*text1*/ "Save",
		/*blank*/ "    ",
		/*Active*/ 0,
        /*Displayed*/ 1,
	    /*state*/ 0,
		/*x*/ 360,
		/*y*/ 70,
		/*w*/ button_width,
		/*h*/ 30

	},

	{	//button 14 Save RTC Time
			/*text0*/ "Set ",
			/*text1*/ "Set ",
			/*blank*/ "    ",
			/*Active*/ 0,
	        /*Displayed*/ 1,
		    /*state*/ 0,
			/*x*/ RTC_Button,
			/*y*/ RTC_line2,
			/*w*/ button_width,
			/*h*/ 30

		},

		{	//button 15 Hours
			/*text0*/ "Hr- ",
			/*text1*/ "Hr- ",
			/*blank*/ "    ",
			/*Active*/ 0,
	        /*Displayed*/ 1,
		    /*state*/ 0,
			/*x*/ RTC_Sub,
			/*y*/ RTC_line0,
			/*w*/ button_width,
			/*h*/ 30

		},

		{	//button 16 Hours
			/*text0*/ "Hr+ ",
			/*text1*/ "Hr+ ",
			/*blank*/ "    ",
			/*Active*/ 0,
	        /*Displayed*/ 1,
		    /*state*/ 0,
			/*x*/ RTC_Add,
			/*y*/ RTC_line0,
			/*w*/ button_width,
			/*h*/ 30
		},


		{	//button 17 minutes
			/*text0*/ "Min-",
			/*text1*/ "Min-",
			/*blank*/ "    ",
			/*Active*/ 0,
	                /*Displayed*/ 1,
		        /*state*/ 0,
			/*x*/ RTC_Sub,
			/*y*/ RTC_line1,
			/*w*/ button_width,
			/*h*/ 30
		},

		{	//button 18 minutes
				/*text0*/ "Min+",
				/*text1*/ "Min+",
				/*blank*/ "    ",
				/*Active*/ 0,
		                /*Displayed*/ 1,
			        /*state*/ 0,
				/*x*/ RTC_Add,
				/*y*/ RTC_line1,
				/*w*/ button_width,
				/*h*/ 30
		},

		{	//button 19 Seconds
			/*text0*/ "Sec-",
			/*text1*/ "Sec-",
			/*blank*/ "    ",
			/*Active*/ 0,
	        /*Displayed*/ 1,
		    /*state*/ 0,
			/*x*/ RTC_Sub,
			/*y*/ RTC_line2,
			/*w*/ button_width,
			/*h*/ 30

		},

		{	//button 20 Seconds
			/*text0*/ "Sec+",
			/*text1*/ "Sec+",
			/*blank*/ "    ",
			/*Active*/ 0,
	        /*Displayed*/ 1,
		    /*state*/ 0,
			/*x*/ RTC_Add,
			/*y*/ RTC_line2,
			/*w*/ button_width,
			/*h*/ 30

		},


		{	//button 21 Day
			/*text0*/ "Day-",
			/*text1*/ "Day-",
			/*blank*/ "    ",
			/*Active*/ 0,
	        /*Displayed*/ 1,
		    /*state*/ 0,
			/*x*/ RTC_Sub,
			/*y*/ RTC_line3,
			/*w*/ button_width,
			/*h*/ 30
		},


		{	//button 22 Day
			/*text0*/ "Day+",
			/*text1*/ "Day+",
			/*blank*/ "    ",
			/*Active*/ 0,
	        /*Displayed*/ 1,
		    /*state*/ 0,
			/*x*/ RTC_Add,
			/*y*/ RTC_line3,
			/*w*/ button_width,
			/*h*/ 30
		},

		{	//button 23 Month
			/*text0*/ "Mon-",
			/*text1*/ "Mon-",
			/*blank*/ "    ",
			/*Active*/ 0,
	        /*Displayed*/ 1,
		    /*state*/ 0,
			/*x*/ RTC_Sub,
			/*y*/ RTC_line4,
			/*w*/ button_width,
			/*h*/ 30
		},


		{	//button 24 Month
			/*text0*/ "Mon+",
			/*text1*/ "Mon+",
			/*blank*/ "    ",
			/*Active*/ 0,
	        /*Displayed*/ 1,
		    /*state*/ 0,
			/*x*/ RTC_Add,
			/*y*/ RTC_line4,
			/*w*/ button_width,
			/*h*/ 30

		},

		{	//button 25 Year
			/*text0*/ "Yr- ",
			/*text1*/ "Yr- ",
			/*blank*/ "    ",
			/*Active*/ 0,
			/*Displayed*/ 1,
			/*state*/ 0,
			/*x*/ RTC_Sub,
			/*y*/ RTC_line5,
			/*w*/ button_width,
			/*h*/ 30
				},


		{	//button 26 Year
			/*text0*/ "Yr+ ",
			/*text1*/ "Yr+ ",
			/*blank*/ "    ",
			/*Active*/ 0,
			/*Displayed*/ 1,
			/*state*/ 0,
			/*x*/ RTC_Add,
			/*y*/ RTC_line5,
			/*w*/ button_width,
			/*h*/ 30

				},

		{	//button 27 Save  RTC Date
			/*text0*/ "Set ",
			/*text1*/ "Set ",
			/*blank*/ "    ",
			/*Active*/ 0,
			/*Displayed*/ 1,
			/*state*/ 0,
			/*x*/ RTC_Button,
			/*y*/ RTC_line5,
			/*w*/ button_width,
			/*h*/ 30
				}


};  // end of button definition



void drawButton(uint16_t i) {

		BSP_LCD_SetFont (&Font16);
	if (sButtonData[i].Active > 0){
        if (sButtonData[i].state == 1)
    	BSP_LCD_SetBackColor(LCD_COLOR_RED);
      else
    	BSP_LCD_SetBackColor(LCD_COLOR_BLUE);

    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

    if (sButtonData[i].state == 1)
    BSP_LCD_DisplayStringAt(sButtonData[i].x, sButtonData[i].y+15, sButtonData[i].text1, 0x03);
    else
    BSP_LCD_DisplayStringAt(sButtonData[i].x, sButtonData[i].y+15, sButtonData[i].text0, 0x03);

    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    }
}



void checkButton(void)  {
      uint16_t i;

    		  for (i=0;i<numButtons;i++){

    		  if (testButton( sButtonData[i].x,sButtonData[i].y,sButtonData[i].w,sButtonData[i].h) == 1)  {


    			  	switch (sButtonData[i].Active){

    				case 0:

    				break;

					case 1:

		    	    sButtonData[i].state =  !sButtonData[i].state;
		    	    drawButton(i);
		    	    executeButton(i);

					break;

					case 2:

		    	    executeButton(i);

					break;

					case 3:
					executeCalibrationButton (i);

					break;

    			  	}
    		     }
              }

      	  }










void executeButton (uint16_t index){

   switch (index) {

   case 0:

	   clear_xmit_messages();
	   terminate_QSO();
	   FT8_Message_Touch = 0;

       sButtonData[0].state = 1;
       drawButton(0);
       HAL_Delay(10);
       sButtonData[0].state = 0;
       drawButton(0);

	   break;

   case 1:

	   if (!sButtonData[1].state)
	  { Beacon_On = 0;
	   Beacon_State = 0;
	   clear_reply_message_box();
	  }
	   else
	  {
	   Beacon_On = 1;
	   clear_reply_message_box();
	   clear_log_stored_data();
	   Beacon_State = 1;
       }

       break;

   case 2:

	   if (!sButtonData[2].state)
	   {

	   tune_Off_sequence();
	   Tune_On = 0;
	   Arm_Tune = 0;
  	   xmit_flag = 0;
  	   receive_sequence();
  	   erase_Cal_Display();
	   }
  	   	else
  	   	{

		Tune_On = 1;  //Turns off display of FT8 traffic
		setup_Cal_Display();
		Arm_Tune = 0;
  	   	}

        break;

   case 3:

	   //no code required, all dependent stuff works off of button state
	   break;

   case 4:

   	   if ( sButtonData[4].state == 1 ){
   	   make_File_Name();
   	   Open_Log_File();
   	   }
   	   else
   	   Close_Log_File();

	   break;

   case 5:

	   if (!sButtonData[5].state)
	   {
		   Auto_Sync = 0;
	   }
  	   	else
  	   	{
  	   		Auto_Sync = 1;
  	   	}

	   	break;

   case 6:  //Lower Gain

	   if (AGC_Gain >= 3) AGC_Gain --;
	   show_short(405, 255, AGC_Gain );
	   Set_PGA_Gain(AGC_Gain);

	   	break;

   case 7:  //Raise Gain

	   if (AGC_Gain < 31) AGC_Gain ++;
	   show_short(405, 255, AGC_Gain );
	   Set_PGA_Gain(AGC_Gain);

	   	break;

   case 8:  //Lower Freq

	   if (cursor > 0) {
	    cursor --;
	    NCO_Frequency = (double) (cursor+ ft8_min_bin) * FFT_Resolution;
	    }
	    show_variable(400, 25,(int)  NCO_Frequency );

	   	break;

   case 9:  //Raise Freq

	    if (cursor <= (ft8_buffer - ft8_min_bin -2)) {  //limits highest NCO frequency to 3875 hz
	    cursor ++;
	    NCO_Frequency = (double) (cursor+ ft8_min_bin) * FFT_Resolution;
	    }
	    show_variable(400, 25,(int)  NCO_Frequency );

	   	break;


   case 12:  //Transmit for Calibration


	   if (!sButtonData[12].state)
	   {
	   tune_Off_sequence();
	   Arm_Tune = 0;
  	   xmit_flag = 0;
  	   receive_sequence();
	   }
  	   	else
  	   	{

  	   	xmit_sequence();
  	   	HAL_Delay(10);
		xmit_flag = 1;
		tune_On_sequence();
		Arm_Tune = 1;
  	   	}

	   break;


   case 13:  //Save Band Changes

	   Options_SetValue(0, BandIndex);

		Options_StoreValue(0);

		start_freq = sBand_Data[BandIndex].Frequency;
		show_wide(380, 0,(int) start_freq );

		set_Rcvr_Freq();
		HAL_Delay(10);

		sButtonData[13].state = 1;
		drawButton(13);
		HAL_Delay(10);
		sButtonData[13].state = 0;
		drawButton(13);

	   break;

	   case 14: //Set RTC to Edit

	   set_RTC_to_TimeEdit();

	   HAL_Delay(10);

	   		sButtonData[14].state = 1;
	   		drawButton(14);
	   		HAL_Delay(10);
	   		sButtonData[14].state = 0;
	   		drawButton(14);


	   break;

	   case 27: //Set RTC to Edit

	   set_RTC_to_DateEdit();

	   HAL_Delay(10);

	   		sButtonData[27].state = 1;
	   		drawButton(27);
	   		HAL_Delay(10);
	   		sButtonData[27].state = 0;
	   		drawButton(27);


	   break;

   }


}








   void executeCalibrationButton (uint16_t index){

      switch (index) {

      case 10:  //Lower Band

      if (BandIndex > 0) {
    	  BandIndex --;
    	  show_wide(340, 60, sBand_Data[BandIndex].Frequency );
    	  sprintf(display_frequency,"%s",sBand_Data[BandIndex].display);
      }

   	   break;

      case 11:  //Raise Band

	  if (BandIndex < numBands-1) {
		  BandIndex ++;
		  show_wide(340, 60, sBand_Data[BandIndex].Frequency );
		  sprintf(display_frequency,"%s",sBand_Data[BandIndex].display);
	  }

   	   break;

      case 15:  //Lower Hour

	  if (s_RTC_Data[3].data > s_RTC_Data[3].Minimum) {
		  s_RTC_Data[3].data --;
		  display_RTC_TimeEdit(RTC_Button-20,RTC_line0 + 15);
	  }

   	   break;

      case 16:  //Raise Hour

	  if (s_RTC_Data[3].data< s_RTC_Data[3].Maximum) {
		  s_RTC_Data[3].data ++;
		  display_RTC_TimeEdit(RTC_Button-20,RTC_line0 + 15);
	  }

   	   break;

      case 17:  //Lower Minute

	  if (s_RTC_Data[4].data > s_RTC_Data[4].Minimum) {
		  s_RTC_Data[4].data --;
		  display_RTC_TimeEdit(RTC_Button-20,RTC_line0 + 15);
	  }

   	   break;

      case 18:  //Raise Minute

	  if (s_RTC_Data[4].data< s_RTC_Data[4].Maximum) {
		  s_RTC_Data[4].data ++;
		  display_RTC_TimeEdit(RTC_Button-20,RTC_line0 + 15);
	  }

   	   break;

      case 19:  //Lower Second

     	  if (s_RTC_Data[5].data > s_RTC_Data[5].Minimum) {
     		  s_RTC_Data[5].data --;
     		  display_RTC_TimeEdit(RTC_Button-20,RTC_line0 + 15);
     	  }

        	   break;

      case 20:  //Raise Second

     	  if (s_RTC_Data[5].data< s_RTC_Data[5].Maximum) {
     		  s_RTC_Data[5].data ++;
     		  display_RTC_TimeEdit(RTC_Button-20,RTC_line0 + 15);
     	  }

        	   break;

      case 21:  //Lower Day

	  if (s_RTC_Data[0].data > s_RTC_Data[0].Minimum) {
		  s_RTC_Data[0].data --;
		  display_RTC_DateEdit(RTC_Button-20,RTC_line3 +15);
	  }

		   break;

      case 22:  //Raise Day

	  if (s_RTC_Data[0].data< s_RTC_Data[0].Maximum) {
		  s_RTC_Data[0].data ++;
		  display_RTC_DateEdit(RTC_Button-20,RTC_line3 +15);
	  }

		   break;

      case 23:  //Lower Month

	  if (s_RTC_Data[1].data > s_RTC_Data[1].Minimum) {
		  s_RTC_Data[1].data --;
		  display_RTC_DateEdit(RTC_Button-20,RTC_line3 +15);
	  }

		   break;

      case 24:  //Raise Month

	  if (s_RTC_Data[1].data< s_RTC_Data[1].Maximum) {
		  s_RTC_Data[1].data ++;
		  display_RTC_DateEdit(RTC_Button-20,RTC_line3 +15);
	  }

		   break;

      case 25:  //Lower Year

	  if (s_RTC_Data[2].data > s_RTC_Data[2].Minimum) {
		  s_RTC_Data[2].data --;
		  display_RTC_DateEdit(RTC_Button-20,RTC_line3 +15);
	  }

		   break;

      case 26:  //Raise Year

	  if (s_RTC_Data[2].data< s_RTC_Data[2].Maximum) {
		  s_RTC_Data[2].data ++;
		  display_RTC_DateEdit(RTC_Button-20,RTC_line3 +15);
	  }

		   break;

      }

   }



uint16_t testButton(uint16_t x,uint16_t y,uint16_t w,uint16_t h) {

	  y = y +15; // compensate for draw offset

	  if  ((valx < x+w && valx > x) && (valy > y && valy < y+h)){
	  return 1;
	  }else{
	  return 0;
		}
}




void setup_Cal_Display(void){

	//clear_messages();
	//clear_xmit_messages();

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(0, FFT_H, 480, 201);


	sButtonData[10].Active = 3;
	sButtonData[11].Active = 3;

	sButtonData[12].Active = 1;
	sButtonData[13].Active = 1;
	sButtonData[14].Active = 1;

	for(int i = 15; i < 27; i++) {
		sButtonData[i].Active = 3;
		drawButton(i);
	}

	sButtonData[27].Active = 1;

	drawButton(10);
	drawButton(11);
	drawButton(12);
	drawButton(13);
	drawButton(14);
	drawButton(27);

	show_wide(340, 60, (int) start_freq );

	load_RealTime();
	display_RTC_TimeEdit(RTC_Button-20,RTC_line0 + 15);

	load_RealDate();
	display_RTC_DateEdit(RTC_Button-20,RTC_line3 +15);



}

void erase_Cal_Display(void){
	//clear_messages();
	//clear_reply_message_box();

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(0, FFT_H, 480, 201);



	for(int i = 10; i < 28; i++) {
			sButtonData[i].Active = 0;
		}

	sButtonData[12].state = 0;
	sButtonData[13].state = 0;
	sButtonData[14].state = 0;
	sButtonData[27].state = 0;
}


void PTT_Out_Init(void)
{
    GPIO_InitTypeDef  gpio_init_structure;


	__HAL_RCC_GPIOI_CLK_ENABLE();

    gpio_init_structure.Pin = GPIO_PIN_2;
    gpio_init_structure.Mode = GPIO_MODE_OUTPUT_OD;
    gpio_init_structure.Pull = GPIO_PULLUP;
    gpio_init_structure.Speed = GPIO_SPEED_HIGH;

    HAL_GPIO_Init(GPIOI, &gpio_init_structure);

    HAL_GPIO_WritePin(GPIOI, GPIO_PIN_2, GPIO_PIN_SET);  //Set = Receive connect

    __HAL_RCC_GPIOA_CLK_ENABLE();

        gpio_init_structure.Pin = GPIO_PIN_15;
        gpio_init_structure.Mode = GPIO_MODE_OUTPUT_OD;
        gpio_init_structure.Pull = GPIO_PULLUP;
        gpio_init_structure.Speed = GPIO_SPEED_HIGH;

        HAL_GPIO_Init(GPIOA, &gpio_init_structure);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);  //Set = Receive short

}


void PTT_Out_Set(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_2, GPIO_PIN_SET);
}

void PTT_Out_RST_Clr(void)
	{
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
	}


void set_codec_input_gain(void){
	Set_PGA_Gain(AGC_Gain);
	HAL_Delay(10);
	Set_ADC_DVC(190);
}


void receive_sequence(void) {

	PTT_Out_Set(); // set output high to connect receiver to antenna
	HAL_Delay(10);

	sButtonData[3].state = 0;
	drawButton(3);
}


void xmit_sequence(void)  {

	PTT_Out_RST_Clr();  //set output low to disconnect receiver from antenna

	HAL_Delay(10);

	sButtonData[3].state = 1;
	drawButton(3);

}


uint64_t F_boot = 11229600000ULL;

void start_Si5351(void){

	  init(SI5351_CRYSTAL_LOAD_0PF, SI5351_XTAL_FREQ, 0);

	  drive_strength(SI5351_CLK0, SI5351_DRIVE_8MA);

	  drive_strength(SI5351_CLK1, SI5351_DRIVE_2MA);

	  drive_strength(SI5351_CLK2, SI5351_DRIVE_2MA);

      set_freq(F_boot, SI5351_CLK1);
      HAL_Delay(10);
      output_enable(SI5351_CLK1, 1);

      HAL_Delay(20);

	  set_Rcvr_Freq();

}



void FT8_Sync(void) {
	start_time = HAL_GetTick();
	ft8_flag = 1;
	FT_8_counter = 0;
	ft8_marker = 1;
	}
