#include "blackjack.h"
#include "../../ui.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "esp_random.h" // Include ESP32 random number generator

// Define a structure to represent a card in the deck
typedef struct {
    char code[4];  // Card code (e.g., "C2", "HK", etc.)
    bool taken;    // Whether the card has been dealt
} Card;

// Create a standard 52-card deck
static Card deck[52] = {
    // Clubs
    {"C2", false}, {"C3", false}, {"C4", false}, {"C5", false}, {"C6", false},
    {"C7", false}, {"C8", false}, {"C9", false}, {"C10", false}, {"CJ", false},
    {"CQ", false}, {"CK", false}, {"CA", false},
    
    // Diamonds
    {"D2", false}, {"D3", false}, {"D4", false}, {"D5", false}, {"D6", false},
    {"D7", false}, {"D8", false}, {"D9", false}, {"D10", false}, {"DJ", false},
    {"DQ", false}, {"DK", false}, {"DA", false},
    
    // Hearts
    {"H2", false}, {"H3", false}, {"H4", false}, {"H5", false}, {"H6", false},
    {"H7", false}, {"H8", false}, {"H9", false}, {"H10", false}, {"HJ", false},
    {"HQ", false}, {"HK", false}, {"HA", false},
    
    // Spades
    {"S2", false}, {"S3", false}, {"S4", false}, {"S5", false}, {"S6", false},
    {"S7", false}, {"S8", false}, {"S9", false}, {"S10", false}, {"SJ", false},
    {"SQ", false}, {"SK", false}, {"SA", false}
};

// Arrays to track player and dealer cards
#define MAX_CARDS 10
static char player_cards[MAX_CARDS][4];
static int player_card_count = 0;
static char dealer_cards[MAX_CARDS][4];
static int dealer_card_count = 0;

// Function to reset the deck (mark all cards as not taken)
void reset_deck() {
    for (int i = 0; i < 52; i++) {
        deck[i].taken = false;
    }
    
    // Reset player and dealer card arrays
    player_card_count = 0;
    dealer_card_count = 0;
}

// Function to reset player cards array
void reset_player_cards_arr() {
    printf("Resetting player cards array\n");
    // Reset the player card counter
    player_card_count = 0;
    // Clear the array (optional but thorough)
    for (int i = 0; i < MAX_CARDS; i++) {
        memset(player_cards[i], 0, sizeof(player_cards[i]));
    }
}

// Function to reset dealer cards array
void reset_dealer_cards_arr() {
    printf("Resetting dealer cards array\n");
    // Reset the dealer card counter
    dealer_card_count = 0;
    // Clear the array (optional but thorough)
    for (int i = 0; i < MAX_CARDS; i++) {
        memset(dealer_cards[i], 0, sizeof(dealer_cards[i]));
    }
}

// Function to get a random card from the deck that hasn't been dealt yet
const char* get_random_card() {
    // Count how many cards are still available
    int available_cards = 0;
    for (int i = 0; i < 52; i++) {
        if (!deck[i].taken) {
            available_cards++;
        }
    }
    
    // If no cards are available, reset the deck
    if (available_cards == 0) {
        reset_deck();
        available_cards = 52;
    }
    
    // Choose a random available card using ESP32's hardware RNG
    uint32_t random_value = esp_random(); // Get a true random 32-bit value
    int target_card = random_value % available_cards;
    int current_card = 0;
    
    for (int i = 0; i < 52; i++) {
        if (!deck[i].taken) {
            if (current_card == target_card) {
                // Mark this card as taken
                deck[i].taken = true;
                return deck[i].code;
            }
            current_card++;
        }
    }
    
    // This should never happen if the code is correct
    return "BACK";
}

// Function to get the image reference for a specific card
const lv_image_dsc_t* get_card_image(const char* card_code) {
    // Club cards
    if (strcmp(card_code, "C2") == 0) return &ui_img_1853341697;   // C-2.png
    if (strcmp(card_code, "C3") == 0) return &ui_img_417965468;    // C-3.png
    if (strcmp(card_code, "C4") == 0) return &ui_img_2119927969;   // C-4.png
    if (strcmp(card_code, "C5") == 0) return &ui_img_1038198790;   // C-5.png
    if (strcmp(card_code, "C6") == 0) return &ui_img_43530389;     // C-6.png
    if (strcmp(card_code, "C7") == 0) return &ui_img_1391845840;   // C-7.png
    if (strcmp(card_code, "C8") == 0) return &ui_img_1077688739;   // C-8.png
    if (strcmp(card_code, "C9") == 0) return &ui_img_2135549378;   // C-9.png
    if (strcmp(card_code, "C10") == 0) return &ui_img_2057722816;  // C-10.png
    if (strcmp(card_code, "CA") == 0) return &ui_img_2057723841;   // C-11.png (Ace)
    if (strcmp(card_code, "CJ") == 0) return &ui_img_2057729214;   // C-12.png (Jack)
    if (strcmp(card_code, "CQ") == 0) return &ui_img_2057730239;   // C-13.png (Queen)
    if (strcmp(card_code, "CK") == 0) return &ui_img_2057727164;   // C-14.png (King)
    
    // Diamond cards
    if (strcmp(card_code, "D2") == 0) return &ui_img_1293794150;   // D-2.png
    if (strcmp(card_code, "D3") == 0) return &ui_img_1919443967;   // D-3.png
    if (strcmp(card_code, "D4") == 0) return &ui_img_162370108;    // D-4.png
    if (strcmp(card_code, "D5") == 0) return &ui_img_919359071;    // D-5.png
    if (strcmp(card_code, "D6") == 0) return &ui_img_516017158;    // D-6.png
    if (strcmp(card_code, "D7") == 0) return &ui_img_565712021;    // D-7.png
    if (strcmp(card_code, "D8") == 0) return &ui_img_259635800;    // D-8.png
    if (strcmp(card_code, "D9") == 0) return &ui_img_1341364979;   // D-9.png
    if (strcmp(card_code, "D10") == 0) return &ui_img_68789583;    // D-10.png
    if (strcmp(card_code, "DA") == 0) return &ui_img_68790608;     // D-11.png (Ace)
    if (strcmp(card_code, "DJ") == 0) return &ui_img_68795981;     // D-12.png (Jack)
    if (strcmp(card_code, "DQ") == 0) return &ui_img_68797006;     // D-13.png (Queen)
    if (strcmp(card_code, "DK") == 0) return &ui_img_68793931;     // D-14.png (King)
    
    // Heart cards
    if (strcmp(card_code, "H2") == 0) return &ui_img_1661094818;   // H-2.png
    if (strcmp(card_code, "H3") == 0) return &ui_img_1552143299;   // H-3.png
    if (strcmp(card_code, "H4") == 0) return &ui_img_470414120;    // H-4.png
    if (strcmp(card_code, "H5") == 0) return &ui_img_611315059;    // H-5.png
    if (strcmp(card_code, "H6") == 0) return &ui_img_824061170;    // H-6.png
    if (strcmp(card_code, "H7") == 0) return &ui_img_257668009;    // H-7.png
    if (strcmp(card_code, "H8") == 0) return &ui_img_892420028;    // H-8.png
    if (strcmp(card_code, "H9") == 0) return &ui_img_189309151;    // H-9.png
    if (strcmp(card_code, "H10") == 0) return &ui_img_693209757;   // H-10.png
    if (strcmp(card_code, "HA") == 0) return &ui_img_693208732;    // H-11.png (Ace)
    if (strcmp(card_code, "HJ") == 0) return &ui_img_693203359;    // H-12.png (Jack)
    if (strcmp(card_code, "HQ") == 0) return &ui_img_693202334;    // H-13.png (Queen)
    if (strcmp(card_code, "HK") == 0) return &ui_img_693205409;    // H-14.png (King)
    
    // Spade cards
    if (strcmp(card_code, "S2") == 0) return &ui_img_1775697841;   // S-2.png
    if (strcmp(card_code, "S3") == 0) return &ui_img_340321612;    // S-3.png
    if (strcmp(card_code, "S4") == 0) return &ui_img_2097395471;   // S-4.png
    if (strcmp(card_code, "S5") == 0) return &ui_img_1115842646;   // S-5.png
    if (strcmp(card_code, "S6") == 0) return &ui_img_34113467;     // S-6.png
    if (strcmp(card_code, "S7") == 0) return &ui_img_1469489696;   // S-7.png
    if (strcmp(card_code, "S8") == 0) return &ui_img_1000044883;   // S-8.png
    if (strcmp(card_code, "S9") == 0) return &ui_img_2081774062;   // S-9.png
    if (strcmp(card_code, "S10") == 0) return &ui_img_1913133936;  // S-10.png
    if (strcmp(card_code, "SA") == 0) return &ui_img_1913134961;   // S-11.png (Ace)
    if (strcmp(card_code, "SJ") == 0) return &ui_img_1913140334;   // S-12.png (Jack)
    if (strcmp(card_code, "SQ") == 0) return &ui_img_1913141359;   // S-13.png (Queen)
    if (strcmp(card_code, "SK") == 0) return &ui_img_1913138284;   // S-14.png (King)
    
    // Card back
    if (strcmp(card_code, "BACK") == 0) return &ui_img_backcard_png; // backcard.png
    
    // Default to card back if not found
    return &ui_img_backcard_png;
}

// Function to get the value of a card
int get_card_value(const char* card_code) {
    // Get the second character (or third for "10")
    char value = card_code[1];
    
    // Handle 10 as a special case
    if (card_code[1] == '1' && card_code[2] == '0') {
        return 10;
    }
    
    // Handle face cards (J, Q, K)
    if (value == 'J' || value == 'Q' || value == 'K') {
        return 10;
    }
    
    // Handle Ace
    if (value == 'A') {
        return 11; // Ace is initially 11, but can be 1 if needed
    }
    
    // For number cards, convert to integer
    return value - '0';
}

// Function to calculate the hand value, handling Aces optimally
int calculate_hand_value(const char cards[][4], int card_count) {
    int total = 0;
    int ace_count = 0;
    
    // First pass: count all cards, treating Aces as 11
    for (int i = 0; i < card_count; i++) {
        int card_value = get_card_value(cards[i]);
        total += card_value;
        
        // Count Aces
        if (cards[i][1] == 'A') {
            ace_count++;
        }
    }
    
    // Second pass: convert Aces from 11 to 1 as needed to avoid busting
    while (total > 21 && ace_count > 0) {
        total -= 10; // Convert one Ace from 11 to 1
        ace_count--;
    }
    
    return total;
}

// Function to get the player's hand value
int get_player_hand_value() {
    return calculate_hand_value(player_cards, player_card_count);
}

// Function to get the dealer's hand value
int get_dealer_hand_value() {
    return calculate_hand_value(dealer_cards, dealer_card_count);
}

// Function to set a card image to an image object
// If card_code is NULL, a random card will be chosen
// is_player: true for player card, false for dealer card
const char* set_card(lv_obj_t* card_obj, const char* card_code, bool is_player) {
    const char* used_card;

    if (card_code == NULL) {
        // Get a random card that hasn't been dealt yet
        used_card = get_random_card();
        printf("Random card: %s\n", used_card);
    } else {
        // Use the specified card
        used_card = card_code;
    }
    
    // Set the card image
    lv_image_set_src(card_obj, get_card_image(used_card));
    
    // Store the card in the appropriate array
    if (is_player && player_card_count < MAX_CARDS) {
        strcpy(player_cards[player_card_count], used_card);
        player_card_count++;
    } else if (!is_player && dealer_card_count < MAX_CARDS) {
        strcpy(dealer_cards[dealer_card_count], used_card);
        dealer_card_count++;
    }
    
    return used_card;
}

// Function to start a new game (reset the deck)
void start_new_blackjack_game() {
    reset_deck();
}

// Function to determine the winner of the blackjack game
int determine_blackjack_winner() {
    int player_value = get_player_hand_value();
    int dealer_value = get_dealer_hand_value();
    
    // Check if player busted (over 21)
    if (player_value > 21) {
        printf("Player busted with %d. Dealer wins!\n", player_value);
        return -1; // Dealer wins
    }
    
    // Check if dealer busted (over 21)
    if (dealer_value > 21) {
        printf("Dealer busted with %d. Player wins!\n", dealer_value);
        return 1; // Player wins
    }
    
    // Check for player blackjack (21 with exactly 2 cards)
    if (player_value == 21 && player_card_count == 2) {
        // If dealer also has blackjack, it's a push
        if (dealer_value == 21 && dealer_card_count == 2) {
            printf("Both have blackjack! Push.\n");
            return 0; // Push
        }
        printf("Player has blackjack! Player wins with 3:2 payout.\n");
        return 1; // Player wins
    }
    
    // Compare values
    if (player_value > dealer_value) {
        printf("Player wins with %d vs dealer's %d!\n", player_value, dealer_value);
        return 1; // Player wins
    } else if (dealer_value > player_value) {
        printf("Dealer wins with %d vs player's %d!\n", dealer_value, player_value);
        return -1; // Dealer wins
    } else {
        printf("Push! Both have %d.\n", player_value);
        return 0; // Push (tie)
    }
}

// Function to get the number of cards in the player's hand
int get_player_card_count() {
    return player_card_count;
}

// Function to get the number of cards in the dealer's hand
int get_dealer_card_count() {
    return dealer_card_count;
}

// Implementation will go here 