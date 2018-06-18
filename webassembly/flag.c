#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "dbg.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <byteswap.h>


// Speck 128 32 rounds

uint64_t rol(uint64_t x, uint8_t y) {
	return (x<<y)|(x>>(64-y));
}

uint64_t table[] = {
	0x52EF7125CFD96BBB,    // 0
	0xBE416E09FC1BBD52,    // 1
	0x80083F5C83EA289B,    // 2
	0x9784D8E9FDDA137E,    // 3
	0x705AF179C6ACB293,    // 4
	0xA6F0A2B874C7F291,    // 5
	0x96AE87C870F2392B,    // 6
	0x8DD0532E85BE0FC4,    // 7
};



uint64_t * loadkey(uint64_t *key) {
	uint8_t r = 0;
	uint64_t * ctx = malloc(0x100);
	uint64_t a = key[1];
	uint64_t b = key[0];

	for(r=0; r<32; r++) {
		ctx[r] = b;
		a = r ^ (b + rol(a,56));
		b = a ^ rol(b,3);
	}
	return ctx;
}

uint64_t * decrypt(uint64_t *ctx, uint64_t *input, uint32_t len) {
	int8_t r;
	uint8_t bloc;
	for(bloc=0; bloc<(len/16); bloc++) {
		uint64_t a = input[bloc*2];
		uint64_t b = input[bloc*2 + 1];

		for(r=31; r>=0; r-=1) {
			a = rol(b^a,61);
			b = rol((ctx[r] ^ b) - a, 8);
		}

		input[bloc*2]     = a;
		input[bloc*2 + 1] = b;
	}
}

int main() {
	uint64_t key[2];
	uint64_t encrypted[6];

	memcpy(key,&table[6],sizeof(key));

	hexdump(key,0x10,"key", 0);
	uint64_t * ctx = loadkey(key);
	hexdump(ctx,0x100,"ctx",0);

	memcpy(encrypted,&table[0],sizeof(encrypted));
	hexdump(encrypted,0x30,"encrypted",0);

	decrypt(ctx, encrypted, 0x30);
	
	hexdump(encrypted,0x30,"cleartext",0);
	printf("%s\n",encrypted);

}

