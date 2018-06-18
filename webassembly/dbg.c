#include "dbg.h"

void log_to_file(char * filename, const char* format, ...) {
	va_list args;
	FILE *f = fopen(filename,"a+");
	va_start (args, format);
	vfprintf (f, format, args);
	va_end (args);
	fclose(f);
}

uint8_t * to_hex(uint8_t * data, int size)
{
	uint32_t i;
	uint8_t *out = (uint8_t *)malloc(2*size);
	if(!out) {
		return NULL;
	}
	char alpha [] = "0123456789abcdef";
	for(i=0; i<size; i++) {
		out[i*2] = alpha[data[i] >> 4];
		out[i*2+1] = alpha[data[i] & 0xF];
	}
	return out;
}


void hexdump_to_file(const void * data, int size, char *name, uint64_t start, char *filename) {

	unsigned char *p = (unsigned char*)data;
	int n, l, i, s, dashlen;

	char line [260] = {0};

	sprintf(line, "\033[36m                   ┌");
	if (name != NULL && strlen(name) > 0) {
		s = strlen(name);
		dashlen = (46-s)/2;
		for(i=0;i<dashlen;i++){
			strncat(line, "─", sizeof(line)-strlen(line)-1);
		}
		strncat(line, "  ", sizeof(line)-strlen(line)-1);
		strncat(line, "\033[1m", sizeof(line)-strlen(line)-1);
		strncat(line, name, sizeof(line)-strlen(line)-1);
		strncat(line, "\033[0m\033[36m", sizeof(line)-strlen(line)-1);
		strncat(line, "  ", sizeof(line)-strlen(line)-1);
		for(i=0;i<(dashlen-(1-s%2));i++){
			strncat(line, "─", sizeof(line)-strlen(line)-1);
		}
	}else{
		for(i=0;i<49;i++){
			strncat(line, "─", sizeof(line)-strlen(line)-1);
		}
	}
	strncat(line, "┬", sizeof(line)-strlen(line)-1);
	for(i=0;i<18;i++){
		strncat(line, "─", sizeof(line)-strlen(line)-1);
	}
	strncat(line, "┐\033[0m\n", sizeof(line)-strlen(line)-1);
	if(filename == NULL) {
		printf("%s",line);
	}else{
		log_to_file(filename,"%s",line);
	}

	for(n=0; n<size; n+=16) {
		sprintf(line, "\033[36m0x%016lx │ \033[0m\033[1m",(n+start));
		for(l=n; l<n+16; l++) {
			if (l < size) {
				sprintf(line, "%s%02x ",line, p[l]);
			}else{
				strncat(line, "   ", sizeof(line)-strlen(line)-1);
			}
		}
		strncat(line, "\033[0m\033[36m│\033[0m\033[1m ",sizeof(line)-strlen(line)-1);
		for(l=n; l<n+16; l++) {
			if (l < size) {
				if (isprint(p[l]) == 0) {
					strncat(line, ".", sizeof(line)-strlen(line)-1);
				}else{
					sprintf(line, "%s%c",line, p[l]);
				}
			}else{
				strncat(line, " ", sizeof(line)-strlen(line)-1);
			}
		}
		strncat(line, "\033[0m\033[36m │\033[0m\n",sizeof(line)-strlen(line)-1);
		if(filename == NULL) {
			printf("%s",line);
		}else{
			log_to_file(filename,"%s",line);
		}
	}
	sprintf(line, "\033[36m                   └");
	for(i=0;i<49;i++){
		strncat(line, "─", sizeof(line)-strlen(line)-1);
	}
	strncat(line, "┴", sizeof(line)-strlen(line)-1);
	for(i=0;i<18;i++){
		strncat(line, "─", sizeof(line)-strlen(line)-1);
	}
	strncat(line, "┘\033[0m\n", sizeof(line)-strlen(line)-1);
	if(filename == NULL) {
		printf("%s",line);
	}else{
		log_to_file(filename,"%s",line);
	}
}

void hexdump(const void * data, int size, char *name, uint64_t start)
{
	hexdump_to_file(data,size,name,start,NULL);
}
