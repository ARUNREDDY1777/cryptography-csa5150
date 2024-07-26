#include <stdio.h>
#include <stdint.h>
#include <string.h>
//#include <openssl/des.h>

// Define constants
#define BLOCK_SIZE 8 // DES block size in bytes

// Function prototypes
void des3_cbc_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, const uint8_t *key, const uint8_t *iv, size_t length);
void print_hex(const char *label, const uint8_t *data, size_t length);

int main() {
    // Example key (24 bytes for 3DES)
    uint8_t key[24] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, // Key1
        0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, // Key2
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77  // Key3
    };
    
    // Example IV (8 bytes for DES)
    uint8_t iv[BLOCK_SIZE] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
    };
    
    // Example plaintext (must be a multiple of BLOCK_SIZE)
    uint8_t plaintext[BLOCK_SIZE] = "ABCDEFGH";
    uint8_t ciphertext[BLOCK_SIZE];
    
    // Encrypt the plaintext
    des3_cbc_encrypt(plaintext, ciphertext, key, iv, BLOCK_SIZE);

    // Print the results
    print_hex("Ciphertext", ciphertext, BLOCK_SIZE);

    return 0;
}

// Encrypt using 3DES in CBC mode
void des3_cbc_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, const uint8_t *key, const uint8_t *iv, size_t length) {
    DES_key_schedule ks1, ks2, ks3;
    DES_cblock key1, key2, key3, ivec;
    DES_cblock block;
    
    // Set the keys and IV
    memcpy(key1, key, 8);
    memcpy(key2, key + 8, 8);
    memcpy(key3, key + 16, 8);
    memcpy(ivec, iv, 8);
    
    // Set the DES key schedules
    DES_set_key((DES_cblock *)key1, &ks1);
    DES_set_key((DES_cblock *)key2, &ks2);
    DES_set_key((DES_cblock *)key3, &ks3);
    
    // Encrypt in CBC mode
    DES_ncbc_encrypt(plaintext, ciphertext, length, &ks1, &ks2, &ks3, &ivec, DES_ENCRYPT);
}

// Print hex representation of data
void print_hex(const char *label, const uint8_t *data, size_t length) {
    printf("%s: ", label);
    for (size_t i = 0; i < length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

