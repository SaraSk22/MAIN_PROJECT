Real-Time Vehicle Status Monitoring System using CAN Protocol
This project implements a real-time vehicle monitoring system using the Controller Area Network (CAN) protocol with an ARM7 microcontroller (LPC21xx family). It monitors fuel level, driver indication (left/right turn signals), and airbag status, and communicates these events across multiple nodes over CAN.
🚗 Project Overview
Modern vehicles rely on distributed electronic control units (ECUs) to manage different subsystems (fuel system, airbag system, indicators, etc.). CAN protocol enables these ECUs to communicate efficiently.
This project demonstrates a mini ECU network consisting of:
•	Main Node → Central control & display (LCD + accelerometer + CAN master)
•	Fuel Node → Monitors fuel level using an ADC and transmits percentage via CAN
•	Indicator Node → Receives left/right indication signals and displays them using LEDs
Together, these nodes simulate a real-time vehicle monitoring system.
__________________________________________________________________________________________________________________________________________________________________
📌 Features
•	Fuel Monitoring:
    o	Reads analog fuel sensor data via ADC (LM35/voltage divider)
    o	Calculates fuel percentage
    o	Displays fuel % on LCD
    o	Sends fuel data to Main Node over CAN
•	Driver Indications (Left/Right):
    o	External interrupts (EINT0/EINT3) used for left/right signal inputs
    o	Sends indication data ('L' or 'R') to Indicator Node
    o	LEDs simulate running light pattern (left-to-right / right-to-left)
•	Airbag Detection:
    o	MMA7660 accelerometer connected via I²C
    o Detects abnormal tilt/acceleration (crash simulation)
    o	Displays AIRBAG OPEN or SAFE on LCD
•	CAN Communication:
    o	Implemented using LPC21xx CAN controller
    o	Messages exchanged between nodes with unique CAN IDs
______________________________________________________________________________________________________________________________________________________________________
🛠️ Hardware Requirements
•	Microcontroller: LPC2148 / LPC2129 (ARM7 TDMI-S)
•	Modules & Components:
    o	MMA7660FC Accelerometer (I²C based)
    o	LCD 16x2 Display
    o	Fuel Sensor (LM35 / Potentiometer / Voltage Divider for ADC)
    o	LEDs (for turn indicators)
    o	External Push Buttons (for Left/Right indication via interrupts)
    o	CAN Transceiver (MCP2551 / SN65HVD230)
•	Power Supply: 5V regulated
________________________________________________________________________________________________________________________________________________________________________
💻 Software Requirements
•	Compiler/IDE: Keil µVision
•	Programmer Tool: Flash Magic
•	Languages: Embedded C
•	Other Tools: Proteus (for simulation, optional)
__________________________________________________________________________________________________________________________________________________________________________
📂 Project Structure
├── MAIN_NODE.C        # Main ECU (Fuel display, airbag monitoring, turn signal send)
├── FUEL_NODE.C        # Fuel ECU (Reads ADC, sends fuel % over CAN)
├── INDICATOR.C        # Indicator ECU (Receives turn signal, controls LEDs)
├── lcd.h / lcd_defines.h
├── can.h / can_defines.h
├── adc.h / adc_defines.h
├── i2cc.h / i2cc_defines.h
├── delay.h
├── interrupt.h
├── pin_connect_block.h
└── README.md          # Project Documentation
___________________________________________________________________________________________________________________________________________________________________________
🔗 CAN Message IDs
•	ID = 10: Left/Right indicator message from Main Node → Indicator Node
•	ID = 11: Fuel percentage message from Fuel Node → Main Node
___________________________________________________________________________________________________________________________________________________________________________
⚙️ How It Works
1.	Fuel Node:
    o	Reads analog fuel value via ADC
    o	Converts to percentage
    o	Sends CAN frame with ID=11 to Main Node
2.	Main Node:
    o	Receives fuel percentage, displays on LCD
    o	Reads accelerometer data via I²C, checks crash conditions
    o	Displays SAFE or AIRBAG OPEN on LCD
    o	Handles button interrupts for left/right indicators
    o	Sends CAN frame with ID=10 and Data='L'/'R' to Indicator Node
3.	Indicator Node:
    o	Receives left/right command from Main Node
    o	Runs LED pattern (left-to-right or right-to-left) accordingly
_____________________________________________________________________________________________________________________________________________________________________________
📊 Flow Diagram
[Fuel Node] --(Fuel %)--> [Main Node] --(Turn signals)--> [Indicator Node]
                                |
                         (Airbag Monitoring)
                                ↓
                              [LCD]
_______________________________________________________________________________________________________________________________________________________________________________
🚀 How to Run
1.	Flash each .c file to the respective LPC2148 boards (Main, Fuel, Indicator).
2.	Connect CAN transceivers (MCP2551) to each board and link via CAN bus.
3.	Power up all nodes.
4.	Observe:
    o	Fuel % updates on Main Node LCD
    o	Left/Right buttons trigger LED animations.
    o	Accelerometer tilt triggers Airbag alert.
