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
enum States{start, init, off, on} state;

// Global Vars
unsigned char tmpA = 0x00;
unsigned char tmpC = 0x00;

// enum flag
enum Flags{button1, button2, both, stillOn, none} flag;

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
            // Check where to go next
            if (tmpA == 0x00) {
                // goes to OFF, with flag set to none
                flag = none;
                state = off;

            } else if (tmpA == 0x01) {
                // goes to ON, with flag set to button1
                flag = button1;
                state = on;

            } else if (tmpA == 0x02) {
                // goes to ON, with flag set to button2
                flag = button2;
                state = on;

            } else if (tmpA == 0x03) {
                // goes to ON, with flag set to both.
                flag = both;
                state = on;
            }
            break;
        case off:
            // Check where to go next
            if (tmpA == 0x00) {
                // goes to OFF, with flag set to none
                flag = none;
                state = off;

            } else if (tmpA == 0x01) {
                // goes to ON, with flag set to button1
                flag = button1;
                state = on;

            } else if (tmpA == 0x02) {
                // goes to ON, with flag set to button2
                flag = button2;
                state = on;

            } else if (tmpA == 0x03) {
                // goes to ON, with flag set to both.
                flag = both;
                state = on;
            }
  
            break;
        case on:
            // Check where to go next
            if (tmpA == 0x00) {
                // goes to OFF, with flag set to none
                if (flag == stillOn) {
                    flag = none;
                    state = off;
                } else {
                    flag = none;
                    state = off;
                }

            } else if (tmpA == 0x01) {
                // goes to ON, with flag set to button1
                if (flag == stillOn) {
                    // nothing
                } else {
                    flag = button1;
                    state = on;
                }

            } else if (tmpA == 0x02) {
                // goes to ON, with flag set to button2
                if (flag == stillOn) {
                    // nothing
                } else {
                    flag = button2;
                    state = on;
                }

            } else if (tmpA == 0x03) {
                // goes to ON, with flag set to both.
                if (flag == stillOn) {
                    // nothing
                } else {
                    flag = both;
                    state = on;
                }
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
            // Sets output to 7 and writes.
            tmpC = 0x07;
            PORTC = tmpC;
            break;
        case off:
            // Decides whether to increment, decrement or nothing
            if (flag == none) {
                // Does nothing.
            } else {
                // shouldn't be able to get here.
            }
            break;
        case on:
            // Decides whether to increment, decrement or nothing
            if (flag == button1) {
                // Does a increment on PORTC by 1 if PORTC < 9.
                if (tmpC < 9) {
                    // Does increment
                    tmpC = tmpC + 1;
                    flag = stillOn;
                } else {
                    // Does nothing
                    flag = stillOn;
                }
            } else if (flag == button2) {
                // Does a decrement on PORTC by 1 if PORTC > 0.
                if (tmpC > 0) {
                    // Does decrement
                    tmpC = tmpC - 1;
                    flag = stillOn;
                } else {
                    // Does nothing
                    flag = stillOn;
                }
            } else if (flag == both) {
                // Resets tmpC to 0x00
                tmpC = 0x00;
                flag = stillOn;
            } else {
                // does nothing
            }
            // writes output
            PORTC = tmpC;
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
