#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEY_LENGTH 256
#define ALPHABET_SIZE 26
int charToNum(char c) {
    return toupper(c) - 'A';
}
char numToChar(int num) {
    return num + 'A';
}
void encryptOneTimePad(const char *plaintext, const int *key, int keyLength, char *ciphertext) {
    int len = strlen(plaintext);

    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int shift = key[i % keyLength];
            int plaintextValue = charToNum(plaintext[i]);
            int encryptedValue = (plaintextValue + shift) % ALPHABET_SIZE;
            ciphertext[i] = numToChar(encryptedValue);
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0'; 
}


void decryptOneTimePad(const char *ciphertext, const int *key, int keyLength, char *plaintext) {
    int len = strlen(ciphertext);

    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            int shift = key[i % keyLength];
            int ciphertextValue = charToNum(ciphertext[i]);
            int decryptedValue = (ciphertextValue - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
            plaintext[i] = numToChar(decryptedValue);
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0'; 
}

int main() {
    char plaintext[] = "Meet me at the usual place.";
    int key[] = {3, 19, 5, 12}; 
    int keyLength = sizeof(key) / sizeof(key[0]);
    char ciphertext[1024];
    char decryptedtext[1024];
    encryptOneTimePad(plaintext, key, keyLength, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    decryptOneTimePad(ciphertext, key, keyLength, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

