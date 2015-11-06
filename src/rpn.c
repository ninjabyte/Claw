/*
 * rpn.c
 *
 *  Created on: 06.11.2015
 *      Author: Benedikt
 */

char* toRpn(char *str) {
	char outputQueue[strlen(str)];
	int outputQueuePtr = 0;
	char numBuffer[6];
	int numBufferPtr = 0;
	int16_t number = 0;

	for( ; str[outputQueuePtr]; outputQueuePtr++) {
		if((str[outputQueuePtr] >= '0' && str[outputQueuePtr] <= '9') || str[outputQueuePtr] == '.') {
			numBuffer[numBufferPtr++] = str[outputQueuePtr];
		} else {
			number = atoi(numBufferPtr);
			while(numBufferPtr > 0)
				numBuffer[numBufferPtr--] = 0;
		}

		if(0) { // function token

		} else if(str[outputQueuePtr] == ',') { // argument seperator

		} else if() {

		}
	}

	return outputQueue;
}
