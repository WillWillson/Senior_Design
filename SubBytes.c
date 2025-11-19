#include <stdio.h>

#define ROTL8(x,shift) ((unsigned char) ((x) << (shift)) | ((x) >> (8 - (shift))))

void sub_bytes(unsigned char r[4][4], unsigned char sbox[256]);
void initialize_aes_sbox(unsigned char sbox[256], unsigned char inv_sbox[256]);
void print_columns(unsigned char r[4][4]);
void print_rows(unsigned char r[4][4]);

int main() {
    unsigned char r[4][4] = {{0x01, 0x02, 0x03, 0x04}, {0x05, 0x06, 0x07, 0x08}, {0x09, 0x0A, 0x0B, 0x0C}, {0x0D, 0x0E, 0x0F, 0x10}};

    unsigned char sbox[256], inv_sbox[256];

    print_columns(r);

    initialize_aes_sbox(sbox, inv_sbox);

    sub_bytes(r, sbox);

    print_columns(r);

    sub_bytes(r, inv_sbox);

    print_columns(r);

    return 0;
}

void sub_bytes(unsigned char r[4][4], unsigned char sbox[256]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            r[i][j] = sbox[r[i][j]];
        }
    }
}

void initialize_aes_sbox(unsigned char sbox[256], unsigned char inv_sbox[256]) {
	unsigned char p = 1, q = 1;
	
	/* loop invariant: p * q == 1 in the Galois field */
	do {
		/* multiply p by 3 */
		p = p ^ (p << 1) ^ (p & 0x80 ? 0x1B : 0);

		/* divide q by 3 (equals multiplication by 0xf6) */
		q ^= q << 1;
		q ^= q << 2;
		q ^= q << 4;
		q ^= q & 0x80 ? 0x09 : 0;

		/* compute the affine transformation */
		unsigned char xformed = q ^ ROTL8(q, 1) ^ ROTL8(q, 2) ^ ROTL8(q, 3) ^ ROTL8(q, 4);
		sbox[p] = xformed ^ 0x63;
        inv_sbox[sbox[p]] = p;
	} while (p != 1);

	/* 0 is a special case since it has no inverse */
	sbox[0] = 0x63;
    inv_sbox[0x63] = 0;
}

void print_columns(unsigned char r[4][4]) {
    printf("Column Matrix:\n");
    for (int i = 0; i < 4; i++) {
        printf("[%d, %d, %d, %d]\n", r[0][i], r[1][i], r[2][i], r[3][i]);
    }   
    printf("\n");
}

void print_rows(unsigned char r[4][4]) {
    for (int i = 0; i < 4; i++) {
        printf("[%d, %d, %d, %d]\n", r[i][0], r[i][1], r[i][2], r[i][3]);
    }
    printf("\n");
}