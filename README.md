# DX FT8  A MULTIBAND FT8 DIGITAL MODE 5 BANDS OR 7 BANDS TABLET TRANSCEIVER

![IMG_2011](https://github.com/user-attachments/assets/36db0864-356a-4503-b567-8c01f2cb571e)


----------------------------------------------------------------------------------------------------------------------------------

DX FT8 FIRMWARE UPDATE HISTORY:

----------------------------------------------------------------------------------------------------------------------------------
DX FT8 Project Firmware Version 1.9.3 Release Notes: 31 March 2025

This version of the firmware updated to include SOTA / POTA calling CQ plus the ability to send Free Text messages.

You can choose 4 type of CQ under tune menu with assigned buttons:
![IMG_2012](https://github.com/user-attachments/assets/e2b0294d-7ba5-4f67-bd8a-4e218d1b6a48)

CQ [YourCall] [YourGrid]

CQ POTA [YourCall] [YourGrid]

CQ SOTA [YourCall] [YourGrid]

CQ QRP [YourCall] [YourGrid]

If you're interested in free text to add your preferred call text, you can add 2 fields in StationData.txt
----------------------------------------------------------------------------------------------------------
[YourCall]:[YourGrid]:[Free Text 1]:[Free Text 2]

Free Text can be 1 to 27 characters in the range of [ 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ+-./?]

To choose between CQ and Free Text, click the Free1 and Free2 buttons  under Tune menu

Preferred CQ Button choice is displayed in main screen. 

- Display Blanking has been added. To BLANK the Display, touch the very Upper Right Hand Corner of the Display.

To turn the Display back On, touch anywhere on the screen. This reduces the current draw by about 100 mA DC. 

---------------------------------------------------------------------------------------------------------------------------------
   ![Touchscreen Blanking](https://github.com/user-attachments/assets/5200658a-2ce7-4d6f-93e6-4fd22537c68c)

----------------------------------------------------------------------------------------------------------------------------------
- The Audio DSP Algorithms have been modified to improve Unwanted Side Band Suppression.

- The Firmware is now being provided as a HEX File to make installation via ST Link easier.

-------------------------------------------------------------------------------------------------------------------------------

The SOTA / POTA capability was initially developed by Wei, AG6AU.

Here is a link to Wei’s GitHub Repository:

https://github.com/wcheng95/DX-FT8-MULTIBAND-TABLET-TRANSCEIVER-Source/tree/main

Many thanks to Wei and hopefully others will use the Open Source Code to make great additions to the code.

WEI, AG6AQ's Instructions how to setup and use DX FT8 on SOTA/POTA mode is in these links:

https://dxft8.groups.io/g/main/message/300

https://dxft8.groups.io/g/main/message/302


---------------------------------------------------------------------------------------------------------------------------------
DX FT8 3D PRINTED CASE FILES ADDED. A big Thank You to Dave,ZL1DMM for his excellent 3D case design.
 ![large_display_IMG_20241127_194136](https://github.com/user-attachments/assets/80376cca-b342-4463-8e1c-0aa2e032ad22)
----------------------------------------------------------------------------------------------------------------------------------
Please note that for Users with Five Band Boards or Seven Band Boards that it is highly recommended that you use a 

Freshly Formatted SD Card with a Fresh StationData.txt file before using DX FT8 V1.9 for the first time.

- An Abstract outlining DX FT8 Conception and Design path as a PDF file added.

- ACKNOWLEDGEMENT: We would like to thank Paul Winwood, G8KIG, for his contributions to refine and refactor DX FT8 Firmware as well

  as adding new features and cleaning the code. Paul's contributions are reflected in DX FT8 V1.9.2 firmware.
  
----------------------------------------------------------------------------------------------------------------------------------------------  

  Check Paul's github page for latest source code files: https://github.com/g8kig/DX-FT8-MULTIBAND-TABLET-TRANSCEIVER-Source/releases/tag/V1.9.2
  
----------------------------------------------------------------------------------------------------------------------------------------------

DX FT8 TRANSCEIVER PROJECT is a collaboration between Charles(Charley)Hill, W5BAA and Barbaros(Barb)Asuroglu, WB2CBA.

DX FT8 Project is brain child of Charles(Charley)Hill, W5BAA. Charley designed and build various versions of GUI based FT8 Transceivers over the years. 

I was lucky enough to collaborate with Charley on 3 different versions of GUI FT8 Transceiver.

DX FT8 is the culmination of all that experience we gained from previous versions.

I can't thank enough Charley for his excellent GUI FT8 Firmware and his perseverance to create a standalone FT8 TABLET Transceiver.

It's a pleasure for me to collaborate with Charley,W5BAA, on hardware side, RF design and PCB design of DX FT8 Transceiver.

DX FT8 is an OPEN SOURCE PROJECT.

DX FT8 is a FT8 Digital mode capable HF QRPp GUI (Graphical User Interface) based multiband Transceiver.

DX FT8 is abreviation for Digital Xceiver for FT8. 

Main aim of DX FT8 Transceiver Project is to create a highly portable stand-alone FT8 GUI Transceiver. Stand-alone aim is to create a user interface for working FT8 digital mode plus Multiband transceiver packed into one unit. 

This creates an advantage for carrying one GUI based FT8 operation capable Transceiver unit and no longer needs to carry a PC or a laptop or tablet for GUI interface operation for FT8 with a classic transceiver. 

This approach is quite appealing for smaller and lighter setups for backpacking for SOTA or POTA activations or as a travel transceiver with FT8.  

Here are some highlights on DX FT8 Specifications:

-	DX FT8 Transceiver GUI (Graphical User Interface) and processing power comes from ST Micro STM32F746 DISCO Evaluation board. This is a ARM CORTEX based evaluation board for STM32F746 microcontrollers with below outlined specifications: 

-	STM32F746NGH6 Arm® Cortex® core-based microcontroller with 1 Mbyte of Flash memory and 340 Kbytes of RAM, in BGA216 package 

-	4.3 inch RGB 480×272 color LCD-TFT with capacitive touch screen 

-	128-Mbit Quad-SPI Flash memory
 
-	DX FT8 Transceiver RF Board plugs into STM32F746 DISCO evaluation board to form the DX FT8 transceiver. 

-	DX FT8 Transceiver operates on 5 HF bands or 7 Bands depending on PCB type. Design files for both 5 band and 7 bands boards are posted in this github page.

-	These bands are:

For 5 Bands Board:
  
1 – 20m (14.074 MHz)

2- 17m (18.100 MHz)

3- 15m (21.074 MHz)

4- 12m (24.915 MHz)

5- 10m (28.074 MHz)

For 7 Bands Board:
  
1 – 40m (7.074 MHz)

2- 30m (10.136 MHz)

3 – 20m (14.074 MHz)

4- 17m (18.100 MHz)

5- 15m (21.074 MHz)

6- 12m (24.915 MHz)

7- 10m (28.074 MHz)


DX FT8 Transceiver has two RF Power Output Selection, LOW RF POWER and HIGH RF POWER which can be selected with the RF POWER Slide switch on the side of the transceiver.

40m	   372mW	       844mW

30m	   373mW	       843mW

20m	   380mW	       823mW

17m	   354mW	       762mW

15m	   314mW	       654mW

12m	   259mW	       520mW

10m	   231mW	       445mW

-	DX FT8 Transceiver can operate either from 5V USB power bank or any 1000mA capacity USB power source or by using the DC barrel Connector can be powered from 7V to 15V external power supply. A power supply source can be selected with DC POWER SELECT slide switch located on the side of the Transceiver. 

-	DX FT8 TRANSCEIVER uses an unconventional RF power Amplifier consisting of a TTL octal buffer IC and step up RF Transformer. There is no conventional MOSFET PA transistors. This creates an extremely resilient RF PA for failure due to high SWR or no antenna accidental operations.  This is an advantage for portable operations as antenna conditions can vary.

-	DX FT8 TRANSCEIVER incorporates a TAYLOE detector based Qudarature Sampling detector receiver with a high gain RF Preamplifier which outputs an I and Q phase output to STM32F746 DISCO board which generates true Upper Side Band (USB) SSB receive signal. 

-	A short video of DX FT8 in action:
  https://www.youtube.com/watch?v=8b2WOxESAVU

- DX FT8 PROJECT FIRMWARE STM IDE Environment Source code files can be downloaded from this link:

https://drive.google.com/drive/folders/1oobpyw1_IDn4CDS9kfwyihfSv9H_CrcM?usp=sharing

Source file is too large to upload to Github. To circumvent around Github file size restriction, a google drive solution is preferred.

The most recent version can be downloaded from this link:

https://github.com/g8kig/DX-FT8-MULTIBAND-TABLET-TRANSCEIVER-Source/releases/tag/untagged-cf0e12cb6f30d0435487

ACKNOWLEDGEMENT:

DX-FT8 Firmware is inspired by work done by Karlis Goba, YL3JG. Here is a link to his website: https://github.com/kgoba/ft8_lib. 

---------------------------------------------------------------------------------------------------------------------------------
KIT ORDERING INFO:
---------------------------------------------------------------------------------------------------------------------------------
All DXFT8 Kit shipments after 14 January 2025 will be 7 Band DXFT8 kits and that the firmware will support both the 5 Band and 7 Band units. 

There is nothing operationally different between the two except the additional bands covered.

---------------------------------------------------------------------------------------------------------------------------------
 
The DX FT8 Kits may be ordered from Kees TALEN (K5BCQ) via PayPal 

Paypal ID is  K5BCQ@ arrl.net

Order as "Goods or Services". Yes that incurs a PayPal Fee but allows K5BCQ to print a shipping label.
 
The kits are divided into two pieces, one set of DX FT8 RF BOARD items from K5BCQ and 

one set of items you must order directly from Mouser, Digikey, etc. to complete the DX FT8 
Transceiver.
 

                        
-	KIT PRICE is US$40.00 for DX FT8 RF BOARD and miscellaneous parts to complete RF board.
      
-	 Shipping for a US address is US$5.00 . 

International shipping will depend on Country. Please send an email to: K5BCQ@arrl.net for inquiring shipping cost to your country.
 
Additional parts to order to finalize the kit building:

1-	STMicro STM32F746 DISCO Evaluation board

Sample Link: 
https://www.digikey.com/en/products/detail/stmicroelectronics/STM32F746G-DISCO/5267791?utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Low%20ROAS%20Categories&utm_term=&utm_content=&utm_id=go_cmp-20243063506_adg-_ad-__dev-c_ext-_prd-5267791_sig-Cj0KCQjwurS3BhCGARIsADdUH50Ts6paiim-lRjlgUEfkDAu1IRlpNb7VxFkCvfQx1aE6lQbkA6ywvwaAkE2EALw_wcB&gad_source=1&gclid=Cj0KCQjwurS3BhCGARIsADdUH50Ts6paiim-lRjlgUEfkDAu1IRlpNb7VxFkCvfQx1aE6lQbkA6ywvwaAkE2EALw_wcB

1-	Micro-SD card for STM board  

Sample Link: 
https://a.co/d/0k5Jp81


1-	12V power supply or 5V supply provided by the user

1-	CR2032 coin cell provided by the user

 
------------------------------------------------------------------------------------------------------------ 









