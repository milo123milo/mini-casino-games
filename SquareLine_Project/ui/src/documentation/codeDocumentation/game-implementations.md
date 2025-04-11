# Game Implementations

This document describes the technical implementation of the three casino games in the application: Slots, Dice Roll, and Blackjack.

## Common Structure

Each game follows a similar structure:

1. **Game Logic**: Core game mechanics implemented in C
2. **UI Integration**: Connection to the LVGL UI framework
3. **Event Handling**: Processing user interactions
4. **Animation**: Visual feedback for game events
5. **Audio**: Sound effects for various game states

## Slots Game

### Directory: `ui/src/games/slots/`

#### Key Files:
- `slotLogic.c/h`: Core logic for symbol matching and win detection
- `animLogic.c/h`: Animation logic for spinning reels
- `iconRandomizer.c/h`: Random selection of symbols for the reels

#### Key Functions:
- `process_slot_result()`: Determines the outcome of a spin and calculates winnings
- `get_random_icons()`: Generates random symbols for each reel
- `start_slot_animation()`: Initiates the spinning animation for a reel
- `stop_at_item()`: Stops a reel at a specified symbol

#### Event Flow:
1. User sets bet amount and presses the Spin button
2. `spinSlotBtn()` in `ui_events.c` is called
3. Random symbols are generated using `get_random_icons()`
4. Reel animations are started with `start_slot_animation()`
5. Animations are set to stop at the randomly selected symbols
6. When animations complete, `process_slot_result()` determines winnings
7. Player's balance is updated based on the outcome

## Dice Roll Game

### Directory: `ui/src/games/dices/`

#### Key Files:
- `diceAnimation.c/h`: Animation and logic for dice rolls

#### Key Functions:
- `init_dice_references()`: Initialize references to dice UI objects
- `roll_dice()`: Generates random values and animates the dice
- `process_dice_result()`: Determines the outcome based on dice values
- `set_dice_roll_complete_callback()`: Sets up callback for roll completion

#### Event Flow:
1. User sets bet amount and presses the Roll button
2. `rollDiceBtn()` in `ui_events.c` is called
3. `roll_dice()` is invoked to generate random dice values
4. Dice animations play to show the rolling effect
5. Once animation completes, `process_dice_result()` determines the outcome
6. Player's balance is updated based on the result

## Blackjack Game

### Directory: `ui/src/games/blackjack/`

#### Key Files:
- `blackjack.c/h`: Core blackjack game logic

#### Key Functions:
- `get_card_value()`: Returns the point value of a card
- `calculate_hand_value()`: Calculates the total value of a hand
- `get_player_hand_value()`: Gets the player's current hand value
- `get_dealer_hand_value()`: Gets the dealer's current hand value
- `set_card()`: Sets a card image and updates hand data
- `determine_blackjack_winner()`: Determines the game outcome
- `reset_deck()`: Resets the deck for a new game

#### Game State Variables:
- `player_cards[]`: Array of cards in player's hand
- `dealer_cards[]`: Array of cards in dealer's hand
- `player_card_count`: Number of cards in player's hand
- `dealer_card_count`: Number of cards in dealer's hand
- `current_player_card`: Index for adding new player cards
- `current_dealer_card`: Index for adding new dealer cards
- `dealer_turn_in_progress`: Flag indicating dealer's turn

#### Event Flow:
1. Game initializes with dealer having two face-down cards
2. Player uses Hit button to draw cards (`hitBtnClicked()` in `ui_events.c`)
3. Player's cards and score are updated
4. Stand button is enabled after player has at least 2 cards
5. When player presses Stand, `standBtnClicked()` is called
6. Dealer's cards are revealed and more are drawn if needed
7. `determine_blackjack_winner()` calculates the result
8. Player's balance is updated based on the outcome
9. Game resets for a new round

## Integration with UI Framework

Game logic is integrated with the UI framework in `ui_events.c`, which contains event handlers for user interactions. These event handlers call the appropriate game functions based on user actions.

For example:
- `spinSlotBtn()`: Handles the Spin button click in the Slots game
- `rollDiceBtn()`: Handles the Roll button click in the Dice Roll game
- `hitBtnClicked()` and `standBtnClicked()`: Handle the Hit and Stand buttons in Blackjack

## Store Integration

All games interact with the Store system through functions like:
- `get_bet_amount()`: Gets the current bet amount
- `update_money()`: Updates the player's balance based on game outcomes

---

*For detailed information about the UI components and animations, refer to the corresponding documentation.* 