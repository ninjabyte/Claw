#ifndef ERROR_H_
#define ERROR_H_

// error code enum
enum Error
{
	ERR_NO_ERROR,
	ERR_UNEXPECTED_INPUT,
	ERR_UNEXPECTED_EOI,
	ERR_UNEXPECTED_TOKEN,
	ERR_OUT_OF_MEMORY,
	NUM_ERRORS
};

void error_printmsg(unsigned int code);

#endif /* ERROR_H_ */
