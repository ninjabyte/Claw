/*
 * func.h
 *
 *  Created on: 10.11.2015
 *      Author: Benedikt
 */

#ifndef TYPES_VARS_H_
#define TYPES_VARS_H_

typedef uint8_t array_val_t;
typedef int16_t numeric_val_t;

typedef uint8_t varscope_t;
typedef uint8_t vartype_t;

enum
{
	VARTYPE_NUMBER,
	VARTYPE_ARRAY,
	VARTYPE_NONE
} VarType;

typedef struct
{
	char* name;
	varscope_t level;
	uint8_t type;
} var_t;

typedef struct
{
	char* name;
	vartype_t type;
} arg_proto_t;

typedef struct
{
	char* name;
	arg_proto_t** prototype;
	vartype_t type;
} function_t;

#endif /* TYPES_VARS_H_ */
