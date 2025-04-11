// mp3_player.h
#ifndef MP3_PLAYER_H
#define MP3_PLAYER_H

// C-compatible function declarations
#ifdef __cplusplus
extern "C" {
#endif

void mp3_init(void);
void mp3_set_volume(int volume);
void mp3_play_track(int track);
void mp3_play_track_with_delay(int track, int delay_ms);
void mp3_play_advertisement(int track, int delay_ms);
void mp3_play_advertisement_with_stop(int track, int delay_ms);
void mp3_stop_advertisement(void);
void mp3_start_repeat(void);
void mp3_stop_repeat(void);
void mp3_start_repeat_with_delay(int delay_ms);
void mp3_stop_repeat_with_delay(int delay_ms);

#ifdef __cplusplus
}
#endif

#endif // MP3_PLAYER_H