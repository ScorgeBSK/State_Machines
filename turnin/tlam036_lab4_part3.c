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

enum States {start, init, poundKey, yKey, xKey, reLock} state;

void tick(){
	unsigned char input = PINA & 0x07;
	unsigned char lockButton = PINA & 0x80;
	unsigned char door = 1;

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
			state = init;
			break;
		case yKey:
			state = reLock;
			break;
		case poundKey:
			state = yKey;
			break;
		case reLock:
			state = init;
			break;
		default:
			state = start;
			break;
	}

	switch(state){
                case init:
			door = 0;
                        break;
		case xKey:
			door = 0;
			state = init;
			break;
		case yKey:
			if(door == 0x04){
				door = 1;
			}
			else{
				state = init;
			}
			break;
		case poundKey:
			door = 0x04;
			break;
		case reLock:
			if(lockButton && (door == 1) ){
				door = 0;
			}
			break;
       		default:
			break;	
	}

	PORTB = door;

	
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
