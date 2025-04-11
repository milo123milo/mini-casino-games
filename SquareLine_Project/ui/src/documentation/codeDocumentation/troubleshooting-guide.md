# Troubleshooting Guide

This document aims to help developers identify and resolve common issues that may arise while working with the Casino Games application.

## Common Issues and Solutions

### UI Issues

#### Buttons Not Responding to Clicks

**Symptoms:**
- Clicking a button does not trigger the expected action
- No visual feedback when pressing a button

**Possible Causes and Solutions:**

1. **Button State Issue:**
   - The button may be in a disabled state
   - **Solution:** Check if `LV_STATE_DISABLED` is set on the button object and clear it:
     ```c
     lv_obj_clear_state(ui_buttonObj, LV_STATE_DISABLED);
     ```

2. **Event Handler Not Connected:**
   - The button may not have an event handler assigned
   - **Solution:** Verify in `ui.c` that the button is properly connected to its event handler:
     ```c
     lv_obj_add_event_cb(ui_buttonObj, ui_event_buttonName, LV_EVENT_ALL, NULL);
     ```

3. **Hidden Objects:**
   - The button might be hidden or covered by another object
   - **Solution:** Check visibility flags:
     ```c
     lv_obj_clear_flag(ui_buttonObj, LV_OBJ_FLAG_HIDDEN);
     ```

4. **Z-Order Issues:**
   - Another object might be on top of the button
   - **Solution:** Bring the button to the front:
     ```c
     lv_obj_move_foreground(ui_buttonObj);
     ```

5. **Animation Interference:**
   - Animations may be in progress that block input
   - **Solution:** Add debug prints to check animation state or ensure buttons are re-enabled after animations complete

#### Screen Transitions Not Working

**Symptoms:**
- Screen doesn't change when expected
- Partial screen transition (content from both screens visible)

**Solutions:**
1. Verify that the correct screen loading function is called:
   ```c
   lv_scr_load_anim(ui_TargetScreen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
   ```
2. Check for errors in the screen's loading callback
3. Ensure animations are completed before attempting screen transitions

### Game Logic Issues

#### Blackjack Game Issues

**Symptoms:**
- Cards not appearing
- Score calculation incorrect
- Dealer behavior unexpected

**Solutions:**

1. **Cards Not Appearing:**
   - Check card object references in `blackJackLoaded` function
   - Verify animation calls for card objects
   - Add debug prints to track card initialization:
     ```c
     printf("Initializing cards: player_card_count=%d, dealer_card_count=%d\n", 
            player_card_count, dealer_card_count);
     ```

2. **Score Calculation Issues:**
   - Add debugging to the score calculation function:
     ```c
     printf("Card value: %d, Current score: %d, Aces: %d\n", 
            card_value, current_score, ace_count);
     ```
   - Verify card values are being correctly determined

3. **Dealer Behavior Issues:**
   - Debug dealer logic flow:
     ```c
     printf("Dealer turn: current score=%d, drawing=%s\n", 
            dealer_score, dealer_score < 17 ? "yes" : "no");
     ```
   - Check timer callbacks for dealer actions

#### Slots Game Issues

**Symptoms:**
- Reels not spinning or stopping correctly
- Incorrect win detection
- Animation glitches

**Solutions:**

1. **Reel Animation Issues:**
   - Verify animation parameters in slots animation functions
   - Check that icon objects exist and are correctly referenced

2. **Win Detection Problems:**
   - Add debugging to print slot results and win conditions:
     ```c
     printf("Slot results: %d %d %d, Win: %s\n", 
            slot1, slot2, slot3, is_win ? "YES" : "NO");
     ```

3. **Random Number Generation Issues:**
   - Debug random number generation to ensure proper distribution

### State Management Issues

#### Money Balance Problems

**Symptoms:**
- Money not updating after wins/losses
- Incorrect bet amounts
- Negative balances

**Solutions:**

1. Verify store operations in game result handlers:
   ```c
   printf("Before win: money=%d, bet=%d\n", get_money(), get_bet_amount());
   update_money(win_amount);
   printf("After win: money=%d\n", get_money());
   ```

2. Check for race conditions between UI updates and store updates

3. Add validation checks to prevent negative balances or invalid bets

#### Game State Persistence Issues

**Symptoms:**
- Game state resets unexpectedly
- Configuration not saved between sessions

**Solutions:**

1. Implement proper state saving mechanism if needed
2. Check initialization functions for proper handling of previous state

### Animation and Timing Issues

**Symptoms:**
- Animations overlapping or conflicting
- Game logic executing before animations complete
- UI elements appearing at wrong times

**Solutions:**

1. **Animation Coordination:**
   - Use timers to sequence animations properly
   - Add delays between animation calls

2. **Animation Debugging:**
   - Add print statements at the start and end of animations:
     ```c
     printf("Starting card pull animation for card %d\n", card_index);
     // Animation setup code...
     ```

3. **Timer Issues:**
   - Verify that timer callbacks are correctly registered
   - Check timer durations for appropriate values

## Debugging Techniques

### Adding Debug Output

Add debug output to key functions to track execution flow:

```c
#define DEBUG_ENABLED 1

#if DEBUG_ENABLED
#define DEBUG_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

// Usage
DEBUG_PRINT("Function %s called with value %d\n", __func__, value);
```

### Checking UI Object State

When UI interactions fail, check the state of the UI objects:

```c
void debug_ui_object(lv_obj_t *obj, const char *name) {
    if (obj == NULL) {
        printf("%s: NULL OBJECT\n", name);
        return;
    }
    
    printf("%s state: %s%s%s%s\n", name,
           lv_obj_has_state(obj, LV_STATE_DISABLED) ? "DISABLED " : "",
           lv_obj_has_flag(obj, LV_OBJ_FLAG_HIDDEN) ? "HIDDEN " : "",
           lv_obj_has_flag(obj, LV_OBJ_FLAG_CLICKABLE) ? "CLICKABLE " : "",
           lv_obj_get_style_opa(obj, LV_PART_MAIN | LV_STATE_DEFAULT) < 255 ? "TRANSPARENT " : "");
}
```

### Event Tracing

To debug event handling issues, add tracing to event handler functions:

```c
void ui_event_button(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    
    printf("Button event: %d (CLICKED=%d) on %p\n", 
           event_code, LV_EVENT_CLICKED, target);
           
    if(event_code == LV_EVENT_CLICKED) {
        buttonClicked(e);
    }
}
```

## Common Error Messages and Meanings

### "Object Not Found" Errors

```
Error: Object reference not set (NULL)
```

This typically means a UI element couldn't be found. Check:
1. The element name in `ui.h`
2. Whether the element is created before it's referenced
3. Typos in element names

### Animation Errors

```
Error: Animation target not set or null
```

Check:
1. The animation target object exists
2. The animation is correctly initialized

## Performance Issues

If the application is experiencing performance issues:

1. **Reduce Animation Complexity:**
   - Simplify animations or reduce the number of concurrent animations

2. **Optimize Event Handling:**
   - Avoid heavy processing in event handlers
   - Move complex calculations to background tasks if possible

3. **Monitor Memory Usage:**
   - Check for memory leaks, especially in game state management
   - Ensure objects are properly destroyed when no longer needed

## Reporting Issues

When reporting an issue to the development team, please include:

1. A clear description of the problem
2. Steps to reproduce the issue
3. Any error messages or logs
4. The state of the game when the issue occurred (e.g., which screen, game progress)
5. Any recent code changes that might be related

---

*This troubleshooting guide is a living document that will be updated as new issues and solutions are identified.* 