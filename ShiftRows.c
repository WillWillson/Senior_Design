#include <stdio.h>

// method declaration
void shift_rows(unsigned char r[8][4]);
void inv_shift_rows(unsigned char r[8][4]);
void print_columns(unsigned char r[8][4]);

int DEBUG = 1;

int main() {

    unsigned char r[8][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}, {17, 18, 19, 20}, {21, 22, 23, 24}, {25, 26, 27, 28}, {29, 30, 31, 32}};

    if (DEBUG) {
        print_columns(r);
    }

    shift_rows(r);

    if (DEBUG) {
        print_columns(r);
    }

    inv_shift_rows(r);

    if (DEBUG) {
        print_columns(r);
    }

    return 0;

}

void shift_rows(unsigned char r[8][4]) {
    unsigned char a[8][4];

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            a[i][j] = r[(j + i) % 8][j];
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            r[i][j] = a[i][j];
        }
    }
    
}

void inv_shift_rows(unsigned char r[8][4]) {
    unsigned char a[8][4];

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            a[i][j] = r[(i - j + 8) % 8][j];
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            r[i][j] = a[i][j];
        }
    }
    
}

void print_columns(unsigned char r[8][4]) {
    printf("Column Matrix:\n");
    for (int i = 0; i < 4; i++) {
        printf("[%d, %d, %d, %d, %d, %d, %d, %d]\n", r[0][i], r[1][i], r[2][i], r[3][i], r[4][i], r[5][i], r[6][i], r[7][i]);
    }   
    printf("\n");
}

void print_rows(unsigned char r[8][4]) {
    for (int i = 0; i < 8; i++) {
        printf("[%d, %d, %d, %d]\n", r[i][0], r[i][1], r[i][2], r[i][3]);
    }
    printf("\n");
}