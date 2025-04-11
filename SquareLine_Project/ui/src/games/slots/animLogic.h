#ifndef ANIMLOGIC_H
#define ANIMLOGIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../ui.h"

// Constants
#define ITEM_SIZE 60        // Height of each item
#define VISIBLE_ITEMS 3     // How many fit in parent's height
#define TOTAL_ITEMS 5       // Total items in parent
#define SCROLL_SPEED 200    // Speed in ms to move one ITEM_SIZE

// Structure for storing animation stop data
typedef struct {
    lv_obj_t *parent;
    lv_obj_t *target_item;
} slot_stop_data_t;

// New: Callback type definition for slot stop event
typedef void (*slot_stop_event_cb_t)(int column_index);

// Function declarations
void start_slot_animation(lv_obj_t *parent);
void stop_at_item(lv_obj_t *item_name, uint32_t delay);

// New: Function to set the slot stop event callback
void set_slot_stop_event_callback(slot_stop_event_cb_t callback);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*ANIMLOGIC_H*/