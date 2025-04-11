# Deployment Guide

This document provides instructions for building, deploying, and running the Casino Games application on supported platforms using the Arduino IDE.

## Development Environment Setup

### Prerequisites

Before building the application, ensure you have the following tools installed:

- **Arduino IDE** (version 1.8.x or 2.x)
- **ESP32 Board Package** by Espressif (version 2.0.11)
- **Required Libraries**:
  - LVGL (version 8.x)
  - TFT_eSPI or compatible display driver
  - Any other project-specific libraries

For UI development and modification:
- **SquareLine Studio** (for UI design)

### Arduino IDE Configuration

1. **Install the ESP32 Board Package**:
   - Open Arduino IDE
   - Go to `File > Preferences`
   - Add the following URL to the "Additional Boards Manager URLs" field:
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Go to `Tools > Board > Boards Manager`
   - Search for "esp32" and install version 2.0.11 of "ESP32 by Espressif Systems"

2. **Install Required Libraries**:
   - Go to `Tools > Manage Libraries...`
   - Search for and install the required libraries:
     - LVGL
     - TFT_eSPI (or your display driver)
     - Any other project-specific libraries

### Getting the Source Code

Clone the repository or download the source code:

```bash
git clone https://github.com/your-org/casino-games.git
```

## Building and Deploying

### Board Selection

Configure the Arduino IDE for your specific ESP32 board:

1. Go to `Tools > Board > ESP32 Arduino` and select your specific board model (e.g., "ESP32 Dev Module", "ESP32-S3 Dev Module", etc.)
2. Configure the board-specific parameters:
   - `Tools > Flash Mode` > "QIO" (usually)
   - `Tools > Flash Size` > "4MB" or larger
   - `Tools > Partition Scheme` > "Default" or "Huge APP" for larger applications
   - `Tools > PSRAM` > "Enabled" (if your board supports it)
   - `Tools > Upload Speed` > "921600" (or lower if experiencing issues)

### Display Configuration

If using TFT_eSPI, configure the display settings:

1. Locate the `User_Setup.h` file in the TFT_eSPI library folder
2. Edit it to match your display configuration (pins, controller type, etc.)
3. Alternatively, create a custom `User_Setup_Select.h` file in your project

### Compiling the Project

1. Open the main `.ino` file in Arduino IDE
2. Click the "Verify" button (✓) to compile the project
3. Fix any compilation errors that may occur

### Uploading to the ESP32

1. Connect your ESP32 device to your computer via USB
2. Select the correct port under `Tools > Port`
3. Click the "Upload" button (→) to flash the firmware to your ESP32
4. If needed, press the BOOT/RESET buttons on your ESP32 to enter programming mode

### Serial Monitor

To view debug output from the application:

1. Go to `Tools > Serial Monitor`
2. Set the baud rate to match your application (usually 115200)
3. The serial monitor will display printf output from the application

## Hardware Requirements

### Minimum Specifications

- **ESP32** microcontroller (dual-core recommended)
- **Display**: 320x240 or larger TFT display with touch support
- **RAM**: ESP32 with PSRAM recommended for smooth animations
- **Flash**: At least 4MB flash storage
- **Input**: Touch screen or physical buttons for control

### Recommended Hardware

- **ESP32-S3** with PSRAM
- **ILI9341** or similar display with 320x240 resolution or higher
- **XPT2046** or similar touch controller
- **Audio DAC** and amplifier for sound effects (optional)

## Pin Configuration

Ensure your hardware is wired according to the pin definitions in your code:

### Display Pins
These should match the configuration in your TFT_eSPI setup:
```
TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_MISO, TFT_SCLK
```

### Touch Pins (if applicable)
```
TOUCH_CS, TOUCH_IRQ
```

### Audio Pins (if applicable)
```
I2S_BCLK, I2S_LRC, I2S_DOUT
```

## Customization

### Display Configuration

To adapt the application for different display sizes or types:

1. Update the display configuration in the TFT_eSPI User_Setup.h file
2. Update the LVGL configuration in your project's lv_conf.h
3. Redesign screens in SquareLine Studio if necessary
4. Export updated UI files from SquareLine Studio

### Adding New Games

To add a new game to the application:

1. Create a new directory in `ui/src/games/[your_game_name]/`
2. Implement the game logic in C files within this directory
3. Design UI screens for the game in SquareLine Studio
4. Add event handlers in `ui_events.c`
5. Update the home screen to include a button for the new game

## Troubleshooting

### Common Build Issues

1. **Missing Libraries**:
   ```
   fatal error: lvgl.h: No such file or directory
   ```
   Solution: Install the required library via the Arduino Library Manager

2. **Compilation Errors**:
   - Check that the ESP32 board package version is 2.0.11
   - Ensure all required libraries are installed
   - Verify that your code is compatible with Arduino-ESP32

3. **Upload Errors**:
   - Verify that the device is properly connected
   - Select the correct port in the Arduino IDE
   - Press the BOOT button during the "Connecting..." phase
   - Try a slower upload speed
   - Check USB cable (use a data cable, not charge-only)

### Common Runtime Issues

1. **Display Issues**:
   - Check TFT_eSPI configuration matches your wiring
   - Verify power supply is adequate (most displays require 3.3V and sufficient current)

2. **Touch Input Problems**:
   - Validate touch controller configuration
   - Calibrate touch if necessary

3. **Memory Issues**:
   - Enable PSRAM in Tools menu if your board supports it
   - Monitor heap usage through Serial Monitor
   - Optimize image assets and animations

## Performance Optimization

For optimal performance on ESP32:

1. **Memory Management**:
   - Use PSRAM when available (`ps_malloc()` instead of `malloc()`)
   - Minimize dynamic allocations during gameplay

2. **Display Performance**:
   - Use hardware acceleration when available (DMA)
   - Optimize LVGL refresh rate and buffer sizes

3. **Compilation Optimization**:
   - Try different optimization levels in `Tools > Optimization`
   - Balance between code size and speed

## Deployment Checklist

Before deploying to production hardware:

- [ ] Verify all games function correctly
- [ ] Test all animations and transitions
- [ ] Optimize performance for target hardware
- [ ] Remove or disable verbose debug statements
- [ ] Test power consumption
- [ ] Validate touch input accuracy

## Technical Support

For technical support or to report deployment issues:

- Open a GitHub issue on the project repository
- Contact the development team via email at support@example.com
- Check the troubleshooting guide for common solutions

## Audio Configuration

To set up the DFPlayer Mini for audio playback:

1. **Prepare the microSD Card**:
   - Format a microSD card (32GB or smaller) as FAT32
   - Create a folder named `mp3` in the root directory
   - Add MP3 files to this folder with specific naming:
     - `001.mp3`, `002.mp3`, etc. matching the sound IDs in the code
   - For best results, use MP3 files with 32kbps bitrate

2. **Hardware Connections**:
   ```
   ESP32           DFPlayer Mini
   -------------------------------
   TX2 (GPIO17) -- RX
   RX2 (GPIO16) -- TX (with 1kΩ resistor in series)
   GND ----------- GND
   5V ------------ VCC
   
   DFPlayer Mini   Speaker/Amplifier
   -------------------------------
   SPK_1 --------- Speaker + 
   SPK_2 --------- Speaker -
   ```

3. **Library Installation**:
   - If using the DFRobotDFPlayerMini library:
     - In Arduino IDE, go to Tools → Manage Libraries
     - Search for "DFRobotDFPlayerMini" and install it

4. **Troubleshooting Tips**:
   - If playback is unstable, add a 1μF capacitor between VCC and GND of the DFPlayer
   - For reliable operation, use a separate power supply for the DFPlayer when driving larger speakers
   - The BUSY pin can be connected to an ESP32 input pin to monitor playback status

---

*This deployment guide is maintained alongside the codebase and will be updated as needed for new Arduino-ESP32 versions or hardware configurations.* 