/*	Author: Trung Lam
 *  Partner(s) Name: 
 *	Lab Section: B22
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, init, incrementPress, decrementPress, resetPress, resultRelease} state;

void tick(){
	unsigned char button = PINA & 0x03;
	unsigned char output = 0;
	
	switch(state){
		case start:
	       		state = init;
			break;
		case init:
			state = (button == 0x01) ? incrementPress: init;
			state = (button == 0x02) ? decrementPress: init;
			state = (button == 0x03) ? resetPress: init;
			break;
		case incrementPress:
			state = resultRelease;
			break;
		case decrementPress:
			state = resultRelease;
			break;
		case resetPress:
			state = (button == 0x01) ? incrementPress: resetPress;
                        state = (button == 0x02) ? decrementPress: resetPress;
			break;
		case resultRelease:
			state = (button == 0x01) ? incrementPress: resultRelease;
			state = (button == 0x02) ? decrementPress: resultRelease;
			state = (button == 0x03) ? resetPress: resultRelease;
			break;
		default:
			state = start;
			break;	
	}

	switch(state){
                case init:
			output = 7;
                        break;
                case incrementPress:
                        output += 1;
			break;
                case decrementPress:
			output -= 1;
                        break;
                case resetPress:
			output = 0;
			break;
		case resultRelease:
			break;
		default:
			break;
        
	}

	PORTC = output;

	
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x07;

    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 1;
}
