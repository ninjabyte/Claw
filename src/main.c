/*
 * main.c
 *
 *  Created on: 05.11.2015
 *      Author: Benedikt
 */

int main(int argc, char *argv[])
{
  if(argc < 2) {
    error("No file specified!");
    return -1;
  }
  return parse(argv[1]);
}
