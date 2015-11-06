/*
 * rpn.c
 *
 *  Created on: 06.11.2015
 *      Author: Benedikt
 */

#include "rpn.h"

int toRpn(char *inputQueue, char *outputQueue)
{
	int outputQueuePtr = 0;
	char *numBuffer[6];
	int numBufferPtr = 0;
	volatile int16_t number = 0;

	for( ; inputQueue[outputQueuePtr]; outputQueuePtr++) {
		if((inputQueue[outputQueuePtr] >= '0' && inputQueue[outputQueuePtr] <= '9') || inputQueue[outputQueuePtr] == '-') {
			numBuffer[numBufferPtr++] = inputQueue[outputQueuePtr]; // add to number buffer
		} else {
			number = atoi(numBufferPtr); // convert number to an integer
			while(numBufferPtr > 0)
				numBuffer[numBufferPtr--] = 0;
		}

		if(0) { // function token

		} else if(inputQueue[outputQueuePtr] == ',') { // argument seperator

		} else if(0) {

		}
	}

	return 1;
}
