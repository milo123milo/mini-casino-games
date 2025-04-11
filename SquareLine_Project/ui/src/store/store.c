#include "store.h"

// Initialize the store with default values
Store store = { 
    .money = 0,
    .boot_flag = 0, 
    .bet_amount = 100,
    .spk_flag = 1,
    .slot_rounds_count = 1
};

// Set money safely within the limit
void set_money(int value) {
    if (value < 0) value = 0;
    if (value > 99999) value = 99999;
    store.money = value;
    printf("Money set: %d\n", store.money); // Corrected printf

}

// Get money value
int get_money(void) {
    printf("Current money: %d\n", store.money); // Corrected printf
    return store.money;

}

void set_boot_flag(int flag) {
    store.boot_flag = flag;
}
int get_boot_flag(){
    return store.boot_flag;
}

void set_bet_amount(int value) {
    if (value < 100) value = 100;
    if(value > store.money){
        value = store.money;
    }
    if (value > 99999) value = 99999;
    store.bet_amount = value;
    

}
int get_bet_amount(){
    return store.bet_amount;
}

int get_spk_state(){
    return store.spk_flag;
}

void set_spk_state(int state){
    store.spk_flag = state;
}

void set_slot_rounds_count(int count){
    store.slot_rounds_count = count;
}

int get_slot_rounds_count(){
    return store.slot_rounds_count;
}