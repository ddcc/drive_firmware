#include<stdio.h>
#include<stdlib.h>



/*
enc file decrypter for "Samsung SSD Firmware Update Utility Ver. 3.1"
(850evo, 950pro, 960evo, 960pro)
*/


/* https://github.com/kokke/tiny-AES-c */

#include "aes.h"
#include "aes.c"

/* 제목없음1 (2019-01-07 오후 5:17:50)
   StartOffset: 00000000, EndOffset: 0000001F, 길이: 00000020 */

unsigned char AES_KEY[32] = {
	0x83, 0x37, 0x83, 0x8B, 0x23, 0x45, 0xAA, 0x76, 0x62, 0xCD, 0x90, 0x2A,
	0x97, 0x31, 0xEF, 0x52, 0xF4, 0x50, 0x62, 0x75, 0xB5, 0x7C, 0xA7, 0xCD,
	0x9C, 0x36, 0xB5, 0x65, 0xBF, 0x99, 0x3C, 0xD1
};



void Decrypt(const char *srcfile,const char *dstfile) {

	FILE *fp=fopen(srcfile,"rb");

	fseek(fp, 0, SEEK_END);
	unsigned int Len = ftell(fp);
	unsigned char *buf = (unsigned char *)malloc(Len + 16);
	memset(buf, 0, Len);
	fseek(fp, 0, SEEK_SET);
	fread(buf, 1, Len, fp);
	fclose(fp);

	struct AES_ctx ctx;

	for(int i=0; i<Len; i+=16) {
		AES_init_ctx(&ctx, AES_KEY);
		AES_ECB_decrypt(&ctx, buf+i);
	}


	FILE *fp2=fopen(dstfile,"wb");
	fwrite(buf,1,Len,fp2);
	fclose(fp2);

	free(buf);
	buf = NULL;
	return;
}

int main(void) {
	Decrypt("DSRD.enc","DSRD.dec");
}

