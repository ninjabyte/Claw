/*
 * cpl.c
 *
 *  Created on: 07.11.2015
 *      Author: Benedikt
 */

#include "cpl.h"

void cpl_init(CplState* cs, CplHeader* ch, FILE* fp)
{
	cs->dst = fp;
	cs->ch = *ch;
}

void cpl_write_header(CplState* cs)
{

}

void cpl_write_instr(CplState* cs, instr_t instr)
{

}

void cpl_write_arg8(CplState* cs, uint8_t arg)
{

}

void cpl_write_arg16(CplState* cs, int16_t arg)
{

}
