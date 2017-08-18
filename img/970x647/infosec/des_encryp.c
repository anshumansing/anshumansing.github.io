#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "des.h"
int initial_key[] = {57, 49,  41, 33,  25,  17,  9,
								 1, 58,  50, 42,  34,  26, 18,
								10,  2,  59, 51,  43,  35, 27,
								19, 11,   3, 60,  52,  44, 36,
								63, 55,  47, 39,  31,  23, 15,
								 7, 62,  54, 46,  38,  30, 22,
								14,  6,  61, 53,  45,  37, 29,
								21, 13,   5, 28,  20,  12,  4};

int initial_message[] =	   {58, 50, 42, 34, 26, 18, 10, 2,
										60, 52, 44, 36, 28, 20, 12, 4,
										62, 54, 46, 38, 30, 22, 14, 6,
										64, 56, 48, 40, 32, 24, 16, 8,
										57, 49, 41, 33, 25, 17,  9, 1,
										59, 51, 43, 35, 27, 19, 11, 3,
										61, 53, 45, 37, 29, 21, 13, 5,
										63, 55, 47, 39, 31, 23, 15, 7};

int key_ss[] = {-1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

int sub_key[] =    {14, 17, 11, 24,  1,  5,
								 3, 28, 15,  6, 21, 10,
								23, 19, 12,  4, 26,  8,
								16,  7, 27, 20, 13,  2,
								41, 52, 31, 37, 47, 55,
								30, 40, 51, 45, 33, 48,
								44, 49, 39, 56, 34, 53,
								46, 42, 50, 36, 29, 32};

int message_expansion[] =  {32,  1,  2,  3,  4,  5,
							 4,  5,  6,  7,  8,  9,
							 8,  9, 10, 11, 12, 13,
							12, 13, 14, 15, 16, 17,
							16, 17, 18, 19, 20, 21,
							20, 21, 22, 23, 24, 25,
							24, 25, 26, 27, 28, 29,
							28, 29, 30, 31, 32,  1};

int S1[] = {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
			 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
			 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
			15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13};

int S2[] = {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
			 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
			 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
			13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9};

int S3[] = {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
			13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
			13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
			 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12};

int S4[] = { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
			13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
			10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
			 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14};

int S5[] = { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
			14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
			 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
			11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3};

int S6[] = {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
			10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
			 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
			 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13};

int S7[] = { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
			13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
			 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
			 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12};

int S8[] = {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
			 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
			 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
			 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11};

int rightsub_message[] =    {16,  7, 20, 21,
									29, 12, 28, 17,
									 1, 15, 23, 26,
									 5, 18, 31, 10,
									 2,  8, 24, 14,
									32, 27,  3,  9,
									19, 13, 30,  6,
									22, 11,  4, 25};

int final_message[] =  {40,  8, 48, 16, 56, 24, 64, 32,
									39,  7, 47, 15, 55, 23, 63, 31,
									38,  6, 46, 14, 54, 22, 62, 30,
									37,  5, 45, 13, 53, 21, 61, 29,
									36,  4, 44, 12, 52, 20, 60, 28,
									35,  3, 43, 11, 51, 19, 59, 27,
									34,  2, 42, 10, 50, 18, 58, 26,
									33,  1, 41,  9, 49, 17, 57, 25};

void chartobin(char input) {
	for (int i=7; i>0; i--) {
		if (input & (1 << i)) {
			printf("1");
		} else {
			printf("0");
		}
	}
}

void generate_key(unsigned char* key) {
	int i;
	for (i=0; i<8; i++) {
		key[i] = rand()%255;
	}
}

void print_keyset(keyset keyset){
	int i=0;
	printf("K: \n");
	while (i<8) {
		printf("%02X : ", keyset.k[i]);
		chartobin(keyset.k[i]);
		printf("\n");
		i++;
	}
	printf("C: \n");
	i=0;
	while (i<4) {
		printf("%02X : ", keyset.c[i]);
		chartobin(keyset.c[i]);
		printf("\n");
		i++;
	}
	printf("D: \n");
	i=0;
	while (i<4) {
		printf("%02X : ", keyset.d[i]);
		chartobin(keyset.d[i]);
		printf("\n");
		i++;
	}
	printf("\n");
}

void generate_sub_keys(unsigned char* mainkey, keyset* keysets) {
	int i, j;
	int ss; //Shift Size
	unsigned char shiftbyte, first_shift, second_shift, third_shift, fourth_shift;

	for (i=0; i<8; i++) {
		keysets[0].k[i] = 0;
	}

	for (i=0; i<56; i++) {
		ss = initial_key[i];
		shiftbyte = 0x80 >> ((ss - 1)%8);
		shiftbyte &= mainkey[(ss - 1)/8];
		shiftbyte <<= ((ss - 1)%8);

		keysets[0].k[i/8] |= (shiftbyte >> i%8);
	}

	for (i=0; i<3; i++) {
		keysets[0].c[i] = keysets[0].k[i];
	}

	keysets[0].c[3] = keysets[0].k[3] & 0xF0;

	for (i=0; i<3; i++) {
		keysets[0].d[i] = (keysets[0].k[i+3] & 0x0F) << 4;
		keysets[0].d[i] |= (keysets[0].k[i+4] & 0xF0) >> 4;
	}

	keysets[0].d[3] = (keysets[0].k[6] & 0x0F) << 4;


	for (i=1; i<17; i++) {
		for (j=0; j<4; j++) {
			keysets[i].c[j] = keysets[i-1].c[j];
			keysets[i].d[j] = keysets[i-1].d[j];
		}

		ss = key_ss[i];
		if (ss == 1){
			shiftbyte = 0x80;
		} else {
			shiftbyte = 0xC0;
		}

		// Process C
		first_shift = shiftbyte & keysets[i].c[0];
		second_shift = shiftbyte & keysets[i].c[1];
		third_shift = shiftbyte & keysets[i].c[2];
		fourth_shift = shiftbyte & keysets[i].c[3];

		keysets[i].c[0] <<= ss;
		keysets[i].c[0] |= (second_shift >> (8 - ss));

		keysets[i].c[1] <<= ss;
		keysets[i].c[1] |= (third_shift >> (8 - ss));

		keysets[i].c[2] <<= ss;
		keysets[i].c[2] |= (fourth_shift >> (8 - ss));

		keysets[i].c[3] <<= ss;
		keysets[i].c[3] |= (first_shift >> (4 - ss));

		// Process D
		first_shift = shiftbyte & keysets[i].d[0];
		second_shift = shiftbyte & keysets[i].d[1];
		third_shift = shiftbyte & keysets[i].d[2];
		fourth_shift = shiftbyte & keysets[i].d[3];

		keysets[i].d[0] <<= ss;
		keysets[i].d[0] |= (second_shift >> (8 - ss));

		keysets[i].d[1] <<= ss;
		keysets[i].d[1] |= (third_shift >> (8 - ss));

		keysets[i].d[2] <<= ss;
		keysets[i].d[2] |= (fourth_shift >> (8 - ss));

		keysets[i].d[3] <<= ss;
		keysets[i].d[3] |= (first_shift >> (4 - ss));

		for (j=0; j<48; j++) {
			ss = sub_key[j];
			if (ss <= 28) {
				shiftbyte = 0x80 >> ((ss - 1)%8);
				shiftbyte &= keysets[i].c[(ss - 1)/8];
				shiftbyte <<= ((ss - 1)%8);
			} else {
				shiftbyte = 0x80 >> ((ss - 29)%8);
				shiftbyte &= keysets[i].d[(ss - 29)/8];
				shiftbyte <<= ((ss - 29)%8);
			}

			keysets[i].k[j/8] |= (shiftbyte >> j%8);
		}
	}
}

void process_message(unsigned char* message_piece, unsigned char* processed_piece, keyset* keysets, int mode) {
	int i, k;
	int ss;
	unsigned char shiftbyte;

	unsigned char initial_permutation[8];
	memset(initial_permutation, 0, 8);
	memset(processed_piece, 0, 8);

	for (i=0; i<64; i++) {
		ss = initial_message[i];
		shiftbyte = 0x80 >> ((ss - 1)%8);
		shiftbyte &= message_piece[(ss - 1)/8];
		shiftbyte <<= ((ss - 1)%8);

		initial_permutation[i/8] |= (shiftbyte >> i%8);
	}

	unsigned char l[4], r[4];
	for (i=0; i<4; i++) {
		l[i] = initial_permutation[i];
		r[i] = initial_permutation[i+4];
	}

	unsigned char ln[4], rn[4], er[6], ser[4];

	int key_index;
	for (k=1; k<=16; k++) {
		memcpy(ln, r, 4);

		memset(er, 0, 6);

		for (i=0; i<48; i++) {
			ss = message_expansion[i];
			shiftbyte = 0x80 >> ((ss - 1)%8);
			shiftbyte &= r[(ss - 1)/8];
			shiftbyte <<= ((ss - 1)%8);

			er[i/8] |= (shiftbyte >> i%8);
		}

		if (mode == DECRYPTION_MODE) {
			key_index = 17 - k;
		} else {
			key_index = k;
		}

		for (i=0; i<6; i++) {
			er[i] ^= keysets[key_index].k[i];
		}

		unsigned char row, column;

		for (i=0; i<4; i++) {
			ser[i] = 0;
		}

		// 0000 0000 0000 0000 0000 0000
		// rccc crrc cccr rccc crrc cccr

		// Byte 1
		row = 0;
		row |= ((er[0] & 0x80) >> 6);
		row |= ((er[0] & 0x04) >> 2);

		column = 0;
		column |= ((er[0] & 0x78) >> 3);

		ser[0] |= ((unsigned char)S1[row*16+column] << 4);

		row = 0;
		row |= (er[0] & 0x02);
		row |= ((er[1] & 0x10) >> 4);

		column = 0;
		column |= ((er[0] & 0x01) << 3);
		column |= ((er[1] & 0xE0) >> 5);

		ser[0] |= (unsigned char)S2[row*16+column];

		// Byte 2
		row = 0;
		row |= ((er[1] & 0x08) >> 2);
		row |= ((er[2] & 0x40) >> 6);

		column = 0;
		column |= ((er[1] & 0x07) << 1);
		column |= ((er[2] & 0x80) >> 7);

		ser[1] |= ((unsigned char)S3[row*16+column] << 4);

		row = 0;
		row |= ((er[2] & 0x20) >> 4);
		row |= (er[2] & 0x01);

		column = 0;
		column |= ((er[2] & 0x1E) >> 1);

		ser[1] |= (unsigned char)S4[row*16+column];

		// Byte 3
		row = 0;
		row |= ((er[3] & 0x80) >> 6);
		row |= ((er[3] & 0x04) >> 2);

		column = 0;
		column |= ((er[3] & 0x78) >> 3);

		ser[2] |= ((unsigned char)S5[row*16+column] << 4);

		row = 0;
		row |= (er[3] & 0x02);
		row |= ((er[4] & 0x10) >> 4);

		column = 0;
		column |= ((er[3] & 0x01) << 3);
		column |= ((er[4] & 0xE0) >> 5);

		ser[2] |= (unsigned char)S6[row*16+column];

		// Byte 4
		row = 0;
		row |= ((er[4] & 0x08) >> 2);
		row |= ((er[5] & 0x40) >> 6);

		column = 0;
		column |= ((er[4] & 0x07) << 1);
		column |= ((er[5] & 0x80) >> 7);

		ser[3] |= ((unsigned char)S7[row*16+column] << 4);

		row = 0;
		row |= ((er[5] & 0x20) >> 4);
		row |= (er[5] & 0x01);

		column = 0;
		column |= ((er[5] & 0x1E) >> 1);

		ser[3] |= (unsigned char)S8[row*16+column];

		for (i=0; i<4; i++) {
			rn[i] = 0;
		}

		for (i=0; i<32; i++) {
			ss = rightsub_message[i];
			shiftbyte = 0x80 >> ((ss - 1)%8);
			shiftbyte &= ser[(ss - 1)/8];
			shiftbyte <<= ((ss - 1)%8);

			rn[i/8] |= (shiftbyte >> i%8);
		}

		for (i=0; i<4; i++) {
			rn[i] ^= l[i];
		}

		for (i=0; i<4; i++) {
			l[i] = ln[i];
			r[i] = rn[i];
		}
	}

	unsigned char pre_end[8];
	for (i=0; i<4; i++) {
		pre_end[i] = r[i];
		pre_end[4+i] = l[i];
	}

	for (i=0; i<64; i++) {
		ss = final_message[i];
		shiftbyte = 0x80 >> ((ss - 1)%8);
		shiftbyte &= pre_end[(ss - 1)/8];
		shiftbyte <<= ((ss - 1)%8);

		processed_piece[i/8] |= (shiftbyte >> i%8);
	}
}
