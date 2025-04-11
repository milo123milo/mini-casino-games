#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <lvgl.h>
#include <stdbool.h>
#include <string.h>

// Define result codes for the blackjack game
typedef enum {
    BLACKJACK_RESULT_PLAYER_WINS,    // Player wins
    BLACKJACK_RESULT_DEALER_WINS,    // Dealer wins
    BLACKJACK_RESULT_PUSH,           // Tie/Push
    BLACKJACK_RESULT_PLAYER_BLACKJACK // Player has blackjack (21 with 2 cards)
} BlackjackResult;

// Function to get the image reference for a specific card
const lv_image_dsc_t* get_card_image(const char* card_code);

// Function to set a card image to an image object
// If card_code is NULL, a random card will be chosen
// is_player: true for player card, false for dealer card
const char* set_card(lv_obj_t* card_obj, const char* card_code, bool is_player);

// Function to reset the deck (mark all cards as not taken)
void reset_deck();

// Function to get a random card from the deck that hasn't been dealt yet
const char* get_random_card();

// Function to start a new game (reset the deck and card arrays)
void start_new_blackjack_game();

// Function to get the player's hand value
int get_player_hand_value();

// Function to get the dealer's hand value
int get_dealer_hand_value();

/**
 * @brief Determines the winner of the Blackjack game
 * @return 1 if player wins, -1 if dealer wins, 0 if it's a push (tie)
 */
int determine_blackjack_winner();

// Function to get the number of cards in the player's hand
int get_player_card_count();

// Function to get the number of cards in the dealer's hand
int get_dealer_card_count();

// Function to reset player cards array
void reset_player_cards_arr();

// Function to reset dealer cards array
void reset_dealer_cards_arr();

// Function declarations will go here

#endif /* BLACKJACK_H */ 