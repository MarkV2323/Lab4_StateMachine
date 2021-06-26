/*	Author: Mark Vincent II
 *  Partner(s) Name: 
 *	Lab Section: A01
 *	Assignment: Lab #4  Exercise #
 *	Exercise Description:
 *
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

// States ie, {Start, Init, ... etc}
enum States{start, init} state;

// Global Vars
//DDRA = 0x00; PORTA = 0xFF; // Configure PORTA as input
//DDRB = 0xFF; PORTB = 0x00; // Configure PORTB as output

unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

unsigned char change = 0x00;

// tick function
void tick() {
    
    // READ INPUT
    tmpA = PINA & 0xFF;

    // Transitions
    switch(state) {
        case start:
            state = init;
            break;
        case init:
            break;
        default:
            state = start;
            break;
    }

    // Actions
    switch(state) {
        case start:
            break;
        case init:
            break;
        default:
            break;
    }

}

// Main Function
int main(void) {
    
    // PORTS
    DDRA = 0x00; PORTA = 0xFF; // Configure PORTA as input
    DDRB = 0xFF; PORTB = 0x00; // Configure PORTB as output

    // init output
    tmpB = 0x00;

    // init state
    state = start; 
    
    // Loop
    while (1) {
        tick();
    }

    return 1;
}
