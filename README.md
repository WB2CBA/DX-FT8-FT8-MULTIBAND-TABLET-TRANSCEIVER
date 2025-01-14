# DX FT8  A MULTIBAND FT8 DIGITAL MODE 5 BANDS OR 7 BANDS TABLET TRANSCEIVER

![DX FT8 INTRO](https://github.com/user-attachments/assets/408df1d6-2f16-4091-8fff-48c7fffb95d2)

DX FT8 FIRMWARE UPDATE HISTORY:

----------------------------------------------------------------------------------------------------------------------------------
DX FT8 Project Firmware Version 1.8 Release Note 14 January 2025:

----------------------------------------------------------------------------------------------------------------------------------
DX FT8 Project Firmware Version 1.8 Release Notes: 14 January 2025

This version of the firmware was written to make six changes:

1) Automatic update of the Date Display and ADIF File Name occurs when the RTC Date changes.

2) When switching from QSO Mode to Beacon Mode or Beacon Mode to QSO the FT Transmit Frequency does

not change.

3) The contents of the StationData.txt file is checked to make sure the entered data is valid. When the Station Data is valid

the user’s Call Sign and Maidenhead Locator are displayed on the boot up screen. If the data is not valid an error message is

displayed instead of the User’s Station Data.

4) The QSO and Beacon FT8 Traffic Handling routines have been extensively revised and tested On The Air to provide for

repeat messages being transmitted when propagation conditions cause normal FT8 exchanges to be disrupted. Please see the

Flow Chart Below for a detailed description of how both the QSO Mode and Beacon Mode now operate.

5) With the release of the Seven Band Board a major revision of the Band Switching routines has been made so that Both

Existing Five Band Boards and New Seven Bands are serviced by a single application. The Version 1.8 firmware 

interrogates the attached DX FT8 board to determine board pedigree and then sets the Band Switching Parameters

accordingly.

Please note that for Users with Five Band Boards or Seven Band Boards that it is highly recommended that you use a 

Freshly Formatted SD Card with a Fresh StationData.txt file before using DX FT8 V1.8 for the first time.

6) The DX FT8 User Guide has been revised to capture the changes made with the Firmware Version 1.8 Release.

Please note that Versions 1.5 thru 1.7 have not and will not be released

- An Abstract outlining DX FT8 Conception and Design path as a PDF file added.

-----------------------------------------------------------------------------------------------------------------------------------

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

-	DX FT8 Transceiver operates on 5 HF bands or 7 Bands depending on PCB type. These bands are:

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

Souce file is too large to upload to Github. To circumvent around Github file size restriction, a google drive solution is preferred.

ACKNOWLEDGEMENT:

DX-FT8 Firmware is inspired by work done by Karlis Goba, YL3JG. Here is a link to his website: https://github.com/kgoba/ft8_lib. 



---------------------------------------------------------------------------------------------------------------
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









