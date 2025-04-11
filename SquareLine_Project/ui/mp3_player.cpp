// mp3_player.cpp
#include <Arduino.h>
#include <DFPlayerMini_Fast.h>
#include "mp3_player.h"

// Define pins for MP3 player communication
#define MP3_RX_PIN 45  // Connect to DFPlayer TX
#define MP3_TX_PIN 9   // Connect to DFPlayer RX

// These are defined in the .cpp file only
static DFPlayerMini_Fast myMP3;
static HardwareSerial MP3Serial(1); // Use UART1 (Hardware Serial 1)

// FreeRTOS task and queue handles
static TaskHandle_t mp3TaskHandle = NULL;
static QueueHandle_t mp3CommandQueue = NULL;

// Define command structure
typedef struct {
    enum {
        CMD_PLAY_TRACK,
        CMD_SET_VOLUME,
        CMD_PLAY_ADVERTISEMENT,
        CMD_STOP_ADVERTISEMENT,
        CMD_START_REPEAT,
        CMD_STOP_REPEAT
    } cmd;
    int param1;  // Track number or volume
    int param2;  // Delay (if needed)
} mp3_cmd_t;

// MP3 player task
static void mp3PlayerTask(void *pvParameters) {
    mp3_cmd_t cmd;
    
    for(;;) {
        if(xQueueReceive(mp3CommandQueue, &cmd, portMAX_DELAY) == pdTRUE) {
            switch(cmd.cmd) {
                case mp3_cmd_t::CMD_SET_VOLUME:
                    myMP3.volume(cmd.param1);
                    break;
                    
                case mp3_cmd_t::CMD_PLAY_TRACK:
                    if(cmd.param2 > 0) {
                        vTaskDelay(cmd.param2 / portTICK_PERIOD_MS);
                    }
                    myMP3.playFromMP3Folder(cmd.param1);
                    break;
                    
                case mp3_cmd_t::CMD_PLAY_ADVERTISEMENT:
                    if(cmd.param2 > 0) {
                        vTaskDelay(cmd.param2 / portTICK_PERIOD_MS);
                    }
                    myMP3.playAdvertisement(cmd.param1);
                    break;
                    
                case mp3_cmd_t::CMD_STOP_ADVERTISEMENT:
                    if(cmd.param2 > 0) {
                        vTaskDelay(cmd.param2 / portTICK_PERIOD_MS);
                    }
                    myMP3.stopAdvertisement();
                    break;
                    
                case mp3_cmd_t::CMD_START_REPEAT:
                    if(cmd.param2 > 0) {
                        vTaskDelay(cmd.param2 / portTICK_PERIOD_MS);
                    }
                    myMP3.startRepeat();
                    break;
                    
                case mp3_cmd_t::CMD_STOP_REPEAT:
                    if(cmd.param2 > 0) {
                        vTaskDelay(cmd.param2 / portTICK_PERIOD_MS);
                    }
                    myMP3.stopRepeat();
                    break;
            }
        }
    }
}

// Implementation
void mp3_set_volume(int volume) {
    mp3_cmd_t cmd = {mp3_cmd_t::CMD_SET_VOLUME, volume, 0};
    xQueueSend(mp3CommandQueue, &cmd, portMAX_DELAY);
}

void mp3_play_track(int track) {
    mp3_cmd_t cmd = {mp3_cmd_t::CMD_PLAY_TRACK, track, 50};
    xQueueSend(mp3CommandQueue, &cmd, portMAX_DELAY);
}

void mp3_init(void) {
    // Start Hardware Serial 1 with custom pins for the MP3 player
    MP3Serial.begin(9600, SERIAL_8N1, MP3_RX_PIN, MP3_TX_PIN);
    delay(1000);
    myMP3.begin(MP3Serial, true);
    
    // Create command queue
    mp3CommandQueue = xQueueCreate(10, sizeof(mp3_cmd_t));
    
    // Create MP3 player task
    xTaskCreate(
        mp3PlayerTask,     // Task function
        "MP3PlayerTask",   // Name
        4096,              // Stack size
        NULL,              // Parameters
        1,                 // Priority
        &mp3TaskHandle     // Task handle
    );

    delay(500);

    mp3_set_volume(20);

    delay(1000);

}


void mp3_play_track_with_delay(int track, int delay_ms) {
    mp3_cmd_t cmd = {mp3_cmd_t::CMD_PLAY_TRACK, track, delay_ms};
    xQueueSend(mp3CommandQueue, &cmd, portMAX_DELAY);
}

void mp3_play_advertisement(int track, int del) {
    mp3_cmd_t cmd = {mp3_cmd_t::CMD_PLAY_ADVERTISEMENT, track, del};
    xQueueSend(mp3CommandQueue, &cmd, portMAX_DELAY);
}

void mp3_play_advertisement_with_stop(int track, int del) {
    mp3_cmd_t cmd = {mp3_cmd_t::CMD_PLAY_ADVERTISEMENT, track, del};
    mp3_cmd_t cmd2 = {mp3_cmd_t::CMD_STOP_ADVERTISEMENT, 0, del};
    xQueueSend(mp3CommandQueue, &cmd2, portMAX_DELAY);
    xQueueSend(mp3CommandQueue, &cmd, portMAX_DELAY);
}

void mp3_stop_advertisement(void) {
    mp3_cmd_t cmd = {mp3_cmd_t::CMD_STOP_ADVERTISEMENT, 0, 0};
    xQueueSend(mp3CommandQueue, &cmd, portMAX_DELAY);
}

void mp3_start_repeat(void) {
    mp3_cmd_t cmd = {mp3_cmd_t::CMD_START_REPEAT, 0, 100};
    xQueueSend(mp3CommandQueue, &cmd, portMAX_DELAY);
}

void mp3_stop_repeat(void) {
    mp3_cmd_t cmd = {mp3_cmd_t::CMD_STOP_REPEAT, 0, 0};
    xQueueSend(mp3CommandQueue, &cmd, portMAX_DELAY);
}

void mp3_start_repeat_with_delay(int delay_ms) {
    mp3_cmd_t cmd = {mp3_cmd_t::CMD_START_REPEAT, 0, delay_ms};
    xQueueSend(mp3CommandQueue, &cmd, portMAX_DELAY);
}

void mp3_stop_repeat_with_delay(int delay_ms) {
    mp3_cmd_t cmd = {mp3_cmd_t::CMD_STOP_REPEAT, 0, delay_ms};
    xQueueSend(mp3CommandQueue, &cmd, portMAX_DELAY);
}