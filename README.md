# ESP32 HUB75 LED Matrix

PlatformIO project for driving a 64x32 HUB75 RGB LED matrix panel from an ESP32 using the Arduino framework and I2S DMA.

The current firmware starts with a red, green, blue, white, and black display test, then runs a FastLED palette-based plasma animation.

## Hardware

- ESP32 development board using the PlatformIO `esp32dev` board target
- 64x32 HUB75 RGB LED matrix panel
- External 5 V power supply sized for the LED panel
- HUB75 ribbon cable from the ESP32 GPIO pins to the panel input connector
- Common ground between the ESP32 and the LED panel power supply

Do not power the panel from the ESP32 5 V pin. HUB75 panels can draw several amps depending on brightness and lit pixels.

## ESP32 PIN LAYOUT MAPPED TO HUB75
HUB75 | ESP32 | ESP32 | HUB75
      | 3v3   | GND   | GND
      | EN    | P23   | G2
      | SVP   | P22   | E
      | SVN   | TX    |  
      | P34   | RX    |  
      | P35   | P21   | R2
OE    | P32   | GND   | GND
CLK   | P33   | P19   | B1
C     | P25   | P18   | R1
A     | P26   | P5    | IO5
B2    | P27   | P17   | G1
IO14  | P14   | P16   | B
      | P12   | P4    | D
GND   | GND   | PD    |  
IO13  | P13   | P2    | LAT
      | SD2   | P15   |  
      | SD3   | SD1   |  
      | CMD   | SD0   |  
5v    | 5V    | CLK   |  

## HUB75 GPIO Mapping

The sketch uses this custom GPIO mapping:

| HUB75 signal | ESP32 GPIO |
| ---          | ---:       |
| R1           | 18         |
| G1           | 17         |
| B1           | 19         |
| R2           | 21         |
| G2           | 23         |
| B2           | 27         |
| A            | 26         |
| B            | 16         |
| C            | 25         |
| D            | 4          |
| CLK          | 33         |
| LAT/STB      | 2          |
| OE           | 32         |
| E            | Not used   |

Panel configuration:

- Width: 64 pixels
- Height: 32 pixels
- Chain length: 1 panel
- Brightness in firmware: `128` out of `255`
- Serial monitor speed: `115200`

## Software Setup

Install:

- Visual Studio Code
- PlatformIO extension
- USB driver for your ESP32 board, if required

This project uses:

- PlatformIO environment: `esp32dev`
- Platform: `espressif32`
- Framework: `arduino`
- Libraries:
  - `ESP32-HUB75-MatrixPanel-I2S-DMA`, vendored in `lib/ESP32-HUB75-MatrixPanel-DMA-master`
  - `FastLED`, declared in `platformio.ini`
  - `Adafruit GFX Library`, declared in `platformio.ini`

## Build and Upload

From the project root:

```sh
pio run
pio run --target upload
pio device monitor --baud 115200
```

The configured upload speed is `921600`. If uploads are unreliable, lower `upload_speed` in `platformio.ini`.

## Expected Startup Behavior

After reset or upload, the serial monitor should show initialization messages. The panel should display:

1. Red for 2 seconds
2. Green for 2 seconds
3. Blue for 2 seconds
4. White for 2 seconds
5. Black for 1 second
6. Continuous plasma animation

The animation changes palettes after every 1024 cycles.

## Troubleshooting

- If the panel stays blank, confirm the ribbon cable is connected to the panel input connector, not the output connector.
- If colors are swapped, verify the R/G/B GPIO wiring against the table above.
- If the display flickers or resets, use a stronger 5 V power supply and confirm the ESP32 and panel share ground.
- If initialization fails with an I2S DMA memory error, reduce panel size, chain length, or brightness before adding more panels.
- If serial output is unreadable, set the monitor baud rate to `115200`.

# HARDWARE LINKS
Waveshare P4 64x32 RGB LED Matrix - https://www.waveshare.com/rgb-matrix-p4-64x32.htm?srsltid=AfmBOorc7DjE0QZmudN0LzJZzf3w6uRR2I-Zb6qSzoCd6VZJYzBtV49H

HUB75 Board from Amazon.com - "ESP32 LED Matrix Adapter Board with Dual Power Input & HUB75 Interface for RPi - Easy Connect Shield for LED Matrix Panel Projects" - https://www.amazon.com/dp/B0FVNMRRTB?ref=ppx_yo2ov_dt_b_fed_asin_title

ESP32 w/ Breakout (breakout not needed) from Amazon.com "AITRIP 3 Sets ESP-WROOM-32 ESP32 ESP-32S 38Pin Development Board Type C Interface ESP-WROOM-32 with ESP32 Breakout Board Shield Terminal Adapter for ESP32 38 PIN Narrow" - https://www.amazon.com/dp/B0FQJG8ZBT?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1

