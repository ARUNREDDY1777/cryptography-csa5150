#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 2
#define ALPHABET_SIZE 26
int charToNum(char c) {
    return toupper(c) - 'A';
}
char numToChar(int num) {
    return num + 'A';
}
void prepareMessage(char *message, char *preparedMessage) {
    int j = 0;
    for (int i = 0; i < strlen(message); i++) {
        if (isalpha(message[i])) {
            preparedMessage[j++] = toupper(message[i]);
        }
    }
    preparedMessage[j] = '\0';
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
void encryptHillCipher(char *message, int key[MATRIX_SIZE][MATRIX_SIZE], char *encryptedMessage) {
    int len = strlen(message);
    int paddedLen = (len + MATRIX_SIZE - 1) / MATRIX_SIZE * MATRIX_SIZE;
    int messageMatrix[paddedLen][MATRIX_SIZE];
    int encryptedMatrix[paddedLen][MATRIX_SIZE];
    int keyMatrix[MATRIX_SIZE][MATRIX_SIZE] = { {94 % ALPHABET_SIZE, 57 % ALPHABET_SIZE}, {0, 0} };
    for (int i = 0; i < len; i++) {
        messageMatrix[i / MATRIX_SIZE][i % MATRIX_SIZE] = charToNum(message[i]);
    }
    for (int i = len; i < paddedLen; i++) {
        messageMatrix[i / MATRIX_SIZE][i % MATRIX_SIZE] = 0; 
    }
    for (int i = 0; i < paddedLen / MATRIX_SIZE; i++) {
        multiplyMatrices(keyMatrix, messageMatrix + i * MATRIX_SIZE, encryptedMatrix + i * MATRIX_SIZE);
    }
    for (int i = 0; i < paddedLen; i++) {
        encryptedMessage[i] = numToChar(encryptedMatrix[i / MATRIX_SIZE][i % MATRIX_SIZE]);
    }
    encryptedMessage[paddedLen] = '\0';
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight o'clock";
    char preparedMessage[1024];
    char encryptedMessage[1024];
    int key[MATRIX_SIZE][MATRIX_SIZE] = { {94 % ALPHABET_SIZE, 57 % ALPHABET_SIZE}, {0, 0} };
    prepareMessage(message, preparedMessage);
    encryptHillCipher(preparedMessage, key, encryptedMessage);
    printf("Encrypted message: %s\n", encryptedMessage);

    return 0;
}

