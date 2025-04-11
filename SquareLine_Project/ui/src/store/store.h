#ifndef STORE_H
#define STORE_H

#include <stdint.h>
#include <stdio.h>


typedef struct {
    int money;
    int boot_flag; 
    int bet_amount;
    int spk_flag;
    int slot_rounds_count;
} Store;

// Global instance of Store
extern Store store;

// Functions to modify store values safely
void set_money(int value);
int get_money(void);
void set_boot_flag(int flag);
int get_boot_flag();
void set_bet_amount(int value);
int get_bet_amount();
int get_spk_state();
void set_spk_state(int state);
void set_slot_rounds_count(int count);
int get_slot_rounds_count();

#endif // STORE_H
