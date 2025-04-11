# Audio System

The Audio System provides sound effects and background music for the casino games application, enhancing the user experience with auditory feedback.

## Overview

The application implements audio playback using a DFPlayer Mini MP3 module connected to the ESP32. This module handles MP3 decoding and playback autonomously, allowing for easy integration of audio into the casino games without requiring significant processing resources from the main microcontroller.

## Directory Structure

Audio-related files are located in:
```
ui/src/
├── mp3_player.c   # Implementation of MP3 playback functions
└── mp3_player.h   # Function declarations and constants
```

## Implementation

### Hardware Configuration

The audio system relies on a DFPlayer Mini module:

- **DFPlayer Mini Module**:
  - Standalone MP3 player with microSD card support
  - Communicates with ESP32 via UART (Serial)
  - Integrated amplifier for directly driving small speakers
  - MP3 files stored on microSD card organized with specific numbering

### Key Components

The audio system consists of several components:

1. **DFPlayer Mini**: External module that handles MP3 decoding and playback
2. **UART Communication**: Serial protocol to control the DFPlayer
3. **MicroSD Card**: Storage for MP3 sound files
4. **Speaker**: Connected directly to the DFPlayer's output pins

## Key Functions

### Playback Control

```c
// Initialize the audio system
void mp3_player_init();

// Play a sound effect (non-blocking)
void mp3_play_sound(int sound_id);

// Play background music (loops continuously)
void mp3_play_music(int music_id);

// Stop all audio playback
void mp3_stop();

// Set volume level (0-30)
void mp3_set_volume(uint8_t volume);

// Check if audio is currently playing
bool mp3_is_playing();

// Play advertisement sound with stop option
void mp3_play_advertisement_with_stop(int sound_id, int stop_sound_id);
```

### Sound IDs

Sound effects and music tracks are referenced by numeric IDs that correspond to the file numbers on the microSD card:

```c
// Game-specific sound IDs
#define SOUND_SLOTS_SPIN       1
#define SOUND_SLOTS_WIN        2
#define SOUND_SLOTS_JACKPOT    3
#define SOUND_DICE_ROLL        4
#define SOUND_DICE_WIN         5
#define SOUND_CARD_DEAL        6
#define SOUND_BJ_WIN           7
#define SOUND_BJ_LOSE          8
#define SOUND_BJ_PUSH          9
#define SOUND_BUTTON_CLICK     10

// Music IDs
#define MUSIC_MAIN_THEME       20
#define MUSIC_SLOTS_BG         21
#define MUSIC_BLACKJACK_BG     22
#define MUSIC_DICE_BG          23
```

## Integration with Arduino

The audio system is integrated with the Arduino framework using:

1. **HardwareSerial**: For UART communication with the DFPlayer
2. **DFRobotDFPlayerMini Library**: Optional library for simplified communication

Example initialization in the Arduino sketch:

```cpp
#include "mp3_player.h"

void setup() {
  // Other initialization code...
  
  // Initialize the audio system (sets up UART and DFPlayer)
  mp3_player_init();
  
  // Set initial volume (0-30 range for DFPlayer)
  mp3_set_volume(20);  // Medium volume
}
```

## MicroSD Card Setup

The DFPlayer Mini requires files to be organized in a specific way:

1. Format the microSD card as FAT16 or FAT32
2. Create a folder named `mp3` at the root of the card
3. Place MP3 files in the folder with filenames matching their ID numbers:
   - `001.mp3` for SOUND_SLOTS_SPIN
   - `002.mp3` for SOUND_SLOTS_WIN
   - And so on...

## Usage in Game Logic

The audio system is used throughout the game code to provide feedback for player actions:

```c
// Example: Playing a sound when a button is clicked
void ui_event_spinBtn(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        // Play spinning sound effect
        mp3_play_sound(SOUND_SLOTS_SPIN);
        
        // Call game logic
        spinSlotBtn(e);
    }
}

// Example: Playing a win sound in game outcome
void updateMoneyAfterSpin(int column_index) {
    // Game logic to calculate winnings...
    
    if (is_win) {
        if (is_jackpot) {
            mp3_play_sound(SOUND_SLOTS_JACKPOT);
        } else {
            mp3_play_sound(SOUND_SLOTS_WIN);
        }
    }
}
```

## User Control

The application allows the user to enable or disable sound through a speaker button in the UI. This state is stored in the Store system:

```c
// Toggle audio on/off based on user preference
void spkButton(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        int current_state = get_spk_state();
        
        if (current_state == 1) {
            // Turn off audio
            set_spk_state(0);
            mp3_stop();
        } else {
            // Turn on audio
            set_spk_state(1);
            // Optionally restart background music
            mp3_play_music(MUSIC_MAIN_THEME);
        }
    }
}
```

## Communication Protocol

The DFPlayer uses a simple serial protocol:

1. **Command Format**: `0x7E 0xFF 0x06 [CMD] [FEEDBACK] [PARAM_MSB] [PARAM_LSB] 0xEF`
   - `CMD`: Command code (e.g., 0x01 for play, 0x0E for volume)
   - `FEEDBACK`: 0x00 for no feedback, 0x01 for feedback
   - `PARAM_MSB` and `PARAM_LSB`: 16-bit parameter value

2. **Common Commands**:
   - Play track: `0x03`
   - Set volume: `0x06`
   - Stop playback: `0x16`

## Troubleshooting

### Common Audio Issues

1. **No Sound Output**:
   - Check physical connections to the DFPlayer and speaker
   - Verify that the microSD card is properly inserted and formatted
   - Ensure file naming on the microSD card follows the required pattern
   - Check that volume is set to a non-zero value

2. **Intermittent Playback or Noise**:
   - Add a 1kΩ resistor in series with the TX line from ESP32 to DFPlayer
   - Ensure adequate power supply (DFPlayer can draw significant current during playback)
   - Isolate power supply for DFPlayer from sensitive digital components

3. **Command Failures**:
   - Implement a short delay (50-100ms) between consecutive commands
   - Check UART baud rate (DFPlayer typically uses 9600 baud)
   - Verify the checksum calculation if implementing the protocol manually

### Debugging

Serial debugging can be added to track communication with the DFPlayer:

```c
#define AUDIO_DEBUG 1  // Set to 1 to enable debug output

#if AUDIO_DEBUG
#define AUDIO_LOG(fmt, ...) Serial.printf("AUDIO: " fmt "\n", ##__VA_ARGS__)
#else
#define AUDIO_LOG(fmt, ...)
#endif
```

## Hardware Connection

Standard connections for the DFPlayer Mini:

```
ESP32           DFPlayer Mini
-------------------------------
GPIO X (TX) --- RX
GPIO Y (RX) --- TX (with 1kΩ resistor)
GND ----------- GND
3.3V/5V ------- VCC

DFPlayer Mini   Speaker
-------------------------------
SPK_1 --------- Speaker +
SPK_2 --------- Speaker -
```

## Customization

To modify or extend the audio system:

1. **Adding New Sounds**:
   - Add MP3 files to the microSD card with appropriate numbering
   - Define new sound IDs in the header file

2. **Changing Volume Levels**:
   - Adjust the volume range (DFPlayer supports 0-30)
   - Implement game-specific volume settings for different effects

3. **Advanced Features**:
   - Implement playback status feedback using the BUSY pin
   - Add equalizer settings using the DFPlayer EQ commands

---

*For more information on hardware connections and pin assignments, refer to the Deployment Guide.* 