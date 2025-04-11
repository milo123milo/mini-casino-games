# Slots Game Documentation

## Overview
The slots game simulates a classic 3-reel slot machine with various symbols and corresponding payouts. It features animations, sound effects, and a betting system.

## Game Interface
- **Bet Controls**: Use the '+' and '-' buttons to increase or decrease your bet amount (in increments of 100 coins).
- **Spin Button**: Starts the game by spinning the reels.
- **Back Button**: Returns to the main menu (disabled during spins).
- **Coin Display**: Shows your current balance at the top of the screen.
- **Bet Display**: Shows your current bet amount.

## Game Mechanics

### How Reels Work
1. The game contains three reels, each with various symbols.
2. When you press "Spin", the reels start spinning quickly.
3. The reels stop one by one (left to right) at predetermined intervals.
4. The outcome is determined by a random number generator that selects the symbols that will appear.

### Winning Combinations and Payouts
The slots game offers different payout multipliers based on the combination of symbols:

| Symbol Combination | Multiplier | Payout (with 100 coin bet) | Description |
|-------------------|------------|----------------------------|-------------|
| Three Sevens | 10x | 1,000 coins | Jackpot - highest payout with special animation |
| Three Cherries | 5x | 500 coins | High value |
| Three Clovers | 3x | 300 coins | Medium-high value |
| Three Hearts | 2x | 200 coins | Medium value |
| Three Bars | 1x | 100 coins | Low value - returns your bet |
| Non-matching symbols | 0x | 0 coins | Loss - you lose your bet |

### Visual and Audio Effects
- **Reel Spinning Animation**: Symbols scroll rapidly during the spin.
- **Stopping Animation**: Each reel stops with a slight bouncing effect.
- **Win Animation**: Special visual effects play when you win, with more elaborate animations for bigger wins.
- **Jackpot Animation**: A special celebration animation plays when you hit three Sevens.
- **Sound Effects**: Different sounds play for:
  - Starting a spin
  - Reels stopping
  - Winning combinations
  - Jackpot celebration

## Betting Strategy
- **Conservative**: Place small bets (100 coins) to extend gameplay time.
- **Medium Risk**: Place moderate bets (300-500 coins) for balanced risk/reward.
- **High Risk**: Place large bets (1000+ coins) for potentially big payouts.

## Game Flow Restrictions
- The back button is disabled during active spins to prevent accidental navigation.
- The spin button is disabled during active spins to prevent multiple spins at once.
- If your balance is less than your current bet, the bet will automatically adjust to match your balance.
- If your balance reaches zero, you'll need to restart the game to continue playing.

## Technical Details
The slot machine uses a random number generator to determine outcomes, ensuring fair results for each spin. The symbols are selected randomly for each reel, and the combinations are checked against the paytable to determine winnings.

---

*This documentation is intended for players of the Slots game in the Casino application built with SquareLine Studio and LVGL.* 