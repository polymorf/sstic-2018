#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "dbg.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


const uint8_t kuz_pi[0x100] = {
	0x5c, 0x23, 0x7a, 0x61, 0xd8, 0xdf, 0x76, 0x9d, 0x54, 0x9b, 0x72, 0xd9, 0xd0, 0x57, 0x6e, 0x15,
	0x4c, 0x13, 0x6a, 0x51, 0xc8, 0xcf, 0x66, 0x8d, 0x44, 0x8b, 0x62, 0xc9, 0xc0, 0x47, 0x5e, 0x05,
	0x3c, 0x03, 0x5a, 0x41, 0xb8, 0xbf, 0x56, 0x7d, 0x34, 0x7b, 0x52, 0xb9, 0xb0, 0x37, 0x4e, 0xf5,
	0x2c, 0xf3, 0x4a, 0x31, 0xa8, 0xaf, 0x46, 0x6d, 0x24, 0x6b, 0x42, 0xa9, 0xa0, 0x27, 0x3e, 0xe5,
	0x1c, 0xe3, 0x3a, 0x21, 0x98, 0x9f, 0x36, 0x5d, 0x14, 0x5b, 0x32, 0x99, 0x90, 0x17, 0x2e, 0xd5,
	0x0c, 0xd3, 0x2a, 0x11, 0x88, 0x8f, 0x26, 0x4d, 0x04, 0x4b, 0x22, 0x89, 0x80, 0x07, 0x1e, 0xc5,
	0xfc, 0xc3, 0x1a, 0x01, 0x78, 0x7f, 0x16, 0x3d, 0xf4, 0x3b, 0x12, 0x79, 0x70, 0xf7, 0x0e, 0xb5,
	0xec, 0xb3, 0x0a, 0xf1, 0x68, 0x6f, 0x06, 0x2d, 0xe4, 0x2b, 0x02, 0x69, 0x60, 0xe7, 0xfe, 0xa5,
	0xdc, 0xa3, 0xfa, 0xe1, 0x58, 0x5f, 0xf6, 0x1d, 0xd4, 0x1b, 0xf2, 0x59, 0x50, 0xd7, 0xee, 0x95,
	0xcc, 0x93, 0xea, 0xd1, 0x48, 0x4f, 0xe6, 0x0d, 0xc4, 0x0b, 0xe2, 0x49, 0x40, 0xc7, 0xde, 0x85,
	0xbc, 0x83, 0xda, 0xc1, 0x38, 0x3f, 0xd6, 0xfd, 0xb4, 0xfb, 0xd2, 0x39, 0x30, 0xb7, 0xce, 0x75,
	0xac, 0x73, 0xca, 0xb1, 0x28, 0x2f, 0xc6, 0xed, 0xa4, 0xeb, 0xc2, 0x29, 0x20, 0xa7, 0xbe, 0x65,
	0x9c, 0x63, 0xba, 0xa1, 0x18, 0x1f, 0xb6, 0xdd, 0x94, 0xdb, 0xb2, 0x19, 0x10, 0x97, 0xae, 0x55,
	0x8c, 0x53, 0xaa, 0x91, 0x08, 0x0f, 0xa6, 0xcd, 0x84, 0xcb, 0xa2, 0x09, 0x00, 0x87, 0x9e, 0x45,
	0x7c, 0x43, 0x9a, 0x81, 0xf8, 0xff, 0x96, 0xbd, 0x74, 0xbb, 0x92, 0xf9, 0xf0, 0x77, 0x8e, 0x35,
	0x6c, 0x33, 0x8a, 0x71, 0xe8, 0xef, 0x86, 0xad, 0x64, 0xab, 0x82, 0xe9, 0xe0, 0x67, 0x7e, 0x25,
};

static const unsigned char kuz_pi_inv[0x100] = {
	0xdc, 0x63, 0x7a, 0x21, 0x58, 0x1f, 0x76, 0x5d, 0xd4, 0xdb, 0x72, 0x99, 0x50, 0x97, 0x6e, 0xd5,
	0xcc, 0x53, 0x6a, 0x11, 0x48, 0x0f, 0x66, 0x4d, 0xc4, 0xcb, 0x62, 0x89, 0x40, 0x87, 0x5e, 0xc5,
	0xbc, 0x43, 0x5a, 0x01, 0x38, 0xff, 0x56, 0x3d, 0xb4, 0xbb, 0x52, 0x79, 0x30, 0x77, 0x4e, 0xb5,
	0xac, 0x33, 0x4a, 0xf1, 0x28, 0xef, 0x46, 0x2d, 0xa4, 0xab, 0x42, 0x69, 0x20, 0x67, 0x3e, 0xa5,
	0x9c, 0x23, 0x3a, 0xe1, 0x18, 0xdf, 0x36, 0x1d, 0x94, 0x9b, 0x32, 0x59, 0x10, 0x57, 0x2e, 0x95,
	0x8c, 0x13, 0x2a, 0xd1, 0x08, 0xcf, 0x26, 0x0d, 0x84, 0x8b, 0x22, 0x49, 0x00, 0x47, 0x1e, 0x85,
	0x7c, 0x03, 0x1a, 0xc1, 0xf8, 0xbf, 0x16, 0xfd, 0x74, 0x7b, 0x12, 0x39, 0xf0, 0x37, 0x0e, 0x75,
	0x6c, 0xf3, 0x0a, 0xb1, 0xe8, 0xaf, 0x06, 0xed, 0x64, 0x6b, 0x02, 0x29, 0xe0, 0x27, 0xfe, 0x65,
	0x5c, 0xe3, 0xfa, 0xa1, 0xd8, 0x9f, 0xf6, 0xdd, 0x54, 0x5b, 0xf2, 0x19, 0xd0, 0x17, 0xee, 0x55,
	0x4c, 0xd3, 0xea, 0x91, 0xc8, 0x8f, 0xe6, 0xcd, 0x44, 0x4b, 0xe2, 0x09, 0xc0, 0x07, 0xde, 0x45,
	0x3c, 0xc3, 0xda, 0x81, 0xb8, 0x7f, 0xd6, 0xbd, 0x34, 0x3b, 0xd2, 0xf9, 0xb0, 0xf7, 0xce, 0x35,
	0x2c, 0xb3, 0xca, 0x71, 0xa8, 0x6f, 0xc6, 0xad, 0x24, 0x2b, 0xc2, 0xe9, 0xa0, 0xe7, 0xbe, 0x25,
	0x1c, 0xa3, 0xba, 0x61, 0x98, 0x5f, 0xb6, 0x9d, 0x14, 0x1b, 0xb2, 0xd9, 0x90, 0xd7, 0xae, 0x15,
	0x0c, 0x93, 0xaa, 0x51, 0x88, 0x4f, 0xa6, 0x8d, 0x04, 0x0b, 0xa2, 0xc9, 0x80, 0xc7, 0x9e, 0x05,
	0xfc, 0x83, 0x9a, 0x41, 0x78, 0x3f, 0x96, 0x7d, 0xf4, 0xfb, 0x92, 0xb9, 0x70, 0xb7, 0x8e, 0xf5,
	0xec, 0x73, 0x8a, 0x31, 0x68, 0x2f, 0x86, 0x6d, 0xe4, 0xeb, 0x82, 0xa9, 0x60, 0xa7, 0x7e, 0xe5,
};

static const unsigned char kuz_lvec[] = {
	0x94, 0x20, 0x85, 0x10, 0xc2, 0xc0, 0x01, 0xfb, 0x01, 0xc0, 0xc2, 0x10, 0x85, 0x20, 0x94, 0x01,
};


void xor(uint8_t *dst, uint8_t *xor_with, uint32_t len) {
	int i;
	for(i=0;i<len;i++) {
		dst[i] ^= xor_with[i];
	}
}

static uint8_t kuz_mul_gf256(uint8_t x, uint8_t y)
{
	uint8_t z;
	z = 0;
	while (y) {
		if (y & 1)
			z ^= x;
		x = (x << 1) ^ (x & 0x80 ? 0xC3 : 0x00);
		y >>= 1;
	}
	return z;
}

static void kuz_l_inv(uint8_t *w) {
	int i, j;
	uint8_t x;
	for (j = 0; j < 16; j++) {
		x = w[0];
		for (i = 0; i < 15; i++) {
			w[i] = w[i + 1];
			x ^= kuz_mul_gf256(w[i], kuz_lvec[i]);
		}
		w[15] = x;
	}
}

static void kuz_l(uint8_t *w) {
	int i, j;
	uint8_t x;
	for (j = 0; j < 16; j++) {
		x = w[15];
		for (i = 14; i >= 0; i--) {
			w[i + 1] = w[i];
			x ^= kuz_mul_gf256(w[i], kuz_lvec[i]);
		}
		w[0] = x;
	}
}

void decryptBlock(uint8_t *ctx, uint8_t *msg) {
	int r, i;
	unsigned char state[16];
	unsigned char *round_key;
	memcpy(state, msg, 16);

	r=9;
	round_key = ctx+r*16;
	xor(state, round_key, 16);
	for(r=8; r>=0; r--) {
		round_key = ctx+r*16;
		kuz_l_inv(state);
		xor(state, round_key, 16);
	}
	for(i=0; i<16; i++) {
		state[i] = kuz_pi_inv[state[i]];
	}
	memcpy(msg, state, 16);
}

void encryptBlock(uint8_t *ctx, uint64_t *msg) {
	int r, i;
	unsigned char state[16];
	unsigned char *round_key;

	memcpy(state, msg, 16);

	for(i=0; i<16; i++) {
		state[i] = kuz_pi[state[i]];
	}
	for(r=0; r<=8; r++) {
		round_key= ctx+r*16;
		xor(state, round_key, 16);
		kuz_l(state);
	}
	round_key= ctx+r*16;
	xor(state, round_key, 16);
	memcpy(msg, state, 16);
}

void setkey(uint8_t *ctx, uint8_t *key) {
	uint64_t v15, v40, v41, v42, v13, v16, v19, v20, v23, i, v24, v17, v21, v43, v14, v44, v29, v9, v31, v32, v35, j, v8, v36, v7, v33, v27, v10;
	uint8_t x;
	int64_t v30, v18;
	unsigned char state[16] = {0};
	unsigned char state2[16] = {0};

	v7 = *(uint64_t *)key;
	v8 = *(uint64_t *)&key[8];
	v9 = *(uint64_t *)&key[16];
	v10 = *(uint64_t *)&key[24];
	memcpy(ctx,key,32);
	for(v42=1; v42<=32; v42++) {
		v41 = v10;
		v40 = v9;
		memset(state2,0,16);
		state2[15] = v42;
		kuz_l(state2);
		*(uint64_t *)&state[0] = v7 ^ *(uint64_t *)&state2[0];
		*(uint64_t *)&state[8] = v8 ^ *(uint64_t *)&state2[8];
		kuz_l(state);
		v10 = v8;
		v9 = v7;
		v7 = *(uint64_t *)&state[0] ^ v40;
		v8 = *(uint64_t *)&state[8] ^ v41;
		*(uint64_t *)&state[0] = v7;
		*(uint64_t *)&state[8] = v8;
		if ( (v42 & 7) == 0 ) {
			*(uint64_t *)&ctx[4*v42] = v7;
			*(uint64_t *)&ctx[4*v42 + 8] = v8;
			*(uint64_t *)&ctx[4*v42 + 16] = v9;
			*(uint64_t *)&ctx[4*v42 + 24] = v10;
		}
	}
}

int main() {
	int i,j,k;
	unsigned char ctx[10*0x10] = {0};
	unsigned char key[0x20] = "\x43\x55\xe1\x54\x49\x28\x78\x7f\xd9\xe8\xb5\xdf\x00\x0f\x0e\x6e\xfc\x96\x1d\x68\xb2\x82\x53\xaa\x2c\x95\x28\x44\xa2\x91\x28\xe5";
	uint8_t msg[16] = {0};
	uint8_t msg2[16] = {0};
	uint8_t iv[16] = {0};
	uint8_t iv_next[16] = {0};

	//setkey(ctx,key);
	memset(ctx,0,sizeof(ctx));

	int fd = open("payload", O_RDONLY, 0);
	if (fd <= 0) {
		err("can't open file\n");
		return 0;
	}
	if (lseek(fd,16,SEEK_SET) < 0) {
		err("can't seek\n");
		close(fd);
		return 0;
	}
	if(read(fd,iv,16) != 16) {
		err("can't read\n");
		close(fd);
		return 0;
	}

	uint8_t search[] = "-Fancy Nounours-";
	xor(search,iv,16);


	if(read(fd,msg2,16) != 16) {
		err("can't read\n");
		close(fd);
		return 0;
	}

	hexdump(msg2,16,"input",0);
	hexdump(search,16,"search",0);

	for(k=0x0;k<0x10;k++) {
		int found=0;
		for(i=0;i<0x100;i++) {
			memcpy(msg,msg2,0x10);
			ctx[k] = i;
			decryptBlock(ctx,msg);
			if(msg[k] == search[k]){
				found=1;
				break;
			}
		}
		if(!found) {
			printf("not found for k=%02d\n",k);
		}
	}

	hexdump(ctx,10*0x10,"CTX",0);
	memcpy(msg,msg2,0x10);
	decryptBlock(ctx,msg);
	xor(msg,iv,0x10);
	hexdump(msg,0x10,"Decrypted first bloc",0);

	memcpy(iv,msg2,16);

	int fd2 = open("./dump",O_WRONLY | O_CREAT);
	if (fd2 <= 0) {
		err("can't open elf\n");
		return 0;
	}

	while(read(fd,msg,16) == 16) {
		memcpy(iv_next,msg,16);
		decryptBlock(ctx,msg);
		xor(msg,iv,16);
		write(fd2,msg,16);
		memcpy(iv,iv_next,16);
	}
	close(fd);
	close(fd2);
}
