#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <stdint.h>

enum Instruction
{
	IN_NOP	= 0x00,
	IN_ADD	= 0x01,
	IN_SUB	= 0x02,
	IN_MUL	= 0x03,
	IN_DIV	= 0x04,

	IN_LDV	= 0x06,
	IN_LDC	= 0x07,
	IN_STR	= 0x08,
	IN_DEL	= 0x09,
	IN_SWP	= 0x0A,
	IN_DUP	= 0x0B,
	IN_LEA	= 0x0C,
	IN_SEA	= 0x0D,

	IN_JP	= 0x17,
	IN_JPZ	= 0x18,
	IN_JPNZ	= 0x19,
	IN_RET	= 0x1A,
	IN_CALL	= 0x1B,

	IN_HCF	= 0x20,

	IN_LAND	= 0x22,
	IN_LOR	= 0x23,
	IN_AND	= 0x24,
	IN_OR	= 0x25,
	IN_XOR	= 0x26,
	IN_NOT	= 0x27,
	IN_BSL	= 0x28,
	IN_BSR	= 0x29,

	IN_INC	= 0x2B,
	IN_DEC	= 0x2C,

	NUM_INSTRUCTIONS
};

typedef uint8_t instr_t;

#endif /* INSTRUCTION_H_ */
