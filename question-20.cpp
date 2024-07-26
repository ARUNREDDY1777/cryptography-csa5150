#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/aes.h>

// Define constants
#define BLOCK_SIZE 16 // AES block size in bytes

// Function prototypes
void aes_ecb_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, const uint8_t *key, size_t length);
void aes_ecb_decrypt(const uint8_t *ciphertext, uint8_t *plaintext, const uint8_t *key, size_t length);
void print_hex(const char *label, const uint8_t *data, size_t length);

int main() {
    // Example AES key (16 bytes for AES-128)
    uint8_t key[AES_BLOCK_SIZE] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
    };
    
    // Example plaintext (must be a multiple of BLOCK_SIZE)
    uint8_t plaintext[BLOCK_SIZE * 2] = "Hello, World! AES!";
    uint8_t ciphertext[BLOCK_SIZE * 2];
    uint8_t decrypted[BLOCK_SIZE * 2];
    
    // Encrypt the plaintext
    aes_ecb_encrypt(plaintext, ciphertext, key, sizeof(plaintext));
    print_hex("Ciphertext", ciphertext, sizeof(ciphertext));
    
    // Introduce an error in the ciphertext
    ciphertext[0] ^= 0xFF; // Flip the first byte to simulate an error
    
    // Decrypt the ciphertext
    aes_ecb_decrypt(ciphertext, decrypted, key, sizeof(ciphertext));
    print_hex("Decrypted", decrypted, sizeof(decrypted));

    return 0;
}

// Encrypt using AES in ECB mode
void aes_ecb_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, const uint8_t *key, size_t length) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        AES_encrypt(plaintext + i, ciphertext + i, &aes_key);
    }
}

// Decrypt using AES in ECB mode
void aes_ecb_decrypt(const uint8_t *ciphertext, uint8_t *plaintext, const uint8_t *key, size_t length) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        AES_decrypt(ciphertext + i, plaintext + i, &aes_key);
    }
}

// Print hex representation of data
void print_hex(const char *label, const uint8_t *data, size_t length) {
    printf("%s: ", label);
    for (size_t i = 0; i < length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

