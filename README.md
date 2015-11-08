# Claw — The embedded scripting language

## What is Claw?
Claw is an easy to learn programming language, that is highly memory optimized and can even be compiled right on the device. Currently a file system with stream support will be required to compile and execute programs, but in the future we work on more portable solutions such as executing from a SPI device (SRAM, EEPROM), executing from internal RAM or Flash. The languages syntax is inspired by Lua but it has no tables. Claw only knows two types of variables: numbers (int16) and arrays (of uint8).
This is an important factor to be memory efficient as arrays are only as big as they are needed most of the time. Of course can the types be altered by changing the code, but this is the configuration we use and suggest.
Another feature of Claw is, that it can be compiled and ran without loading the full program into RAM at once as it's streamed.

## What is the development status?
Claw is currently under heavy development. Any help is welcomed :)
