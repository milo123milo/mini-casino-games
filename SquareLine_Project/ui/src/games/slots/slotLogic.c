#include "slotLogic.h"
#include "../../ui.h"
#include <stdio.h>

int process_slot_result(lv_obj_t *selected_icons[SELECTED_COUNT]) {
    int result = 0;
    
    // Example logic: Assign a unique value based on selected icons
    printf("Selected Icons:\n");
    for (int i = 0; i < SELECTED_COUNT; i++) {
        printf("Icon %d: %p\n", i, (void *)selected_icons[i]);  
        // If you have a label or identifier, print it instead of the pointer.
    }
    
        if (selected_icons[0] == ui_sevenIcon && selected_icons[1] == ui_sevenIcon1 && selected_icons[2] == ui_sevenIcon2) {
            result = 10;
        } else if (selected_icons[0] == ui_cherryIcon && selected_icons[1] == ui_cherryIcon1 && selected_icons[2] == ui_cherryIcon2) {
            result = 5;
        } else if (selected_icons[0] == ui_cloverIcon && selected_icons[1] == ui_cloverIcon1 && selected_icons[2] == ui_cloverIcon2) {
            result = 3;
        } else if (selected_icons[0] == ui_heartIcon && selected_icons[1] == ui_heartIcon1 && selected_icons[2] == ui_heartIcon2) {
            result = 2;
        } else if (selected_icons[0] == ui_barIcon && selected_icons[1] == ui_barIcon1 && selected_icons[2] == ui_barIcon2) {
            result = 1;
        } 
    
    
    return result;
}