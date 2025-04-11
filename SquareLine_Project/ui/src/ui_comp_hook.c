#include "ui.h"
#include <lvgl.h>
#include <stdio.h>
#include "store/store.h"

// Global money store
static int money_store = 0; // Starts at 0
static lv_obj_t *money_label = NULL; // Reference to label
static lv_obj_t *money_label_slots = NULL; // Reference to label


// Animation callback to update label
static void money_anim_cb(void * var, int32_t value)
{
    char buf[10];
    snprintf(buf, sizeof(buf), "%d", value);
    lv_label_set_text((lv_obj_t *)var, buf);
}

// Function to update money with animation
void update_money(int delta, uint16_t delay, bool anim, void * var)
{
    if ((lv_obj_t *)var == NULL) return; // Ensure label exists
    int old_amount = get_money();

    if(get_boot_flag() == 0) {
        delta = 1500;
        set_boot_flag(1);
    }
    if(delta == 0){
        delta = get_money();
        old_amount = 0;
    }

    int new_amount = old_amount + delta; // Calculate new money value

    set_money(new_amount);



    
    lv_anim_t a;
    if(anim == true){
    lv_anim_init(&a);
    

    lv_anim_set_var(&a, (lv_obj_t *)var);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)money_anim_cb);
    lv_anim_set_time(&a, 2500); // Animation duration: 4 seconds
    lv_anim_set_values(&a, old_amount, new_amount);
    lv_anim_set_playback_time(&a, 0); // No reverse playback
    lv_anim_set_repeat_count(&a, 1); // Play once
    lv_anim_set_path_cb(&a, lv_anim_path_linear);

    
    // ✅ Set delay before the animation starts
    lv_anim_set_delay(&a, delay);

  
    lv_anim_start(&a);
    }
 
    
}

void set_bet_value(lv_obj_t *comp, int value)
{
    if (comp == NULL) {
        printf("Error: Label component is NULL!\n");
        return;
    }
    int currentBet = get_bet_amount();
    int betAmount = currentBet + value;
    set_bet_amount(betAmount);
    char buf[10];  
    betAmount = get_bet_amount();
    sprintf(buf, "%d", betAmount);  // Convert int to string
    lv_label_set_text(comp, buf);  // Set text to the label
}




// Hook function for component
void ui_comp_coinAmontLabel_create_hook(lv_obj_t * comp)
{
    // Get the child component
    money_label = ui_comp_get_child(comp, UI_COMP_COINAMONTLABEL_COINAMONTLABEL);
    if (money_label == NULL) return;
    update_money(0, 2000, true, money_label);
}

void ui_comp_coinAmountLabelSlots_create_hook( lv_obj_t * comp)
{
    money_label_slots = ui_comp_get_child(comp, UI_COMP_COINAMOUNTLABELSLOTS_COINAMOUNTLABELSLOTS);
    if (money_label_slots == NULL) return;
    update_money(0, 1600, true, money_label_slots);

}

void ui_comp_betAmountSlots_create_hook( lv_obj_t * comp)
{
}
