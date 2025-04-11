#ifndef ICON_RANDOMIZER_H
#define ICON_RANDOMIZER_H

#include <stdlib.h>
#include "lvgl.h"  // Include LVGL library

#define TOTAL_OBJECTS 15
#define SELECTED_COUNT 3

void get_random_icons(lv_obj_t *selected_icons[SELECTED_COUNT]);

#endif // ICON_RANDOMIZER_H
