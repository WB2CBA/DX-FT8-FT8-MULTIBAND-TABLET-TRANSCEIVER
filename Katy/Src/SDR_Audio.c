/*
 * SDR_Audio.c
 *
 *  Created on: May 10, 2016
 *      Author: user
 */

#include "SDR_Audio.h"
#include "stm32746g_discovery_audio.h"
#include "wm8994.h"
#include "stm32746g_discovery_lcd.h"
#include "arm_math.h"
#include "Process_DSP.h"
#include <stdlib.h>

#include "button.h"

extern const int Sine_table[];
#define PI2 6.2831853071795864765
#define KCONV 10430.37835              // 		4096*16/PI2
double LO_Freq = 10000;
float Sample_Frequency = 32000.0;


//uint32_t uwVolume = 80;
//float rgain = 0.5;


void start_audio_I2C (void){
	AUDIO_IO_Init();
}

void clear_Output_Buffers(void);

void clear_Output_Buffers(void) {
	int i;
	for(i=0; i<BUFFERSIZE;i++) 	out_buff[i] = 0;
	}

uint32_t hope;

void start_codec(void) {
	hope = wm8994_Reset(AUDIO_I2C_ADDRESS);
	HAL_Delay(100);
	hope = wm8994_Init(AUDIO_I2C_ADDRESS, INPUT_DEVICE_INPUT_LINE_1 | OUTPUT_DEVICE_BOTH, 70, (uint32_t)16000);
	HAL_Delay(100);
}

void start_duplex(int mode) {
  //note, somehow there is a sneak path for setting the codec frequency see wmcodec for reference

  HAL_Delay(10);
  clear_Output_Buffers();
  if(mode == 0)
  BSP_AUDIO_IN_OUT_Init(INPUT_DEVICE_INPUT_LINE_1, OUTPUT_DEVICE_BOTH, 70, 32000);
  else
  BSP_AUDIO_IN_OUT_Init(INPUT_DEVICE_INPUT_LINE_1, OUTPUT_DEVICE_BOTH, 70, 8000) ;


  BSP_AUDIO_IN_Record((uint16_t*)&in_buff,BUFFERSIZE);

  BSP_AUDIO_OUT_Play((uint16_t*)&out_buff, 2*BUFFERSIZE);

  R_lgain = 0.5;

  NoOp;

}

void transfer_buffers(void)  {
	int j;
    for (j = 0; j < BUFFERSIZE/4; j++)
    {
		out_buff[buff_offset + j*2] = in_buff[buff_offset + j*2];

		out_buff[buff_offset + j*2 + 1] = in_buff[buff_offset + j*2+1];

    }
}

void clear_buffers(void)  {
	int j;
    for (j = 0; j < BUFFERSIZE/4; j++)
    {
		out_buff[buff_offset + j*2] = 0;
		out_buff[buff_offset + j*2 + 1] = 0;
    }
}


void BSP_AUDIO_IN_TransferComplete_CallBack(void)
{
	buff_offset = BUFFERSIZE/2;
	DSP_Flag = 1;
	//I2S2_RX_ProcessBuffer(buff_offset );
	//transfer_buffers();


}

void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{
	buff_offset = 0;
	DSP_Flag = 1;
	//I2S2_RX_ProcessBuffer(buff_offset );
	//transfer_buffers();
}


void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
	//buff_offset = BUFFERSIZE/2;
	//DSP_Flag = 1;
	//transfer_buffers();
	//I2S2_RX_ProcessBuffer(buff_offset );
	//DSP_Process_Switch(buff_offset);
}


void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{
	//buff_offset = 0;
	//DSP_Flag = 1;
	//transfer_buffers();
	//I2S2_RX_ProcessBuffer(buff_offset );
	//DSP_Process_Switch(buff_offset);

}

int frame_counter;


void I2S2_RX_ProcessBuffer(uint16_t offset){

	static q15_t TX_I,TX_Q ;
	static long NCO_phz;
	float m_RMSConstant = 0.00001;


	x_NCOphzinc = (PI2 * LO_Freq / (double) Sample_Frequency);

	for (int i = 0; i < BUFFERSIZE / 4; i++) {
			NCO_phz += (long) (KCONV * (x_NCOphzinc));
			TX_I = (Sine_table[(NCO_phz >> 4) & 0xFFF]);
			TX_Q = (Sine_table[((NCO_phz >> 4) + 0x400) & 0xFFF]);

			FIR_I_In[i] = (q15_t) ((float) TX_I * (float)in_buff[i*2+offset] * m_RMSConstant);
			FIR_Q_In[i] = (q15_t) ((float) TX_Q   * (float)in_buff[i*2+1+offset] * m_RMSConstant);

		}

		 Process_FIR_I_32K();
		 Process_FIR_Q_32K();

		 for(int i=0;i<BUFFERSIZE/4;i++){

		 USB_Out[i] = FIR_I_Out[i] - FIR_Q_Out[i];
		 LSB_Out[i] = FIR_I_Out[i] + FIR_Q_Out[i];



			 if(frame_counter <4) {

				if(i%5 == 0) FT8_Data[i/5 + frame_counter * 256] = USB_Out[i] ;
				 }


		out_buff[i*2+offset]= (int16_t)USB_Out[i];
		out_buff[i*2+1+offset]= (int16_t)LSB_Out[i];

		 }

		 frame_counter++;

		 if(frame_counter == 4)
		 {
			  process_FT8_FFT();
			  frame_counter = 0;
		 }

    }
















