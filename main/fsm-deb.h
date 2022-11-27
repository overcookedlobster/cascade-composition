#ifndef FSM_H
#define FSM_H
#include <stdlib.h>
#define STALL 0
#define COUNT 1
#define SHIFT 2
#define WAIT 3
void fsm_deb(int button, int *state, int *flag, int *state_led){
	switch(*state){
		case STALL:
			if(button) *state = COUNT;
			break;	
		case COUNT:
			if(!button) *state = STALL;
			else if(button && (*flag)) *state = SHIFT;
			break;
		case SHIFT:
			*state_led = (4 + *state_led + button) % 4;
			*state = WAIT;
			*flag = 0;
			break;
		case WAIT:
			if(!button) *state = STALL; 
			break;
	}	

}

void fsm_led(int *state, int *led){
	switch(*state){
		case 0: 
			*(led) = 1;
			*(led+1) = 0;
			*(led+2) = 0;
			*(led+3) = 0;
			break;
		case 1: 
			*(led) = 0;
			*(led+1) = 1;
			*(led+2) = 0;
			*(led+3) = 0;
			break;
		case 2: 
			*(led) = 0;
			*(led+1) = 0;
			*(led+2) = 1;
			*(led+3) = 0;
			break;
		case 3: 
			*(led) = 0;
			*(led+1) = 0;
			*(led+2) = 0;
			*(led+3) = 1;
			break;

}
		

}

#endif
