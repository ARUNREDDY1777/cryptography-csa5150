#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define DES_KEY_SIZE 8    
#define DES_BLOCK_SIZE 8  
#define NUM_ROUNDS 16     
void desDecrypt(uint8_t *input, uint8_t *output, uint8_t key[DES_KEY_SIZE]);
void generateSubkeys(uint8_t *key, uint8_t subkeys[NUM_ROUNDS][DES_KEY_SIZE]);
void permute(uint8_t *input, uint8_t *output, const uint8_t *table, int size);
void shiftLeft(uint8_t *key, int shifts);
void xorBlocks(uint8_t *a, uint8_t *b, uint8_t *result, int size);

int main() {
    uint8_t key[DES_KEY_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};  
    uint8_t ciphertext[DES_BLOCK_SIZE] = {0x3D, 0xC1, 0xE1, 0xA0, 0x3C, 0x91, 0xAC, 0x30};  
    uint8_t plaintext[DES_BLOCK_SIZE];
    desDecrypt(ciphertext, plaintext, key);

    printf("Decrypted text: ");
    for (int i = 0; i < DES_BLOCK_SIZE; i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");

    return 0;
}
void desDecrypt(uint8_t *input, uint8_t *output, uint8_t key[DES_KEY_SIZE]) {
    uint8_t subkeys[NUM_ROUNDS][DES_KEY_SIZE];
    generateSubkeys(key, subkeys);
    for (int round = NUM_ROUNDS - 1; round >= 0; round--) {
    }
}

void generateSubkeys(uint8_t *key, uint8_t subkeys[NUM_ROUNDS][DES_KEY_SIZE]) {
    for (int i = 0; i < NUM_ROUNDS; i++) {
        memcpy(subkeys[i], key, DES_KEY_SIZE);
    }
}
void permute(uint8_t *input, uint8_t *output, const uint8_t *table, int size) {
}
void shiftLeft(uint8_t *key, int shifts) {
}
void xorBlocks(uint8_t *a, uint8_t *b, uint8_t *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] ^ b[i];
    }
}

