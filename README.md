# DX-FT8---FT8-MULTIBAND-TABLET-TRANSCEIVER

![IMG_5568](https://github.com/user-attachments/assets/4db14f59-7d77-43b2-ba8d-116dba856e28)

DX FT8 is a FT8 Digital mode capable HF QRPp GUI (Graphical User Interface) based multiband Transceiver.  

Main aim of DX FT8 TRX Project is to create a highly portable self-contained FT8 GUI Transceiver. Self-contained aim is to create User interface plus Multiband transceiver in the same unit. 

This creates an advantage of carrying one GUI based TRX unit and no longer need to carry a PC or a laptop or tablet for GUI interface operation for FT8 with a classic transceiver. 

This approach is quite appealing for smaller and lighter setups for backpacking for SOTA or POTA activations or as a travel transceiver with FT8.  

Here are some highlights on DX FT8 Specifications:

-	DX FT8 Transceiver GUI (Graphical User Interface) and processing power comes from ST Micro STM32F746 DISCO Evaluation board. This is a ARM CORTEX based evaluation board for STM32F746 microcontrollers with below outlined specifications: 

-	STM32F746NGH6 Arm® Cortex® core-based microcontroller with 1 Mbyte of Flash memory and 340 Kbytes of RAM, in BGA216 package 

-	4.3” RGB 480×272 color LCD-TFT with capacitive touch screen 

-	128-Mbit Quad-SPI Flash memory
 
-	DX FT8 Transceiver RF Board plugs into STM32F746 DISCO evaluation board to form the DX FT8 transceiver. 

-	DX FT8 Transceiver operates on 5 HF bands. These bands are:
  
1 – 20m (14.074 MHz)

2- 17m (18.100 MHz)

3- 15m (21.074 MHz)

4- 12m (24.915 MHz)

5- 10m (28.074 MHz)

DX FT8 Transceiver has two RF Power Output Selection, HIGH RF POWER and LOW RF POWER which can be selected with the RF POWER Slide switch on the side of the transceiver.

20m	   380mW	       823mW

17m	   354mW	       762mW

15m	   314mW	       654mW

12m	   259mW	       520mW

10m	   231mW	       445mW

-	DX FT8 Transceiver can operate from 5V USB power bank or any 500mA capacity USB power source or by using DC barrel Connector can be powered from 7V to 15V external power supply. A power supply source can be selected with DC POWER SELECT slide switch located in one side of the Transceiver. 

-	DX FT8 TRANSCEIVER uses an unconventional RF power Amplifier consisting of a TTL octal buffer IC and step up RF Transformer. There is no MOSFET PA transistors. This creates an extremely resilient RF PA for failure due to high SWR or no antenna accidental operations.  This is an advantage for portable operations as antenna conditions can vary.

-	DX FT8 TRANSCEIVER incorporates a TAYLOE detector based Qudarature Sampling detector receiver which outputs an I and Q phase output to STM32F746 DISCO board which generates through Upper Side Band SSB receive signal.


