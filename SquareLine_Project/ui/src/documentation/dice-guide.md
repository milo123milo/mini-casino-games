# Dice Roll Game Documentation

## Overview
The Dice Roll game simulates a classic casino dice game where players bet on the outcome of rolling two dice. The game features animated dice rolls, sound effects, and a straightforward betting system.

## Game Interface
- **Bet Controls**: Use the '+' and '-' buttons to increase or decrease your bet amount (in increments of 100 coins).
- **Roll Button**: Starts the game by rolling the dice.
- **Back Button**: Returns to the main menu (disabled during dice rolls).
- **Coin Display**: Shows your current balance at the top of the screen.
- **Bet Display**: Shows your current bet amount.

## Game Mechanics

### How Dice Rolling Works
1. When you press the "Roll" button, two animated dice appear on the screen.
2. The dice roll with a realistic 3D animation.
3. After a brief animation, the dice settle to reveal their final values.
4. The sum of the two dice determines whether you win or lose.

### Winning Rules and Payouts
The outcome is based on the sum of the two dice:

| Roll (Sum) | Result | Multiplier | Outcome (with 100 coin bet) | Description |
|------------|--------|------------|----------------------------|-------------|
| 7 or 11 | Win | 5x | +500 coins | Natural win - highest payout |
| 2, 3, or 12 | Lose | -1x | -100 coins | Craps - you lose your bet |
| 4, 5, 6, 8, 9, 10 | No win/loss | 0x | 0 coins (bet returned) | Push - your bet is returned |

### Visual and Audio Effects
- **Roll Animation**: The dice tumble and spin in a realistic 3D animation.
- **Dice Appearance**: 3D-rendered dice with clearly visible pips (dots).
- **Win Animation**: Special visual effects play when you win.
- **Sound Effects**:
  - Dice rolling sounds
  - Win celebration sounds
  - Loss indication sounds

## Strategy Notes
- **Playing it Safe**: Since 7 is the most common roll in dice (6 different combinations out of 36 possible outcomes), and 11 has 2 combinations, your probability of winning is 8/36 or about 22%.
- **Understanding the Odds**:
  - 7 can be rolled as: 1+6, 2+5, 3+4, 4+3, 5+2, 6+1
  - 11 can be rolled as: 5+6, 6+5
  - Craps (2, 3, 12) probabilities: 2 (1+1), 3 (1+2, 2+1), 12 (6+6)

## Game Flow Restrictions
- The back button is disabled during active dice rolls to prevent accidental navigation.
- The roll button is disabled during the dice animation to prevent multiple rolls at once.
- After a roll completes, there's a brief delay before the roll button is re-enabled.
- Longer celebration and animation times apply for wins compared to other outcomes.

## Technical Details
The dice roll game uses a random number generator to determine the outcome of each die, ensuring fair results for each roll. The values are generated using ESP32's hardware random number generator for true randomness.

---

*This documentation is intended for players of the Dice Roll game in the Casino application built with SquareLine Studio and LVGL.* 