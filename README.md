# DX FT8 A MULTIBAND FT8 DIGITAL MODE TABLET TRANSCEIVER

![DX FT8 INTRO](https://github.com/user-attachments/assets/408df1d6-2f16-4091-8fff-48c7fffb95d2)

----------------------------------------------------------------------------------------------------------------------------------

## UPDATE #1 (11/04/2024):

- Firmware Update DX_FT8_V1.1.bin released.
- DX FT8 V1.1 Firmware, DX_FT8_V1.1.bin release notes PDF File added.
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

# Here are some highlights on DX FT8 Specifications:

- DX FT8 Transceiver GUI (Graphical User Interface) and processing power comes from ST Micro STM32F746 DISCO Evaluation board. This is a ARM CORTEX based evaluation board for STM32F746 microcontrollers with below outlined specifications:

  - STM32F746NGH6 Arm® Cortex® core-based microcontroller with 1 Mbyte of Flash memory and 340 Kbytes of RAM, in BGA216 package
  - 4.3 inch RGB 480×272 color LCD-TFT with capacitive touch screen
  - 128-Mbit Quad-SPI Flash memory

- DX FT8 Transceiver RF Board plugs into STM32F746 DISCO evaluation board to form the DX FT8 transceiver.

- DX FT8 Transceiver operates on 5 HF bands. These bands are:
  1. 20m (14.074 MHz)
  2. 17m (18.100 MHz)
  3. 15m (21.074 MHz)
  4. 12m (24.915 MHz)
  5. 10m (28.074 MHz)

- DX FT8 Transceiver has two RF Power Output Selection, LOW RF POWER and HIGH RF POWER which can be selected with the RF POWER Slide switch on the side of the transceiver.

  | Band  | Min   | Max   |
  | :---: | ----: | ----: |
  | 20m   | 380mW | 823mW |
  | 17m   | 354mW | 762mW |
  | 15m   | 314mW | 654mW |
  | 12m   | 259mW | 520mW |
  | 10m   | 231mW | 445mW |

- DX FT8 Transceiver can operate either from 5V USB power bank or any 1000mA capacity USB power source or by using the DC barrel Connector can be powered from 7V to 15V external power supply. A power supply source can be selected with DC POWER SELECT slide switch located on the side of the Transceiver.

- DX FT8 TRANSCEIVER uses an unconventional RF power Amplifier consisting of a TTL octal buffer IC and step up RF Transformer. There is no conventional MOSFET PA transistors. This creates an extremely resilient RF PA for failure due to high SWR or no antenna accidental operations. This is an advantage for portable operations as antenna conditions can vary.

- DX FT8 TRANSCEIVER incorporates a TAYLOE detector based Qudarature Sampling detector receiver with a high gain RF Preamplifier which outputs an I and Q phase output to STM32F746 DISCO board which generates true Upper Side Band (USB) SSB receive signal.

- A short video of DX FT8 in action:
  * https://www.youtube.com/watch?v=8b2WOxESAVU

- DX FT8 PROJECT FIRMWARE STM IDE Environment Source code files can be found inside the `Kathy` directory.


# KIT ORDERING INFO:

The DX FT8 Kits may be ordered from Kees TALEN (K5BCQ) via PayPal
- Paypal ID is K5BCQ@arrl.net

Order as Merchandise. Yes that incurs a PayPal Fee but allows K5BCQ to print a shipping label.

The kits are divided into two pieces:
- one set of DX FT8 RF BOARD items from K5BCQ, and
- one set of items you must order directly from Mouser, Digikey, etc. to complete the DX FT8 Transceiver.

KIT PRICE is US$40.00 for DX FT8 RF BOARD and miscellaneous parts to complete RF board.

Shipping for a US address is US$5.00 .

International shipping will depend on Country. Please send an email to: K5BCQ@arrl.net for inquiring shipping cost to your country.

Additional parts to order to finalize the kit building:

- STMicro STM32F746 DISCO Evaluation board
  * [Digikey](https://www.digikey.com/en/products/detail/stmicroelectronics/STM32F746G-DISCO/5267791)

- Micro-SD card for STM board
  * [Amazon](https://www.amazon.com/dp/B00316OUDS)

- 12V power supply or 5V supply provided by the user

- CR2032 coin cell provided by the user
