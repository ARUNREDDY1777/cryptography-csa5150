#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DES_KEY_SIZE 8     
#define HALF_KEY_SIZE 28   
#define SUBKEY_SIZE 6      
void permuteKey(const uint8_t *key, uint8_t *permutedKey);
void shiftLeft(uint8_t *key, int shifts);
void generateSubkeys(const uint8_t *key, uint8_t subkeys[16][SUBKEY_SIZE]);
static const int PC1[] = {
};
static const int SHIFT_SCHEDULE[] = {1, 1, 2, 2, 2, 2, 1, 1,
                                     2, 2, 2, 2, 1, 1, 2, 2};
static const int PC2[] = {
};

int main() {
    uint8_t key[DES_KEY_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};  // Example key
    uint8_t subkeys[16][SUBKEY_SIZE];
    generateSubkeys(key, subkeys);
    printf("Generated Subkeys:\n");
    for (int i = 0; i < 16; i++) {
        printf("Subkey %d: ", i + 1);
        for (int j = 0; j < SUBKEY_SIZE; j++) {
            printf("%02X ", subkeys[i][j]);
        }
        printf("\n");
    }

    return 0;
}
void permuteKey(const uint8_t *key, uint8_t *permutedKey) {
}
void shiftLeft(uint8_t *key, int shifts) {
}
void generateSubkeys(const uint8_t *key, uint8_t subkeys[16][SUBKEY_SIZE]) {
    uint8_t permutedKey[DES_KEY_SIZE] = {0};
    uint8_t C[HALF_KEY_SIZE / 8] = {0};
    uint8_t D[HALF_KEY_SIZE / 8] = {0};
    permuteKey(key, permutedKey);
    memcpy(C, permutedKey, HALF_KEY_SIZE / 8);
    memcpy(D, permutedKey + HALF_KEY_SIZE / 8, HALF_KEY_SIZE / 8);
    for (int i = 0; i < 16; i++) {
        shiftLeft(C, SHIFT_SCHEDULE[i]);
        shiftLeft(D, SHIFT_SCHEDULE[i]);
        for (int j = 0; j < SUBKEY_SIZE; j++) {
            subkeys[i][j] = 
		}
    }
}

