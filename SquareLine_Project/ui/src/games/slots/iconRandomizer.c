#include "iconRandomizer.h"
#include "../../ui.h"
#include "../../store/store.h"

int luck_round_number_flag = 0;
// Function to randomly pick 3 unique objects
void get_random_icons(lv_obj_t *selected_icons[SELECTED_COUNT]) {
    // Define groups by their ending number
    lv_obj_t *icon_groups[3][5] = {
        {ui_sevenIcon, ui_cherryIcon, ui_cloverIcon, ui_heartIcon, ui_barIcon},   // Group 0
        {ui_sevenIcon1, ui_cherryIcon1, ui_cloverIcon1, ui_heartIcon1, ui_barIcon1}, // Group 1
        {ui_sevenIcon2, ui_cherryIcon2, ui_cloverIcon2, ui_heartIcon2, ui_barIcon2}  // Group 2
    };

    // Select a random icon from each group
    for (int i = 0; i < SELECTED_COUNT; i++) {
        int random_index = rand() % 5;  // Pick a random icon from each group (0-4)
      
        selected_icons[i] = icon_groups[i][random_index];
    }

    if(get_slot_rounds_count() == 1 && luck_round_number_flag == 0){
        set_luck();
        luck_round_number_flag = 1;
    } else {
        set_slot_rounds_count(get_slot_rounds_count() - 1);
    }

    if(get_slot_rounds_count() == 0){
        set_slot_rounds_count(1);
        int rand_slot_win = rand() % 5;

        selected_icons[0] = icon_groups[0][rand_slot_win];
        selected_icons[1] = icon_groups[1][rand_slot_win];  
        selected_icons[2] = icon_groups[2][rand_slot_win];

        luck_round_number_flag = 0;
    }


}

void set_luck() {
    int luck_rounds = rand() % 8;
    if(luck_rounds == 0 || luck_rounds == 1){
        luck_rounds = 2;
    }
    set_slot_rounds_count(luck_rounds);
}