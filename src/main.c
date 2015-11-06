/*
 * main.c
 *
 *  Created on: 05.11.2015
 *      Author: Benedikt
 */

#include <stdlib.h>
#include "parser.h"
#include "io.h"
#include "lex/lex.h"
#include "error/error.h"

int main(int argc, char *argv[])
{
  if(argc < 2) {
    error("No file specified!");
    return -1;
  }
  error_printmsg(lex_test(argv[1]));
  return EXIT_SUCCESS;
}
