/*	Author: Mark Vincent II
 *  Partner(s) Name: 
 *	Lab Section: A01
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description:
 *
 *  Two buttons are connect to pins A0 and A1. Output on PORTC is initially 7.
 *  Pressing A0 increments PORTC by 1, stopping at 9.
 *  Pressing A1 decrements PORTC by 1, stopping at 0.
 *  If both buttons are NOT pressed (0x00), PORTC resets to 0.
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
unsigned char tmpA = 0x00;
unsigned char tmpC = 0x00;

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
    DDRC = 0xFF; PORTC = 0x00; // Configure PORTC as output

    // init output
    tmpC = 0x07;

    // init state
    state = start; 
    
    // Loop
    while (1) {
        tick();
    }

    return 1;
}
