/*
 * DS3231.c
 *
 *  Created on: Dec 25, 2019
 *      Author: user
 */

#include "DS3231.h"
#include "stm32746g_discovery.h"
#include "Display.h"
#include "main.h"
#include "options.h"

//char set_hour, set_minute, set_ampm, set_day, set_dow, set_event_desc[8], set_recipient_phone[16];

unsigned int temp_conv;
char txt_buffer[7];

char tmp, no_of_zeros;


RTCStruct s_RTC_Data[] = {
	{
		/*Name*/ "  Day ", //opt0
		/*Min */ 1,
		/*Max */ 31,
		/*Data*/ 0,
	},

	{
		/*Name*/ "Month", //opt1
		/*Min */ 1,
		/*Max */ 12,
		/*Data*/ 0,
	},

	{
		/*Name*/ "Year", //opt2
		/*Min */ 24,
		/*Max */ 99,
		/*Data*/ 0,
	},

	{
			/*Name*/ "Hour", //opt3
			/*Min */ 0,
			/*Max */ 23,
			/*Data*/ 0,
	},

	{
			/*Name*/ "Minute", //opt4

			/*Min */ 0,
			/*Max */ 59,
			/*Data*/ 0,
	},

	{
			/*Name*/ "Second", //opt5
			/*Min */ 0,
			/*Max */ 59,
			/*Data*/ 0,
		}

};

unsigned char bcd_to_decimal(unsigned char d)
{
         return ((d & 0x0F) + (((d & 0xF0) >> 4) * 10));
}


unsigned char decimal_to_bcd(unsigned char d)
{
         return (((d / 10) << 4) & 0xF0) | ((d % 10) & 0x0F);
}


unsigned char DS3231_Read(unsigned char address)
{
	return EXT_I2C_Read(DS3231_Read_addr, address);
}


void DS3231_Write(unsigned char address, unsigned char value)
{
	EXT_I2C_Write(DS3231_Write_addr, address, value);
}


void DS3231_init(void)
{

         DS3231_Write(controlREG, 0x00);
         DS3231_Write(statusREG, 0x08);

}


void getTime(unsigned char *p3, unsigned char *p2, unsigned char *p1, short *p0, short hour_format)
{
         unsigned char tmp = 0;

         *p1 = DS3231_Read(secondREG);
             *p1 = bcd_to_decimal(*p1);

        *p2 = DS3231_Read(minuteREG);
        *p2 =  bcd_to_decimal(*p2);

         switch(hour_format)
         {
                  case 1:
                  {
                           tmp = DS3231_Read(hourREG);
                           tmp &= 0x20;
                           *p0 = (short)(tmp >> 5);
                           *p3 = (0x1F & DS3231_Read(hourREG));
                           *p3 = bcd_to_decimal(*p3);
                           break;
                  }
                  default:
                  {
                           *p3 = (0x3F & DS3231_Read(hourREG));
                           *p3 = bcd_to_decimal(*p3);
                           break;
                  }
         }
}


void getDate(unsigned char *p4, unsigned char *p3, unsigned char *p2, unsigned char *p1)
{
         *p1 = DS3231_Read(yearREG);
         *p1 = bcd_to_decimal(*p1);
         *p2 = (0x1F & DS3231_Read(monthREG));
         *p2 = bcd_to_decimal(*p2);
         *p3 = (0x3F & DS3231_Read(dateREG));
         *p3 = bcd_to_decimal(*p3);
         *p4 = (0x07 & DS3231_Read(dayREG));
         *p4 = bcd_to_decimal(*p4);
}


void RTC_setTime(unsigned char hSet, unsigned char mSet, unsigned char sSet, short am_pm_state, short hour_format)
{
         unsigned char tmp = 0;
         DS3231_Write(secondREG, (decimal_to_bcd(sSet)));
         DS3231_Write(minuteREG, (decimal_to_bcd(mSet)));
         switch(hour_format)
         {
                  case 1:
                  {
                           switch(am_pm_state)
                           {
                                    case 1:
                                    {
                                             tmp = 0x60;
                                             break;
                                    }
                                    default:
                                    {
                                             tmp = 0x40;
                                             break;
                                    }
                           }
                           DS3231_Write(hourREG, ((tmp | (0x1F & (decimal_to_bcd(hSet))))));
                           break;
                  }

                  default:
                  {
                           DS3231_Write(hourREG, (0x3F & (decimal_to_bcd(hSet))));
                           break;
                  }
         }
}


void RTC_setDate(unsigned char daySet, unsigned char dateSet, unsigned char monthSet, unsigned char yearSet)
{
         DS3231_Write(dayREG, (decimal_to_bcd(daySet)));
         DS3231_Write(dateREG, (decimal_to_bcd(dateSet)));
         DS3231_Write(monthREG, (decimal_to_bcd(monthSet)));
         DS3231_Write(yearREG, (decimal_to_bcd(yearSet)));
}

/*
float getTemp(void)
{
         register float t = 0.0;
         unsigned char lowByte = 0;
         signed char highByte = 0;
         lowByte = DS3231_Read(tempLSBREG);
         highByte = DS3231_Read(tempMSBREG);
         lowByte >>= 6;
         lowByte &= 0x03;
         t = ((float)lowByte);


         t *= 0.25;
         t += highByte;
         return t;// return temp value

}

*/


void display_RealTime(int x, int y) {
	 //fetch time from RTC
	getTime(&rtc_hour, &rtc_minute, &rtc_second, &rtc_ampm,  _24_hour_format );
	show_UTC_time(x, y,rtc_hour,rtc_minute,rtc_second, 0);
}

void load_RealTime(void) {
	getTime(&rtc_hour, &rtc_minute, &rtc_second, &rtc_ampm,  _24_hour_format );
	s_RTC_Data[3].data = rtc_hour;
	s_RTC_Data[4].data = rtc_minute;
	s_RTC_Data[5].data = rtc_second;
}

void display_RTC_TimeEdit(int x, int y){
	show_UTC_time(x, y,s_RTC_Data[3].data,s_RTC_Data[4].data,s_RTC_Data[5].data, 0);
}

void set_RTC_to_TimeEdit(void) {
	RTC_setTime(s_RTC_Data[3].data,s_RTC_Data[4].data,s_RTC_Data[5].data ,0, 0);
}

void load_RealDate(void) {
	getDate(&rtc_dow,&rtc_date , &rtc_month, &rtc_year);
	if(rtc_date > 0) s_RTC_Data[0].data = rtc_date;
	else s_RTC_Data[0].data = rtc_date = 1;

	if(rtc_month > 0) s_RTC_Data[1].data = rtc_month;
	else s_RTC_Data[1].data = 1;

	if (rtc_year >= 24) s_RTC_Data[2].data = rtc_year;
	else
	s_RTC_Data[2].data = 1;
}

void display_RTC_DateEdit(int x, int y){
    show_Real_Date(x,  y,s_RTC_Data[0].data,s_RTC_Data[1].data,s_RTC_Data[2].data);
}

void set_RTC_to_DateEdit(void) {
	RTC_setDate(0,s_RTC_Data[0].data,s_RTC_Data[1].data,s_RTC_Data[2].data);
}


void display_Real_Date(int x, int y) {
	getDate(&rtc_dow,&rtc_date , &rtc_month, &rtc_year);
    show_Real_Date(x, y,rtc_date,rtc_month,rtc_year);
}


void make_Real_Time(void) {

	getTime(&rtc_hour, &rtc_minute, &rtc_second, &rtc_ampm,  _24_hour_format );

	sprintf((char *)log_rtc_time_string,"%2i%2i%2i",rtc_hour,rtc_minute,rtc_second);

	for (int i=0; i<9; i++) if (log_rtc_time_string[i] == 32) log_rtc_time_string[i] = 48;  //blank remover

	/*
    BSP_LCD_SetFont (&Font16);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(240, 160, log_rtc_time_string, LEFT_MODE);
    */
}

void make_Real_Date(void){

	getDate(&rtc_dow,&rtc_date , &rtc_month, &rtc_year);
	sprintf((char *)log_rtc_date_string,"%2s%2i%2i%2i","20",rtc_year, rtc_month,rtc_date);

	for (int i=0; i<9; i++) if (log_rtc_date_string[i] == 32) log_rtc_date_string[i] = 48;  //blank remover

	/*
    BSP_LCD_SetFont (&Font16);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

    //show_short(240, 120, rtc_date);
    //show_short(300, 120, rtc_month);
    //show_short(360, 120, rtc_year);
    BSP_LCD_DisplayStringAt(240, 140, log_rtc_date_string, LEFT_MODE);
	*/

}

void make_File_Name(void){

	//make_Real_Time();
	make_Real_Date();

	//getDate(&rtc_dow,&rtc_date , &rtc_month, &rtc_year);
	//sprintf((char *)file_name_string,"%s_%s.adi",log_rtc_date_string,log_rtc_time_string);
	//for (int i=0; i<9; i++) if (log_rtc_date_string[i] == 32) log_rtc_date_string[i] = 48;  //blank remover

	sprintf((char *)file_name_string,"%s.adi",log_rtc_date_string);
	for (int i=0; i<24; i++) if (file_name_string[i] == 32) file_name_string[i] = 48;

	//BSP_LCD_SetFont (&Font16);
    //BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

    //show_short(240, 120, rtc_date);
    //show_short(300, 120, rtc_month);
    //show_short(360, 120, rtc_year);
    //BSP_LCD_DisplayStringAt(240, 180, file_name_string, LEFT_MODE);


}


/*
void sync_RTC(void) {
	DS3231_Write(secondREG, 0);

}

void sync_FT8_Time(void) {


		int sync_Flag;
		while (!sync_Flag){
		getTime(&rtc_hour, &rtc_minute, &rtc_second, &rtc_ampm,  _24_hour_format );
		if (rtc_second  % 15 == 0) sync_Flag = 1;
		}



}



void set_RTC_Item(int item, int16_t value){

	    unsigned char bcd_value;


		switch (item) {

		case RTC_Date:
			 bcd_value = decimal_to_bcd( (unsigned char) value);
			 DS3231_Write(dateREG, bcd_value);
		break;

		case RTC_Month:
			 bcd_value = decimal_to_bcd( (unsigned char) value);
			 DS3231_Write(monthREG, bcd_value);
		break;

		case RTC_Year:
			 bcd_value = decimal_to_bcd( (unsigned char) value);
			 DS3231_Write(yearREG, bcd_value);
		break;

		case RTC_Hour:
			bcd_value = decimal_to_bcd( (unsigned char) value);
			DS3231_Write(hourREG, bcd_value);
		break;

		case RTC_Minute:
			bcd_value = decimal_to_bcd( (unsigned char) value);
			   DS3231_Write(minuteREG, bcd_value);
		break;

		}

}

*/


void RTC_SetValue(int Idx, char newValue)
{
	s_RTC_Data[Idx].data = newValue;

    }
