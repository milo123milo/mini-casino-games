# Blackjack Game Documentation

## Overview
Blackjack is a card comparison game where players attempt to beat the dealer by getting a hand value as close to 21 as possible without exceeding it. This implementation features animated cards, sound effects, and follows standard casino blackjack rules with some modifications.

## Game Interface
- **Bet Controls**: Use the '+' and '-' buttons to increase or decrease your bet amount (in increments of 100 coins).
- **Hit Button**: Draw an additional card to your hand.
- **Stand Button**: End your turn and let the dealer play their hand (only enabled after you have at least 2 cards).
- **Back Button**: Returns to the main menu (disabled during gameplay).
- **Coin Display**: Shows your current balance at the top of the screen.
- **Bet Display**: Shows your current bet amount.
- **Points Display**: Shows the current point value of your hand and the dealer's hand.

## Game Mechanics

### Card Values
- **Number Cards (2-10)**: Worth their face value (e.g., 2 of Hearts = 2 points)
- **Face Cards (Jack, Queen, King)**: Worth 10 points each
- **Aces**: Worth 11 points, unless that would cause the hand to exceed 21, in which case they're worth 1 point

### Game Setup
1. At the start of a new game, the dealer is dealt two face-down cards.
2. The player has no initial cards and must use the 'Hit' button to receive cards.
3. The player's cards are always dealt face-up.

### Player's Turn
1. Press the 'Hit' button to draw a card.
2. Continue drawing cards to try to reach a total as close to 21 as possible without exceeding it.
3. After you have at least 2 cards, the 'Stand' button is enabled.
4. Once you are satisfied with your hand, press 'Stand' to end your turn.
5. If your hand exceeds 21, you "bust" and lose immediately.
6. You can draw up to a maximum of 5 cards.

### Dealer's Turn
1. After you stand, the dealer reveals their face-down cards one by one.
2. The dealer must draw cards until their hand value is 17 or higher.
3. If the dealer's hand exceeds 21, they bust and you win.
4. The dealer will draw up to a maximum of 5 cards.

### Winning Conditions
- **Player wins if**:
  - Their final hand value is higher than the dealer's without exceeding 21
  - The dealer busts (exceeds 21)
  - The player gets a "blackjack" (21 points with their first 2 cards)
- **Dealer wins if**:
  - The player busts (exceeds 21)
  - The dealer's final hand value is higher than the player's without exceeding 21
- **Push (tie) if**:
  - Both the player and dealer have the same hand value

### Payout Structure
| Outcome | Payout Multiplier | Example (with 100 coin bet) | Description |
|---------|------------------|----------------------------|-------------|
| Blackjack (21 with first 2 cards) | 5x | +500 coins | Special highest payout |
| Regular win | 3x | +300 coins | Standard win payout |
| Push (tie) | 0x | 0 coins | Bet returned (no win/loss) |
| Loss | -1x | -100 coins | You lose your bet |

## Game Flow Restrictions
- At the start of the game, all buttons are disabled for 5 seconds to allow for initial animations.
- The 'Hit' button is enabled after the 5-second delay.
- The 'Stand' button remains disabled until you have at least 2 cards.
- The back button is disabled during active gameplay to prevent accidental navigation.
- After the game concludes, there's a brief delay before the game resets for the next round.

## Visual and Audio Effects
- **Card Animations**:
  - Pull animation: Cards slide onto the screen
  - Flip animation: Cards turn over to reveal their value
- **Win/Loss Notifications**: Special visual notifications appear when you win or lose
- **Sound Effects**:
  - Card dealing sounds
  - Win celebration sounds
  - Loss indication sounds

## Strategy Tips
- **Basic Strategy**: Stand on 17 or higher, hit on 16 or lower.
- **Understand the Odds**: The dealer has to hit on 16 or less, which can lead them to bust.
- **Card Counting**: Not effective in this game as the deck is reset each round.
- **Bet Management**: Adjust your bet based on your remaining balance and risk tolerance.

## Technical Details
The blackjack game uses a standard 52-card deck with cards randomly selected for each hand. The game implements standard blackjack rules with automatic standing at 5 cards and special payouts for blackjack.

---

*This documentation is intended for players of the Blackjack game in the Casino application built with SquareLine Studio and LVGL.* 