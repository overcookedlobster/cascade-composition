#include <strings.h>
#include <stdio.h>
#include "fsm-deb.h"

void main(){
int button = 0;
int state = 0;
int state_led = 0;
int flag = 0;
int i = 0;
while(i < 10){
	for(button=-1;button<2;button++){
		for(flag = 0; flag <2; flag++){
		fsm_deb(button, &state, &flag, &state_led);
		printf("button:%d, state:%d, flag:%d, state_led:%d\n", button, state, flag, state_led);
		}
	}
	i++;
} 
}
