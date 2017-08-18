#ifndef _DES_H_
#define _DES_H_

#define ENCRYPTION_MODE 1
#define DECRYPTION_MODE 0

typedef struct {
	unsigned char k[8];
	unsigned char c[4];
	unsigned char d[4];
} keyset;

void keygen(unsigned char* key);
void subkeys_gen(unsigned char* mainkey, keyset* keysets);
void process_message(unsigned char* message_piece, unsigned char* processed_piece, keyset* keysets, int mode);

#endif

