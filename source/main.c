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

enum States {start, init, incrementPress, decrementPress, resetPress, resultRelease} state;

void tick(){
	unsigned char button = PINA & 0x03;
	unsigned char output = 7;

	switch(state){
		case start:
	       		state = init;
			break;
		case init:
			if (button == 0x01){ 
			     	state = incrementPress;
			}
			else if(button == 0x02){
				state = decrementPress;
			}
			else if(button == 0x03){
				state = resetPress;
			}
			else{
				state = init;
			}
			break;
		case incrementPress:
			state = resultRelease;
			break;
		case decrementPress:
			state = resultRelease;
			break;
		case resetPress:
			if (button == 0x01){
                                state = incrementPress;
                        }
                        else if(button == 0x02){
                                state = decrementPress;
                        }
                        else{
                                state = resetPress;
                        }
                        break;
		case resultRelease:
			if (button == 0x01){ 
                                state = incrementPress;
                        }
                        else if(button == 0x02){
                                state = decrementPress;
                        }
			else if(button == 0x03){
				state = resetPress;
			}
                        else{
                                state = resultRelease;
                        }
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
                        output = output + 1;
			if(output > 9){
				output = 9;
			}
			break;
		case decrementPress:
			output = output - 1;
			if(output < 0){
				output = 0;
			}
			break;
		case resetPress:
			output = 0;
			break;
		case resultRelease:
			output = output;
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
