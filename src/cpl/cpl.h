/*
 * cpl.h
 *
 *  Created on: 07.11.2015
 *      Author: Benedikt
 */

#ifndef CPL_CPL_H_
#define CPL_CPL_H_

#include <stdio.h>
#include <stdint.h>

typedef uint8_t instr_t;
typedef uint32_t permission_t;

typedef enum {
	IN_NOP = 0x0,	 /* Do nothing. */
	IN_ADD = 0x1,	 /* Pops $0 and $1. Pushes $1   $0. */
	IN_SUB = 0x2,	 /* Pops $0 and $1. Pushes $1 - $0. */
	IN_MUL = 0x3,	 /* Pops $0 and $1. Pushes $1 * $0. */
	IN_DIV = 0x4,	 /* Pops $0 and $1. Pushes $1 / $0. This is a signed division. */
	IN_RICK = 0x5,	 /* nice */
	IN_LD = 0x6,	 /* Pushes the value of the numeric variable. */
	IN_LDS = 0x7,	 /* Pops $0. Pushes the numeric variable referenced by $0. */
	IN_LDA = 0x8,	 /* Pops $0. Pushes the number at index $0 of the array. */
	IN_LDAS = 0x9,	 /* Pops $0 and $1. Pushes the number at index $1 of the array referenced by $0. */
	IN_LDC = 0xa,	 /* Pushes the constant. */
	IN_ST = 0xb,	 /* Pops $0. Stores $0 in the numeric variable. */
	IN_STS = 0xc,	 /* Pops $0 and $1. Stores $1 in the numeric variable referenced by $0. */
	IN_STA = 0xd,	 /* Pops $0 and $1. Stores $1 at index $0 of the array. */
	IN_STAS = 0xe,	 /* Pops $0, $1 and $2. Stores $2 at index $1 of the array referenced by $0. */
	IN_DEL = 0xf,	 /* Pops $0. */
	IN_SWP = 0x10,	 /* Pops $0 and $1. Pushes $0 and then $1. */
	IN_DUP = 0x11,	 /* Pushes $0 to the stack. */
	IN_VC = 0x12,	 /* Creates a new variable. */
	IN_VCA = 0x13,	 /* Pops $0. Creates a new array with the size $0. */
	IN_VPX = 0x14,	 /* Pushes the ID of the variable. */
	IN_VPXS = 0x15,	 /* Pops $0. Pushes the ID of the variable referenced by the $0. */
	IN_VPS = 0x16,	 /* Pushes the size of the array. */
	IN_VPSS = 0x17,	 /* Pops $0. Pushes the size of the array referenced by $0. */
	IN_VSWP = 0x18,	 /* Swaps two variables with each other. */
	IN_VSWPS = 0x19,	 /* Swaps the variable referenced by $1 with $0. */
	IN_VCPY = 0x1a,	 /* Copies the contents of the variable to another variable. */
	IN_VCPYS = 0x1b,	 /* Copies the contents of the variable referenced by $1 to the variable referenced by $0 */
	IN_VD = 0x1c,	 /* Destroys the last created variable. */
	IN_VDR = 0x1d,	 /* Destroys multiple of the last created variables. */
	IN_VDRS = 0x1e,	 /* Pops $0. Destroys $0 of the last created variables. */
	IN_JP = 0x22,	 /*  */
	IN_JPZ = 0x23,	 /*  */
	IN_JPNZ = 0x24,	 /*  */
	IN_RET = 0x25,	 /* Return to $0. If the bottom of the stack is reached, the program will halt. */
	IN_CALL = 0x26,	 /* Push current location to stack, and call the function */
	IN_SC = 0x27,	 /* Pops all required arguments. Calls a native function. */
	IN_LAND = 0x29,	 /* Pops $0 and $1. Pushes $1 && $0. This is a locical function */
	IN_LOR = 0x2a,	 /* Pops $0 and $1. Pushes $1 || $0. This is a logical function. */
	IN_AND = 0x2b,	 /* Pops $0 and $1. Pushes $1 & $0. This is a bitwise function. */
	IN_OR = 0x2c,	 /* Pops $0 and $1. Pushes $1 | $0. This is a bitwise function. */
	IN_XOR = 0x2d,	 /* Pops $0 and $1. Pushes $1 ^ $0. This is a bitwise function. */
	IN_NOT = 0x2e,	 /* Pops $0. Pushes !$0. This is a bitwise function. */
	IN_BSL = 0x2f,	 /* Pops $0 and $1. Pushes $1 << $0. This is a bitwise function. */
	IN_BSR = 0x30,	 /* Pops $0 and $1. Pushes $1 >> $0. This is a bitwise function. */
	IN_INC = 0x32,	 /* Pops $0. Pushes $0   1. */
	IN_DEC = 0x33	 /* Pops $0. Pushes $0 - 1. */
} Instruction;

enum Version
{
	VER_MAJOR = 0,
	VER_MINOR = 1,
	VER_REVISION = 2
};

enum Permissions
{
	PERM_WIFI
};

typedef struct
{
	char name[15];
	char author[15];
	uint8_t version[3];
	permission_t permissions;
} CplHeader;

/* compiler state */
typedef struct
{
	FILE* dst;	/* the destination file */
	CplHeader ch; /* header */
} CplState;

void cpl_init(CplState*, CplHeader*, FILE*);
void cpl_write_header(CplState*);
void cpl_write_instr(CplState*, instr_t);
void cpl_write_arg8(CplState*, uint8_t);
void cpl_write_arg16(CplState*, int16_t);

#endif /* CPL_CPL_H_ */
