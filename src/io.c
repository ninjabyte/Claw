/*
 * io.c
 *
 *  Created on: 05.11.2015
 *      Author: Benedikt
 */

#include <stdio.h>

#include "io.h"

void error(const char *msg) {
  fprintf(stderr, "%s\n", msg);
}
