# Casino Games Guide

This guide provides detailed instructions on how to play the casino games available in this application. Each game has its own rules, betting system, and payout structure.

## Table of Contents
- [General Information](#general-information)
  - [Coin System](#coin-system)
  - [Betting System](#betting-system)
- [Slots](#slots)
  - [How to Play](#how-to-play-slots)
  - [Winning Combinations](#winning-combinations)
  - [Payouts](#slots-payouts)
- [Dice Roll](#dice-roll)
  - [How to Play](#how-to-play-dice)
  - [Winning Combinations](#winning-combinations-dice)
  - [Payouts](#dice-payouts)
- [Blackjack](#blackjack)
  - [How to Play](#how-to-play-blackjack)
  - [Card Values](#card-values)
  - [Game Flow](#game-flow)
  - [Dealer Rules](#dealer-rules)
  - [Winning Conditions](#winning-conditions-blackjack)
  - [Payouts](#blackjack-payouts)

## General Information

### Coin System
The game uses a virtual coin system for all bets and winnings. Your current balance is displayed at the top of each game screen.

### Betting System
- Each game allows you to adjust your bet amount using the '+' and '-' buttons.
- The default betting increment is 100 coins.
- You cannot bet more than your current balance.
- Some games have special payout multipliers for certain winning combinations.

## Slots

### How to Play Slots
1. Set your bet amount using the '+' and '-' buttons.
2. Press the 'Spin' button to start the game.
3. Watch as the three reels spin and eventually stop.
4. If you get a winning combination, your winnings will be automatically added to your balance.

### Winning Combinations
The slot machine has the following symbols, listed from highest to lowest value:
- Seven (7) - Highest value
- Cherry
- Clover
- Heart
- Bar - Lowest value

A winning combination is formed when you get identical symbols on all three reels.

### Slots Payouts
| Combination | Multiplier | Payout Example (with 100 coin bet) |
|-------------|------------|-----------------------------------|
| Three Sevens | 10x | 1,000 coins |
| Three Cherries | 5x | 500 coins |
| Three Clovers | 3x | 300 coins |
| Three Hearts | 2x | 200 coins |
| Three Bars | 1x | 100 coins |
| Non-matching symbols | 0x | 0 coins (loss) |

When you win, special animations and sounds will play, with a special jackpot animation for the highest payout.

## Dice Roll

### How to Play Dice
1. Set your bet amount using the '+' and '-' buttons.
2. Press the 'Roll' button to roll the dice.
3. Two dice will be rolled, and the sum of the values will determine if you win or lose.
4. If you roll a winning combination, your winnings will be added to your balance.

### Winning Combinations Dice
The game is based on the sum of the two dice:
- Win: If you roll a 7 or 11
- Lose: If you roll a 2, 3, or 12 (Craps)
- No win/loss: Any other sum

### Dice Payouts
| Roll (Sum) | Result | Multiplier | Payout Example (with the bet of 100) |
|------------|--------|------------|--------------------------------------|
| 7 or 11 | Win | 5x | 500 coins |
| 2, 3, or 12 | Lose | -1x | -100 coins (you lose your bet) |
| Other numbers (4, 5, 6, 8, 9, 10) | No win/loss | 0x | 0 coins (bet returned) |

## Blackjack

### How to Play Blackjack
1. Set your bet amount using the '+' and '-' buttons.
2. The game starts with the dealer giving two face-down cards to themselves and no initial cards to the player.
3. Use the 'Hit' button to draw a card. The goal is to get as close to 21 as possible without exceeding it.
4. After you have at least 2 cards, you can use the 'Stand' button if you're satisfied with your hand, and the dealer will play their turn.
5. The dealer will then reveal their cards and draw additional cards according to fixed rules.
6. The hand closest to 21 without going over wins.

### Card Values
- Number cards (2-10): Face value
- Face cards (Jack, Queen, King): 10 points
- Aces: 11 points, or 1 point if counting as 11 would cause the hand to exceed 21

### Game Flow
1. Wait for the game to load and initial animations to complete (5 seconds).
2. The 'Hit' button becomes enabled after this period.
3. The 'Stand' button remains disabled until you have at least 2 cards.
4. You can draw up to 5 cards maximum.
5. If your hand exceeds 21, you bust automatically and lose your bet.
6. After you stand, the dealer reveals their cards and draws according to their rules.

### Dealer Rules
- The dealer must hit until their hand value is 17 or higher.
- The dealer must stand on a hand value of 17 or higher.
- The dealer will draw up to a maximum of 5 cards.

### Winning Conditions Blackjack
- You win if your final hand value is higher than the dealer's without exceeding 21.
- You win if the dealer busts (exceeds 21).
- You win with a blackjack (an Ace and a 10-value card as your first two cards).
- You lose if your hand exceeds 21 (bust).
- You lose if the dealer's final hand value is higher than yours without exceeding 21.
- It's a push (tie) if your hand value equals the dealer's.

### Blackjack Payouts
| Outcome | Payout Multiplier | Example (with 100 coin bet) |
|---------|------------------|----------------------------|
| Blackjack (21 with first 2 cards) | 5x | 500 coins |
| Regular win | 3x | 300 coins |
| Push (tie) | 0x | Bet returned (no win/loss) |
| Loss | -1x | -100 coins (you lose your bet) |

---

## Audio Controls

A speaker button is available that allows you to toggle game sounds on and off. Each game has its own background music and special sound effects for wins and losses.

## Navigation

Use the back button to return to the main menu from any game. Note that the back button is disabled during certain game actions to prevent accidental navigation:
- During the first 5 seconds when a game loads
- During active gameplay (e.g., when spinning slots, rolling dice, or during a blackjack hand)
- The back button is re-enabled after game actions complete

---

*This guide is intended for the casino games application developed using SquareLine Studio with LVGL.*
