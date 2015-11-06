/*
 * rpn.c
 *
 *  Created on: 06.11.2015
 *      Author: Benedikt
 */

#include "rpn.h"
/*
int toRpn(char inputQueue[], char outputQueue[])
{
	int inputQueuePtr = 0;
	int outputQueuePtr = 0
	volatile int16_t number = 0;

	for( ; inputQueue[inputQueuePtr]; inputQueuePtr++) {
		if((inputQueue[inputQueuePtr] >= '0' && inputQueue[inputQueuePtr] <= '9') || inputQueue[inputQueuePtr] == '-')
			outputQueue[outputQueuePtr++] = inputQueue[inputQueuePtr]; // add number to output buffer

		if(0) { // function token

		} else if(inputQueue[inputQueuePtr] == ',') { // argument seperator

		} else if(0) {

		}
	}

	return 1;
}

*/
int16_t conv_number(char inputQueue[])
{
	int inputQueuePtr = 0;
	char numBuffer[6];
	int numBufferPtr = 0;
	volatile int16_t number = 0;

	for( ; inputQueue[inputQueuePtr]; inputQueuePtr++) {
		if((inputQueue[inputQueuePtr] >= '0' && inputQueue[inputQueuePtr] <= '9') || inputQueue[inputQueuePtr] == '-') {
			numBuffer[numBufferPtr++] = inputQueue[inputQueuePtr]; // add to number buffer
		}
		if(!inputQueue[inputQueuePtr + 1]) {
			number = atoi(numBuffer); // convert number to an integer
			while(numBufferPtr > 0)
				numBuffer[numBufferPtr--] = 0;
		}
	}

	return number;
}
