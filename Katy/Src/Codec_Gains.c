/*
 * Code that connects various audio source to CODEC and adjusts gains
 *
 * STM32-SDR: A software defined HAM radio embedded system.
 * Copyright (C) 2013, STM32-SDR Group
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#include "stm32746g_discovery.h"
#include "Codec_Gains.h"
#include "wm8994.h"
#include "stm32746g_discovery_audio.h"

#define Codec_Pause 1


void Set_HP_Gain(int HP_gain)
{

	if (HP_gain > HP_GAIN_MAX) 		HP_gain = HP_GAIN_MAX;
		if (HP_gain < HP_GAIN_MIN)			HP_gain = HP_GAIN_MIN;

	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x001C, HP_gain+64);  //headphone volume
	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x001D, HP_gain+320);  //headphone volume
   }   // End of Set_HP_Gain

/*
void Set_Mic_PGA_Gain(int PGA_gain)
{

	if (PGA_gain < PGA_GAIN_MIN)
		PGA_gain = PGA_GAIN_MIN;
	if (PGA_gain > PGA_GAIN_MAX)
		PGA_gain = PGA_GAIN_MAX;

	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x0019, PGA_gain);
	HAL_Delay(1);

	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x001B, PGA_gain+256);
	HAL_Delay(1);
  }   // End of Set_PGA_gain
*/

void Set_PGA_Gain(int PGA_gain)
{

	if (PGA_gain < PGA_GAIN_MIN)
		PGA_gain = PGA_GAIN_MIN;
	if (PGA_gain > PGA_GAIN_MAX)
		PGA_gain = PGA_GAIN_MAX;

	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x0018, PGA_gain);
	HAL_Delay(1);

	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x001A, PGA_gain+256);
	HAL_Delay(1);
}   // End of Set_PGA_gain

/*==========================================================================*/
/*
void Set_Spkr_DVC(int DAC_gain)  //gain is in 1 dB steps
{

	if (DAC_gain > DAC_GAIN_MAX)
		DAC_gain = DAC_GAIN_MAX;
	if (DAC_gain < DAC_GAIN_MIN)
		DAC_gain = DAC_GAIN_MIN;

	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x0026, DAC_gain+64);  //speaker volume
	HAL_Delay(Codec_Pause);

	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x0027, DAC_gain+320);  //speaker volume
	HAL_Delay(Codec_Pause);


}   // End of Set_Dig_DVC
*/
/*============================================================================*/
/*
void Set_Mic_ADC_DVC(int ADC_gain)  // gain in 0.375 dB steps
{

	if (ADC_gain > ADC_GAIN_MAX)
		ADC_gain = ADC_GAIN_MAX;
	if (ADC_gain < ADC_GAIN_MIN)
		ADC_gain = ADC_GAIN_MIN;


	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x404, ADC_gain);
	HAL_Delay(1);
	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x405, ADC_gain+256);
	HAL_Delay(1);


}   // End of Set_ADC_DVC
*/

void Set_ADC_DVC(int ADC_gain)  // gain in 0.375 dB steps
{

	if (ADC_gain > ADC_GAIN_MAX)
		ADC_gain = ADC_GAIN_MAX;
	if (ADC_gain < ADC_GAIN_MIN)
		ADC_gain = ADC_GAIN_MIN;


	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x400, ADC_gain);
	HAL_Delay(1);

	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x401, ADC_gain+256);
	HAL_Delay(1);


}   // End of Set_ADC_DVC




/*============================================================================*/
//Mute HP Outputs
/*
void Mute_HP(void)
{
	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x001C, 0);
	HAL_Delay(Codec_Pause);

	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x001D, 0);
	HAL_Delay(Codec_Pause);

}
*/
/*============================================================================*/


//Mute Speaker Outputs
/*
void Mute_Speakers(void)
{
	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x0026, 0xC0);
	HAL_Delay(Codec_Pause);

	AUDIO_IO_Write(AUDIO_I2C_ADDRESS, 0x0027, 0xC0);
	HAL_Delay(Codec_Pause);
}
*/


