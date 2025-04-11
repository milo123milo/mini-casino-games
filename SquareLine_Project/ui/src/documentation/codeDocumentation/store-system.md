# Store System

The Store System manages the in-game economy, including player's money balance, betting, and game state persistence.

## Overview

The Store module provides a central mechanism for tracking player funds and bet amounts across all games. It ensures that player actions, such as placing bets or receiving winnings, are properly reflected in their balance.

## Directory: `ui/src/store/`

### Key Files:
- `store.c`: Implementation of the store functionality
- `store.h`: Definitions and function declarations for the store system

## Data Structure

The main data structure is the `Store` struct, which contains:

```c
typedef struct {
    int money;           // Player's current balance
    int boot_flag;       // Flag indicating first boot/session
    int bet_amount;      // Current bet amount
    int spk_flag;        // Speaker/audio state
    int slot_rounds_count; // Counter for slot game rounds
} Store;
```

A global instance of this struct, `store`, is maintained to keep track of the game state.

## Key Functions

### Money Management:
- `set_money(int value)`: Sets the player's balance to a specific value
- `get_money(void)`: Retrieves the player's current balance
- `update_money(int amount, int duration, bool animate, lv_obj_t *label)`: Updates the player's balance, optionally with animation

### Betting System:
- `set_bet_amount(int value)`: Sets the current bet amount
- `get_bet_amount()`: Retrieves the current bet amount
- `set_bet_value(lv_obj_t *label, int change)`: Updates a bet amount label and adjusts the bet value

### State Management:
- `set_boot_flag(int flag)`: Sets the boot flag
- `get_boot_flag()`: Retrieves the boot flag
- `get_spk_state()`: Gets the speaker/audio state
- `set_spk_state(int state)`: Sets the speaker/audio state
- `set_slot_rounds_count(int count)`: Sets the counter for slot game rounds
- `get_slot_rounds_count()`: Gets the counter for slot game rounds

## Integration with Games

All games interact with the Store system to:
1. Check the player's current balance
2. Retrieve the current bet amount for wagers
3. Update the player's balance based on game outcomes

### Example Usage:

```c
// Getting the current bet amount for a game
uint16_t betAmount = get_bet_amount();

// Updating the player's balance after a win
update_money(betAmount * multiplier, 600, true, money_label);

// Adjusting bet amount using buttons
set_bet_value(bet_amount_label, 100);  // Increase bet by 100
set_bet_value(bet_amount_label, -100); // Decrease bet by 100
```

## UI Integration

The Store system is integrated with the UI through:

1. **Labels**: Money and bet amount labels are updated to reflect current values
2. **Animations**: Balance changes can be animated for visual feedback
3. **Button States**: Betting buttons are enabled/disabled based on the player's current balance

## Constraints

The Store system enforces several constraints:
1. Bet amounts cannot be negative
2. Bet amounts cannot exceed the player's current balance
3. When the player's balance is zero, certain game actions are disabled

## Persistence

While the current implementation does not include true persistence (values reset when the application restarts), the structure supports future implementation of persistent storage for player balances.

---

*For information about how the Store system interacts with specific games, refer to the Game Implementations documentation.* 