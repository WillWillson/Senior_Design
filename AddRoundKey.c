#include <stdio.h>

void add_round_key(unsigned char r[4][4], unsigned char k[4][4]);
void print_columns(unsigned char r[4][4]);
void print_rows(unsigned char r[4][4]);

int main() {
    unsigned char r[4][4] = {{0x01, 0x02, 0x03, 0x04}, {0x05, 0x06, 0x07, 0x08}, {0x09, 0x0A, 0x0B, 0x0C}, {0x0D, 0x0E, 0x0F, 0x10}};
    unsigned char k[4][4] = {{0x10, 0x20, 0x30, 0x40}, {0x50, 0x60, 0x70, 0x80}, {0x90, 0xA0, 0xB0, 0xC0}, {0xD0, 0xE0, 0xF0, 0x01}};

    print_columns(r);

    add_round_key(r, k);

    print_columns(r);

    print_rows(r);

    return 0;
}

void add_round_key(unsigned char r[4][4], unsigned char k[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            r[i][j] = r[i][j] ^ k[i][j];
        }
    }
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