/*
 * Process_DSP.c
 *
 *  Created on: Feb 6, 2016
 *      Author: user
 */

#include "SDR_Audio.h"
#include "arm_math.h"
#include "Process_DSP.h"
#include "arm_common_tables.h"
#include "main.h"
#include "Display.h"
#include <math.h>
#include <errno.h>
#include "decode.h"
#include "FIR_Coefficients.h"

float ft_blackman_i(int i, int N);

int plain_text[174];
int iterations = 40;
int test_results;
double RSL_Mag;
int    RSL;

q15_t FIR_State_I[NUM_FIR_COEF + (BUFFERSIZE / 4) - 1];
q15_t FIR_State_Q[NUM_FIR_COEF + (BUFFERSIZE / 4) - 1];


arm_fir_instance_q15 S_FIR_I_32K = { NUM_FIR_COEF,&FIR_State_I[0], &coeff_fir_I_32K[0] };
//arm_fir_instance_q15 S_FIR_Q_32K = { NUM_FIR_COEF,&FIR_State_Q[0], &coeff_fir_Q_32K[0] };
arm_fir_instance_q15 S_FIR_Q_32K = { NUM_FIR_COEF,&FIR_State_Q[0], &coeff_fir_I_32K[0] };



void Process_FIR_I_32K(void){
	arm_fir_q15(&S_FIR_I_32K, &FIR_I_In[0], &FIR_I_Out[0], BUFFERSIZE / 4);
	}

void Process_FIR_Q_32K(void){
	arm_fir_q15(&S_FIR_Q_32K, &FIR_Q_In[0], &FIR_Q_Out[0], BUFFERSIZE / 4);
	}




arm_rfft_instance_q15 fft_inst;


void init_DSP(void) {
   arm_rfft_init_q15(&fft_inst, FFT_SIZE, 0, 1);
   for (int i = 0; i < FFT_SIZE; ++i) window[i] = ft_blackman_i(i, FFT_SIZE);
   offset_step = (int) ft8_buffer*4;
}


float ft_blackman_i(int i, int N);

float ft_blackman_i(int i, int N) {
    const float alpha = 0.16f; // or 2860/18608
    const float a0 = (1 - alpha) / 2;
    const float a1 = 1.0f / 2;
    const float a2 = alpha / 2;

    float x1 = cosf(2 * (float)M_PI * i / (N - 1));
    float x2 = 2*x1*x1 - 1; // Use double angle formula

    return a0 - a1*x1 + a2*x2;
}


int master_offset;


void process_FT8_FFT(void) {



		 for(int i = 0; i< input_gulp_size; i++) {
			 extract_signal[i] = extract_signal[i + input_gulp_size];
			 extract_signal[i+ input_gulp_size] = extract_signal[i + 2*input_gulp_size];
			 extract_signal[i+ 2* input_gulp_size] =  FT8_Data[i];

		 }

		 if(ft8_flag == 1) {

		 master_offset =  offset_step *  FT_8_counter;
		 extract_power(master_offset);

		 for(int k = 0; k<ft8_buffer; k++){

			//	if(export_fft_power[k + master_offset ] <64 && export_fft_power[k + master_offset ] >= 0)
				if(export_fft_power[k + master_offset ] <64 )
				{
				FFT_Buffer[2*k] = (uint16_t )export_fft_power[k + master_offset ] ;
				FFT_Buffer[2*k+1] = (uint16_t )export_fft_power[k + master_offset + ft8_buffer] ;
				}
				else {
				//FFT_Buffer[2*k] = 0;
				//FFT_Buffer[2*k+1] = 0;

				FFT_Buffer[2*k] = 63;
				FFT_Buffer[2*k+1] = 63;
		 	 	 }
		 }

		Display_WF();

		 FT_8_counter++;
		 if (FT_8_counter == ft8_msg_samples)
		 {ft8_flag = 0;
		 decode_flag = 1;
		 }

		 }
  }



// Compute FFT magnitudes (log power) for each timeslot in the signal
void extract_power( int offset) {


        // Loop over two possible time offsets (0 and block_size/2)
        for (int time_sub = 0; time_sub <= input_gulp_size/2; time_sub += input_gulp_size/2) {

        for (int i = 0; i <  FFT_SIZE ; i++) window_dsp_buffer[i] = (q15_t) ( (float) extract_signal[i + time_sub] * window[i] );
        arm_rfft_q15(&fft_inst, window_dsp_buffer,dsp_output );
        arm_shift_q15(&dsp_output[0], 5, &FFT_Scale[0], FFT_SIZE * 2 );
        arm_cmplx_mag_squared_q15(&FFT_Scale[0], &FFT_Magnitude[0], FFT_SIZE);

       for (int j = 0; j< FFT_SIZE/2; j++) {
        FFT_Mag_10[j] = 10 * (int32_t)FFT_Magnitude[j];
        mag_db[j] =  5.0 * log((float)FFT_Mag_10[j] + 0.1);

       }

            // Loop over two possible frequency bin offsets (for averaging)
            for (int freq_sub = 0; freq_sub < 2; ++freq_sub) {
                for (int j = 0; j < ft8_buffer; ++j) {
                    float db1 = mag_db[j * 2 + freq_sub];
                    float db2 = mag_db[j * 2 + freq_sub + 1];
                    float db = (db1 + db2) / 2;

                    int scaled = (int) (db);
                  // export_fft_power[offset] = (scaled < 0) ? 0 : ((scaled > 255) ? 255 : scaled);
                    export_fft_power[offset] =  (uint8_t)  (scaled < 0) ? 0 : ((scaled > 255) ? 255 : scaled);
                    ++offset;
                }
            }
        }

}



