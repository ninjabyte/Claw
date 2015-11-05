/*
 ============================================================================
 Name        : parser.c
 Author      : Benedikt Müssig
 Version     : 0.1
 Copyright   : (c) 2015 Benedikt Müssig
 Description : Parser for the Claw language
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "parser.h"

const char* keywords[13] = {
		"break", "continue", "else", "elseif", "end", "false",
		"for", "function", "if", "return", "true", "var", "while"};

int parse(char *file)
{
  FILE *fp;

  fp = fopen(file, "r");
  if(!fp) {
    error("Invalid file!");
    return -1;
  }

  char line_buffer[LINE_LENGTH];
  int line_ptr = 0;

  while(1) {
    int chr = fgetc(fp);
    if(chr == EOF)
      break;
    if(chr == '\n' || chr == ';') {
      parse_line(line_buffer); // new line; copy buffer
      for(int i = 0; i < LINE_LENGTH; i++)
        line_buffer[i] = 0;
      line_ptr = 0;
      continue;
    }

    line_buffer[line_ptr++] = chr;
    if(line_ptr >= LINE_LENGTH) {
    	error("Line too long!");
    	break;
    }
  }

  fclose(fp);
  return 0;
}

int parse_line(char line[])
{
  for(int i = 0; line[i] && i < LINE_LENGTH; i++) {

    printf("%c", line[i]);
  }
  return 0;
}
