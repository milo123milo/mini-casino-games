#include "diceAnimation.h"
#include <stdlib.h>
#include <esp_system.h>
#include "../../ui.h"
#include "../../../mp3_player.h"

// Dice image objects
static lv_obj_t *dice1_images[6];
static lv_obj_t *dice2_images[6];

typedef void (*dice_roll_complete_callback)(int dice1, int dice2);

static dice_roll_complete_callback roll_complete_cb = NULL;

// Current dice values (1-6)
static int current_dice1 = 0;
static int current_dice2 = 0;



void init_dice_references(void) {
    // Initialize first dice references
    dice1_images[0] = ui_d11;
    dice1_images[1] = ui_d12;
    dice1_images[2] = ui_d13;
    dice1_images[3] = ui_d14;
    dice1_images[4] = ui_d15;
    dice1_images[5] = ui_d16;
    
    // Initialize second dice references
    dice2_images[0] = ui_d21;
    dice2_images[1] = ui_d22;
    dice2_images[2] = ui_d23;
    dice2_images[3] = ui_d24;
    dice2_images[4] = ui_d25;
    dice2_images[5] = ui_d26;
}

// Reset all dice to invisible
void reset_dice_visibility(void) {
    for (int i = 0; i < 6; i++) {
        lv_obj_set_style_opa(dice1_images[i], 0, LV_PART_MAIN);
        lv_obj_set_style_opa(dice2_images[i], 0, LV_PART_MAIN);
    }
}

// Animation complete callback
static void dice_roll_complete(void) {
    if (roll_complete_cb != NULL) {
        roll_complete_cb(current_dice1 + 1, current_dice2 + 1); // +1 because array is 0-based
    }
}

// Timer callback for when dice roll completes
static void dice_roll_timer_cb(lv_timer_t * timer) {
    dice_roll_complete();
    lv_timer_del(timer);
}

void roll_dice(void) {
    // Reset all dice visibility
    reset_dice_visibility();
    
    // Generate random dice values (0-5 for array index)
    current_dice1 = esp_random() % 6;
    current_dice2 = (esp_random() >> 8) % 6;
    
    // Apply your pre-created animation to the randomly selected dice
    diceAppear_Animation(dice1_images[current_dice1], 2000);
    diceAppear_Animation(dice2_images[current_dice2], 2000);
    
    // Create a timer to trigger the callback after animations are complete
    // Adding 2500ms to ensure both animations have completed
    lv_timer_t * timer = lv_timer_create(dice_roll_timer_cb, 2500, NULL);
    lv_timer_set_repeat_count(timer, 1);
}

void set_dice_roll_complete_callback(dice_roll_complete_callback callback) {
    roll_complete_cb = callback;
}

int process_dice_result(int dice1, int dice2) {
    // Empty function for future bet/win logic implementation
    int dicesum = dice1 + dice2;
    if(dicesum == 7 || dicesum == 11){
        return 5;
    } else if(dicesum == 2 || dicesum == 3 || dicesum == 12) {
        return 1;
    } else {
        return 0;
    }
} 