# Smart Weather Station 
A simple IoT-based weather monitoring system built using an ESP32. 
This project measures temperature and humidity, displays the data on an OLED screen, and uses LEDs to indicate environmental conditions in real time.

## Features
- Real-time temperature monitoring
- Humidity measurement
- OLED display output
- Adjustable temperature threshold using a potentiometer
- WiFi connection support (optional for expansion)
- LED status indicators:
  - White-normal conditions
  - Green-warm
  - Blue-humid
  - Red-high temperature + high humidity (danger)

## Hardware Requirements
- ESP32 development board
- DHT11 temperature & humidity sensor
- OLED display (SSD1306, I2C, 128×64)
- Analog Input Potentiometer
- LEDs (Red, Green, Blue, White)
- Breadboard & jumper wires

## Pin Configuration
| Component	  |  ESP32 Pin   |
| ------------  | --------- |
| DHT11 Data	 | GPIO 4 |
| Potentiometer	| GPIO 34   |
| LED Red	      |GPIO 12    |
| LED Green     |	GPIO 13   |
| LED Blue	    |GPIO 14    |
| LED White	    |GPIO 27    |
| OLED (SDA)    |	GPIO 21 |
| OLED (SCL)    |	GPIO 22 |

## Schematic Diagram
Full Circuit Schematic
<img width="957" height="795" alt="Screenshot From 2026-04-16 17-49-23" src="https://github.com/user-attachments/assets/bf140374-9d8b-470a-9453-34cc1c74bdf8" />
This schematic shows the wiring of the ESP32-based weather station, including the sensor, display, user input, and LED indicators.

## How It Works
- The DHT11 sensor reads temperature and humidity.
- The potentiometer adjusts the temperature threshold (20°C – 40°C).
- The system compares real-time readings with thresholds:
   - Temperature ≥ threshold - "Too Hot"
   - Humidity ≥ 70% - "Too Humid"
- Based on conditions, LEDs indicate system status.
- The OLED display shows:
   - Temperature
   - Humidity
Current threshold
- Data is printed to the Serial Monitor for debugging

## Display Output
The OLED shows:
- Project title
- Temperature 
- Humidity 
- Alert threshold 

## Libraries Used
- Wire.h
- Adafruit_GFX.h
- Adafruit_SSD1306.h
- DHT.h
- WiFi.h

## Getting Started
- Install Arduino IDE and ESP32 board support
- Install required libraries
- Connect components as per schematic
- Upload the code to ESP32
- Open Serial Monitor (115200 baud rate)

## Notes
- Threshold adjustment only affects temperature
- WiFi is optional and expandable

## Project Images

###  Full Setup
<img width="565" height="832" alt="Screenshot From 2026-04-17 16-36-49" src="https://github.com/user-attachments/assets/32f49292-c453-4fe3-af16-10e4d617270b" />

## Author
Developed as a mini-project using ESP32 for embedded systems and IoT learning

