# UI System

The UI System forms the foundation of the casino games application, providing the graphical interface that users interact with. It is built using the Light and Versatile Graphics Library (LVGL) and SquareLine Studio.

## Overview

The UI System handles:
- Screen transitions and navigation
- User input through buttons, sliders, and other controls
- Display of game elements, text, and graphics
- Visual feedback and animations
- Layout and positioning of UI elements

## Directory Structure

The UI system files are primarily found in:
- `ui/src/`: Main UI implementation files
- `ui/src/ui/`: Auto-generated UI code from SquareLine Studio
- `ui/src/assets/`: Image and font resources

## Key Components

### Screens

The application consists of multiple screens representing different states:
- **Main Menu (Home)**: Entry point with game selection options
- **Slots Screen**: Interface for the Slots game
- **Dice Screen**: Interface for the Dice Roll game 
- **Blackjack Screen**: Interface for the Blackjack game
- **Settings Screen**: Configuration options for the application

### Key UI Files

#### Auto-generated Files

- `ui.c/h`: Contains UI element definitions and initialization functions
- `ui_comp.c/h`: Component definitions for reusable UI elements
- `ui_helpers.c/h`: Helper functions for common UI tasks
- `ui_img.c/h`: Image resource declarations and loading

#### Custom UI Event Files

- `ui_events.c/h`: Event handlers for user interactions with UI elements

## UI Element Hierarchy

UI elements are organized in a parent-child hierarchy:
1. **Screens**: Top-level containers (e.g., `ui_HomeScreen`)
2. **Panels**: Intermediate containers for logical grouping
3. **Controls**: Interactive elements like buttons, sliders, etc.
4. **Visual Elements**: Non-interactive elements like images and labels

## Screen Transitions

Screen changes are handled through the LVGL screen loading mechanism:
```c
lv_scr_load_anim(ui_SlotsScreen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
```

Each screen has associated loading and unloading event handlers:
- `[screenName]Loaded`: Called when a screen is loaded
- `[screenName]Unloaded`: Called when a screen is unloaded

## Event Handling

User interactions are captured through event callbacks defined in `ui_events.c`:

```c
void ui_event_hitBtn(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        hitBtnClicked(e);
    }
}
```

Common event types include:
- `LV_EVENT_CLICKED`: Button clicks
- `LV_EVENT_VALUE_CHANGED`: Slider or dropdown value changes
- `LV_EVENT_SCREEN_LOADED`: Screen load complete

## Game UI Integration

Each game has specialized UI elements:
- **Slots**: Reels, bet controls, win indicators
- **Dice**: Dice images, roll button, bet controls
- **Blackjack**: Card displays, hit/stand buttons, score indicators

## UI Creation Process

The UI is primarily created using SquareLine Studio, which generates C code. The workflow is:
1. Design UI visually in SquareLine Studio
2. Export to C code (`ui.c`, `ui_comp.c`, etc.)
3. Implement event handlers in `ui_events.c`
4. Add custom game logic that interacts with UI elements

## Dynamic UI Updates

The UI is updated at runtime through various methods:
- **Setting properties**: `lv_obj_set_style_bg_color(obj, color, LV_PART_MAIN | LV_STATE_DEFAULT);`
- **Changing text**: `lv_label_set_text(ui_scoreLabel, "Score: 21");`
- **Showing/hiding**: `lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);` or `lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);`
- **Enabling/disabling**: `lv_obj_add_state(obj, LV_STATE_DISABLED);` or `lv_obj_clear_state(obj, LV_STATE_DISABLED);`
- **Animation**: Using animation functions like `cardPullAnim_Animation(card_obj, delay);`

## UI States

UI elements can have different states:
- **Default**: Normal appearance
- **Pressed**: When being clicked
- **Disabled**: When interaction is not allowed
- **Checked**: For toggleable elements
- **Hidden**: When completely removed from view

## Responsive Design

The UI is designed for a specific target resolution, but elements use relative positioning where possible to accommodate minor variations in display size.

## Resource Management

UI assets (images, fonts) are managed through:
- **Images**: Defined in `ui_img.c` and loaded with `LV_IMG_DECLARE(image_name);`
- **Fonts**: Defined in custom font files and referenced in style settings

## Integration with Other Systems

The UI system integrates closely with:
- **Store System**: To display and update money and bet amounts
- **Animation System**: To provide visual feedback
- **Game Logic**: To reflect game state in the UI

---

*For more detailed information about UI interactions with specific games, refer to the Game Implementations documentation.* 