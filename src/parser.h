/*
 * parser.h
 *
 *  Created on: 05.11.2015
 *      Author: Benedikt
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "cpl/cpl.h"

int do_compile(char*, char*, CplHeader*);
int do_debug_parse(char*);

#define LINE_LENGTH 100

#endif /* PARSER_H_ */
