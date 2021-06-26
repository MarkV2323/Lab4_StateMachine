/*	Author: Mark Vincent II
 *  Partner(s) Name: 
 *	Lab Section: A01
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description:
 *
 *  We have a button (A0) that determines which LED to turn on (B0 and B1) B1
 *  is initially OFF (0), while B0 is initially ON (1). Implement a SM.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

// States ie, {Start, Init, ... etc}
enum States{start, init, released, pressed} state;

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
            state = released;
            break;
        case released:
            // Checks what state to move to
            if (tmpA == 0x00) {
                state = released;
            } else if (tmpA == 0x01) {
                state = pressed;
            }

            // Changes LED on the transition
            if ((change == 0x00) && (state == pressed)) {
                change = 0x01;
                tmpB = 0x02;
            } else if ((change == 0x01) && (state == pressed)) {
                change = 0x00;
                tmpB = 0x01;
            }

            // write output
            PORTB = tmpB;
            break;
        case pressed:
            // Checks what state to move to
            if (tmpA == 0x01) {
                state = pressed;
            } else if (tmpA == 0x00) {
                state = released;
            }
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
            tmpB = 0x01; // init LED B0 to ON.
            change = 0x00; // init change to 0
            // write output
            PORTB = tmpB;
            break;
        case released:
            break;
        case pressed:
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
