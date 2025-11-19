#include <stdio.h>

#define ROTL8(x,shift) ((unsigned char) ((x) << (shift)) | ((x) >> (8 - (shift))))

void initialize_aes_sbox(unsigned char sbox[256]);
void rotate_bytes(unsigned char r[4]);
void KeyExpansion(unsigned char key[4][4], unsigned char sbox[256], unsigned char roundkeys[11][4][4]);

int main() {

    unsigned char sbox[256];

    unsigned char roundkeys[11][4][4];

    initialize_aes_sbox(sbox);

    unsigned char cipher_key[4][4] = {{0x01, 0x02, 0x03, 0x04}, {0x05, 0x06, 0x07, 0x08}, {0x09, 0x0A, 0x0B, 0x0C}, {0x0D, 0x0E, 0x0F, 0x10}};

    KeyExpansion(cipher_key, sbox, roundkeys);

    return 0;
}


void initialize_aes_sbox(unsigned char sbox[256]) {
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
	} while (p != 1);

	/* 0 is a special case since it has no inverse */
	sbox[0] = 0x63;
}

void rotate_bytes(unsigned char r[4]) {
    unsigned char temp = r[0];

    for (int i = 0; i < 3; i++) {
        r[i] = r[i+1];
    }

    r[4] = temp;
}
// DEFINITIONS

/*
    Nr == number of rounds (does not include the +1 from the initial round)
    Nb == number of columns in the block (4 for 128 bit, 6 for 192 bit, and 8 for 256 bit)
    Nk == number of columns in the key (4 for 128 bit, 6 for 192 bit, and 8 for 256 bit)
    Rcon[i] == (RC(i), '00', '00', '00')
    RC(i) == 0x01 << (i - 1)
*/

void KeyExpansion(unsigned char key[4][4], unsigned char sbox[256], unsigned char roundkeys[11][4][4]) { 

    unsigned char w[44][4];

    // sets the first 4 bytes (first 'word') of the w array to be the original key
    // original key is made up of 16 bytes (for 128 bit keys), 16 bytes = 4 words
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {     // this is the 'w[i] = (Key[4*i],Key[4*i+1],Key[4*i+2],Key[4*i+3]);' part
            w[i][j] = key[i][j];          // first 4 entries of the 'w' array are the 4 words that make up the OG key
        }
    }

    for(int i = 4; i < 44; i++) {
        unsigned char temp[4]; 
        
        for (int j = 0; j < 4; j++) {
            temp[j] = w[i - 1][j];        // temp = w[i - 1];
        }

        if ((i % 4) == 0) {
            // temp = SubByte(RotByte(temp)) ^ Rcon[i / Nk];
            rotate_bytes(temp);               // RotBytes(temp)
            for (int i = 0; i < 4; i++) {  
                temp[i] = sbox[temp[i]];      // SubBytes(RotBytes(temp))
            }
            temp[0] = temp[0] ^ (0x01 << ((i % 4) - 1));    // SubBytes(RotBytes(temp)) ^ Rcon[i / Nk]
        }

        // w[i] = w[i - Nk] ^ temp;
        for (int j = 0; j < 4; j++) {
            w[i][j] = w[i - 4][j] ^ temp[j];
        }
    }

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                roundkeys[i][j][k] = w[4*i+j][j];
            }
        }
    }


}

// ok time to figure out wtf this is on about

/*
    The expanded key is a linear array of 'words' (4 bytes back to back, i.e. 0x12,34,56,78)
        -- I'm turning this into an 44x4 array of bytes (44 arrays, 4 bytes in each array)

    Key is a 4x4 array of bytes
        -- this makes for 16 bytes <=> 128 bits

    Assume 128 bit key
        -- this makes for 16 bytes in this key size
        -- 11 round keys are necessary
*/

// unmodified pseudocode of the keyexpansion algorithm from NIST
//      for Nk <= 6 (i.e. key size 128 or 192)

// KeyExpansion(byte Key[4*Nk] word w[Nb*(Nr+1)]) {
//     for(i = 0; i < Nk; i++)
//         w[i] = (Key[4*i],Key[4*i+1],Key[4*i+2],Key[4*i+3]);
//     for(i = Nk; i < Nb * (Nr + 1); i++) {
//         temp = w[i - 1];
//         if (i % Nk == 0)
//             temp = SubByte(RotByte(temp)) ^ Rcon[i / Nk];
//         w[i] = w[i - Nk] ^ temp;
//     }
// }