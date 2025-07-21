/*
 * Header file for setting codec gains
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



#ifndef CODEC_GAINS_H_
#define CODEC_GAINS_H_
#define PGA_GAIN_MIN 0
#define PGA_GAIN_MAX 31


#define DAC_GAIN_MIN 0
#define DAC_GAIN_MAX 63
#define HP_GAIN_MIN 0
#define HP_GAIN_MAX 63

#define ADC_GAIN_MIN 1
#define ADC_GAIN_MAX 255
void Set_HP_Gain(int HP_gain);
void Set_PGA_Gain(int PGA_gain);
void Set_ADC_DVC(int ADC_gain);
//void Set_Spkr_DVC(int DAC_gain);
//void Mute_HP(void);
//void Mute_Speakers(void);
//void wm8994_Mute(uint8_t Cmd);
//void Set_Mic_PGA_Gain(int PGA_gain);
//void Set_Mic_ADC_DVC(int ADC_gain);

#endif /* CODEC_GAINS_H_ */
