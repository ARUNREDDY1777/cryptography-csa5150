#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2
#define ALPHABET_SIZE 26
int charToNum(char c) {
    return c - 'A';
}
char numToChar(int num) {
    return num + 'A';
}
void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void multiplyMatrices(int a[MATRIX_SIZE][MATRIX_SIZE], int b[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
            result[i][j] %= ALPHABET_SIZE;
        }
    }
}
int inverseMod26(int a) {
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if ((a * i) % ALPHABET_SIZE == 1) {
            return i;
        }
    }
    return -1; 
}

void inverseMatrix2x2(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int determinant = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % ALPHABET_SIZE;
    determinant = (determinant + ALPHABET_SIZE) % ALPHABET_SIZE; // Handle negative determinant

    int invDet = inverseMod26(determinant);
    if (invDet == -1) {
        printf("Matrix is not invertible\n");
        exit(1);
    }

    inverse[0][0] = (matrix[1][1] * invDet) % ALPHABET_SIZE;
    inverse[0][1] = (-matrix[0][1] * invDet) % ALPHABET_SIZE;
    inverse[1][0] = (-matrix[1][0] * invDet) % ALPHABET_SIZE;
    inverse[1][1] = (matrix[0][0] * invDet) % ALPHABET_SIZE;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (inverse[i][j] < 0) {
                inverse[i][j] += ALPHABET_SIZE;
            }
        }
    }
}
void decryptHillCipher(int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext, char *plaintext) {
    int inverseKeyMatrix[MATRIX_SIZE][MATRIX_SIZE];
    inverseMatrix2x2(keyMatrix, inverseKeyMatrix);

    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += MATRIX_SIZE) {
        int cipherBlock[MATRIX_SIZE][MATRIX_SIZE];
        int plainBlock[MATRIX_SIZE][MATRIX_SIZE];

        for (int j = 0; j < MATRIX_SIZE; j++) {
            cipherBlock[j][0] = charToNum(ciphertext[i + j]);
        }
        multiplyMatrices(inverseKeyMatrix, cipherBlock, plainBlock);

        for (int j = 0; j < MATRIX_SIZE; j++) {
            plaintext[i + j] = numToChar(plainBlock[j][0]);
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char plaintext[] = "HI";
    char ciphertext[] = "BK"; 
    int plaintextMatrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {charToNum(plaintext[0]), charToNum(plaintext[1])},
        {0, 0} 
    };
    int ciphertextMatrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {charToNum(ciphertext[0]), charToNum(ciphertext[1])},
        {0, 0} 
    };
    int keyMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int tempMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int inversePlaintextMatrix[MATRIX_SIZE][MATRIX_SIZE];

    inverseMatrix2x2(plaintextMatrix, inversePlaintextMatrix);
    multiplyMatrices(ciphertextMatrix, inversePlaintextMatrix, keyMatrix);
    printf("Key Matrix:\n");
    printMatrix(keyMatrix);
    char decryptedMessage[1024];
    decryptHillCipher(keyMatrix, ciphertext, decryptedMessage);
    printf("Decrypted message: %s\n", decryptedMessage);

    return 0;
}

