#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
void initializeMatrix(char matrix[SIZE][SIZE]) {
    char predefinedMatrix[SIZE][SIZE] = {
        {'M', 'F', 'H', 'I', 'J'},
        {'K', 'U', 'N', 'O', 'P'},
        {'Q', 'Z', 'V', 'W', 'X'},
        {'Y', 'E', 'L', 'A', 'R'},
        {'G', 'D', 'S', 'T', 'B'}
    };

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = predefinedMatrix[i][j];
        }
    }
}


void searchInMatrix(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptPlayfair(char plaintext[], char matrix[SIZE][SIZE], char ciphertext[]) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        searchInMatrix(matrix, toupper(plaintext[i]), &row1, &col1);
        searchInMatrix(matrix, toupper(plaintext[i + 1]), &row2, &col2);

        if (row1 == row2) {
            ciphertext[i] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[i] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}
void decryptPlayfair(char ciphertext[], char matrix[SIZE][SIZE], char plaintext[]) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        searchInMatrix(matrix, toupper(ciphertext[i]), &row1, &col1);
        searchInMatrix(matrix, toupper(ciphertext[i + 1]), &row2, &col2);

        if (row1 == row2) {
            plaintext[i] = matrix[row1][(col1 + SIZE - 1) % SIZE];
            plaintext[i + 1] = matrix[row2][(col2 + SIZE - 1) % SIZE];
        } else if (col1 == col2) {
            plaintext[i] = matrix[(row1 + SIZE - 1) % SIZE][col1];
            plaintext[i + 1] = matrix[(row2 + SIZE - 1) % SIZE][col2];
        } else {

            plaintext[i] = matrix[row1][col2];
            plaintext[i + 1] = matrix[row2][col1];
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char matrix[SIZE][SIZE];
    char plaintext[] = "HELLO";
    char ciphertext[1024];
    char decryptedtext[1024];
    initializeMatrix(matrix);

    printf("Playfair Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    encryptPlayfair(plaintext, matrix, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    decryptPlayfair(ciphertext, matrix, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

