/*	Author: Trung Lam
 *  Partner(s) Name: 
 *	Lab Section: B22
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, init, poundKey, yKey, xKey} state;

void tick(){
	unsigned char input = PINA & 0x07;
	unsigned char lockButton = PINA & 0x80;

	switch(state){
		case start:
	       		state = init;
			break;
		case init:
			if(input == 0x01){
				state = xKey;
			}
			else if(input == 0x02){
				state = yKey;
			}
			else if(input == 0x04){
				state = poundKey;
			}
			else{
				state = init;
			}
			break;
		case xKey:
			if(input == 0x02){
                                state = yKey;
                        }
                        else if(input == 0x04){
                                state = poundKey;
                        }
			break;
		case yKey:
			break;
		case poundKey:
			break;
	}

	switch(state){
                case init:
                        break;
       		default:
			break;	
	}

	PORTB = PINA & 0x01;

	
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 1;
}
