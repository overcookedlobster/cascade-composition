#include <stdio.h>
#include <strings.h>
#include "fsm-deb.h"

void main(){
int state = 0;
int led[4];

for(state=0;state<4;state++){
	fsm_led(&state, led);
	printf("state:%d , led:[%d %d %d %d]\n", state, led[0], led[1], led[2], led[3]);
}
}
