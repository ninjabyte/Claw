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

enum Instruction
{
	IN_NOP,
	IN_ADD,
	IN_SUB,
	IN_MUL,
	IN_SDIV,
	IN_UDIV,
	IN_LDV,
	IN_LDC,
	IN_STR,
	IN_DEL,
	IN_SWP,
	IN_DUP,
	IN_LEA,
	IN_SEA,
	IN_NONE = -1
};

// compiler state
typedef struct
{
	FILE* dst;	// the destination file
} CplState;

void cpl_init(CplState* cs, FILE* fp);
void cpl_write_instr(CplState* cs, int instr);
void cpl_write_arg8(CplState* cs, uint8_t arg);
void cpl_write_arg16(CplState* cs, int16_t arg);

#endif /* CPL_CPL_H_ */
