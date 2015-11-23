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
#include "instruction.h"

typedef uint32_t permission_t;

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
