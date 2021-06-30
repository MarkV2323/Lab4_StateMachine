/*	Author: Mark Vincent II
 *  Partner(s) Name: 
 *	Lab Section: A01
 *	Assignment: Lab #4  Exercise #4
 *	Exercise Description:
 *
 *  The system
 *  has buttons on a keypad. Button 'X' connects to PA0, 'Y' to PA1, and '#' to PA2. Pressing
 *  and releasing '#', then pressing 'Y', should unlock the door by setting PB0 to 1. Any
 *  other sequence fails to unlock. Pressing a button from inside the house (PA7) locks the
 *  door (PB0=0). 
 *
 *  We need to allow functionatily for locking the door again with the same
 *  combo if it's already unlocked.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

// States ie, {Start, Init, ... etc}
enum States{start, init, inputWait, inputPoundPressed, inputPoundReleased} state;

// Global Vars
unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

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
            state = inputWait;
            break;
        case inputWait:
            // Checks if door is locked from inside
            if ( (tmpA & 0x80) == 0x80) {
                // locks door
                tmpB = 0x00;
                PORTB = tmpB;
            }
            // Checks if I.P.P can be transitioned to
            if ( (tmpA & 0x04) == 0x04) {
                // transition to I.P.P state cause pound has been pressed.
                state = inputPoundPressed;
            } else {
            // Otherwise we just stay in the inputWait state.
            state = inputWait;
            }
            break;
        case inputPoundPressed:
            // Checks if door is locked from inside
            if ( (tmpA & 0x80) == 0x80) {
                // locks door
                tmpB = 0x00;
                PORTB = tmpB;
            }
            // Checks if pound has been released
            if ( (tmpA & 0x0F) == 0x00) {
                // move to I.P.R state
                state = inputPoundReleased;
            } else if ( (tmpA & 0x04) == 0x04) {
                // stay in I.P.P state
                state = inputPoundPressed;
            } else {
            // Otherwise reset state back to inputWait
            state = inputWait;
            }
            break;
        case inputPoundReleased:
            // Checks if door is locked from inside
            if ( (tmpA & 0x80) == 0x80) {
                // locks door
                tmpB = 0x00;
                PORTB = tmpB;
            }
            // Checks if Y has been pressed
            if ( (tmpA & 0x02) == 0x02) {
                // if door was already unlocked, lock it with same combo
                if (tmpB == 0x01) {
                    // locks door
                    tmpB = 0x00;
                    PORTB = tmpB;
                    state = inputWait;
                } else {
                    // unlock door and reset state back to inputWait
                    tmpB = 0x01;
                    PORTB = tmpB;
                    state = inputWait;
                }
            } else if ( (tmpA & 0x0F) == 0x00) {
                // stay in I.P.R cause nothing has been pressed.
                state = inputPoundReleased;
            } else {
                // some other key was pressed, reset back to inputWait
                state = inputWait;
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
            tmpB = 0x00;
            // write inted output to PORTB.
            PORTB = tmpB;
            break;
        case inputWait:
            break;
        case inputPoundPressed:
            break;
        case inputPoundReleased:
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
