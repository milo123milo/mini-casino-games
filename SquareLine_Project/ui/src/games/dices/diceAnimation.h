#ifndef DICE_ANIMATION_H
#define DICE_ANIMATION_H

#include <lvgl.h>

// Initialize dice references
void init_dice_references(void);

// Roll dice function
void roll_dice(void);

// Set callback for when dice roll completes
typedef void (*dice_roll_complete_callback)(int dice1, int dice2);
void set_dice_roll_complete_callback(dice_roll_complete_callback callback);

// Process dice result
int process_dice_result(int dice1, int dice2);
void reset_dice_visibility(void);

#endif // DICE_ANIMATION_H 