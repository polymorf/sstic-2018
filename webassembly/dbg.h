#ifndef __DBG_H__
#define __DBG_H__
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define err(f_, ...) printf("[\033[31;1m!\033[0m] "); printf(f_, ##__VA_ARGS__);
#define ok(f_, ...) printf("[\033[32;1m+\033[0m] "); printf(f_, ##__VA_ARGS__);
#define info(f_, ...) printf("[\033[34;1m-\033[0m] "); printf(f_, ##__VA_ARGS__);
#define debug(f_, ...) printf("DEBUG:"); printf(f_, ##__VA_ARGS__);
#define warn(f_, ...) printf("[\033[33;1mw\033[0m] "); printf(f_, ##__VA_ARGS__);

void hexdump(const void * data, int size, char *name, uint64_t start);
void hexdump_to_file(const void * data, int size, char *name, uint64_t start, char *filename);
void log_to_file(char * filename, const char* format, ...);
uint8_t * to_hex(uint8_t * data, int size);

#endif
