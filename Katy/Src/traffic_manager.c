/*
 * traffic_manager.c
 *
 *  Created on: Feb 29, 2020
 *      Author: user
 */

#include "button.h"
#include "gen_ft8.h"
#include "decode_ft8.h"
#include "stm32746g_discovery_lcd.h"
#include "SDR_Audio.h"
#include "traffic_manager.h"
#include "display.h"
#include "SiLabs.h"
#include "Process_DSP.h"
#include "Codec_Gains.h"

#define FT8_TONE_SPACING        625

//char blank1[] = "                  ";
//char blank2[] = "                           ";

extern int QSO_xmit;
extern int Xmit_DSP_counter;

extern uint16_t start_freq;
extern int AGC_Gain;
extern int ADC_DVC_Gain;
extern int ADC_DVC_Off;


void service_QSO_mode(int decoded_signals, int message_touch){

	//int receive_status;

	//receive_status = Check_QSO_Calling_Stations(decoded_signals, 0);
	Check_QSO_Calling_Stations(decoded_signals, 0);

	if(QSO_xmit == 1 ) {
		setup_to_transmit_on_next_DSP_Flag();
		update_log_display(1);
		QSO_xmit = 0;
	}


	}

void service_Beacon_mode(int decoded_signals){
	int receive_status;

	switch (Beacon_State){

	case 0:   //receive_status = Check_Calling_Stations(decoded_signals, 0);
	break;

	case 1:    receive_status = Check_Calling_Stations(decoded_signals, 0);
			   if(receive_status == 1) {
			    setup_to_transmit_on_next_DSP_Flag();
				}
			   else {
				set_cq();
			    setup_to_transmit_on_next_DSP_Flag();
			    }

			    Beacon_State = 2;
	break;

	case 2:   receive_status = Check_Calling_Stations(decoded_signals, 0);
			  if(receive_status == 1) {
			  setup_to_transmit_on_next_DSP_Flag();
			  }
			  Beacon_State = 1;
	break;

	}

}  //end of service_Beacon_mode

void setup_to_transmit_on_next_DSP_Flag(void){
		ft8_xmit_counter = 0;
		xmit_sequence();
		ft8_transmit_sequence();
		xmit_flag = 1;
		Xmit_DSP_counter = 0;
}

void terminate_QSO(void) {
	ft8_receive_sequence();
	receive_sequence();
	xmit_flag = 0;
}




uint64_t F_Long, F_FT8, F_Receive;

   void ft8_transmit_sequence(void){
	      Set_ADC_DVC(ADC_DVC_Off);
	      HAL_Delay(10);
	      set_Xmit_Freq();
	      HAL_Delay(10);
	     // output_enable(SI5351_CLK0, 1);
   }

      void ft8_receive_sequence(void){
           output_enable(SI5351_CLK0, 0);
           HAL_Delay(10);
           Set_ADC_DVC(ADC_DVC_Gain);
   }


   void tune_On_sequence(void){
	      Set_ADC_DVC(ADC_DVC_Off);
	      HAL_Delay(10);
	      set_Xmit_Freq();
	      HAL_Delay(10);
	      output_enable(SI5351_CLK0, 1);
   }

      void tune_Off_sequence(void){
          output_enable(SI5351_CLK0, 0);
          HAL_Delay(10);
          Set_ADC_DVC(ADC_DVC_Gain);
   }


   void  set_Xmit_Freq(void){
      F_Long = ((start_freq * 1000ULL + (uint16_t) NCO_Frequency) * 100ULL  );
      set_freq(F_Long, SI5351_CLK0);
}



    void set_FT8_Tone( uint8_t ft8_tone) {
          F_FT8 =  F_Long + (uint64_t)ft8_tone * FT8_TONE_SPACING;
          set_freq(F_FT8, SI5351_CLK0);
    }


  void set_Rcvr_Freq(void) {
	  F_Receive =  (  (  start_freq * 1000ULL - 10000ULL )   * 100ULL * 4ULL );
      set_freq(F_Receive, SI5351_CLK1);

  }

