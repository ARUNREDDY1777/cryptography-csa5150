#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/aes.h>

// Define constants
#define BLOCK_SIZE 16 // AES block size in bytes

// Function prototypes
void aes_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, const uint8_t *key, size_t length, const char *mode);
void aes_decrypt(const uint8_t *ciphertext, uint8_t *plaintext, const uint8_t *key, size_t length, const char *mode);
void print_hex(const char *label, const uint8_t *data, size_t length);
void pad_plaintext(uint8_t *data, size_t *length);
void unpad_plaintext(uint8_t *data, size_t *length);

int main() {
    // Example AES key (16 bytes for AES-128)
    uint8_t key[AES_BLOCK_SIZE] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
    };
    
    // Example plaintext (needs padding for modes except CFB)
    uint8_t plaintext[BLOCK_SIZE * 2 + 4] = "Hello, World! AES!";
    size_t length = strlen((char *)plaintext);

    // Pad plaintext
    pad_plaintext(plaintext, &length);
    
    // Arrays for ciphertext and decrypted text
    uint8_t ciphertext[BLOCK_SIZE * 2 + 4];
    uint8_t decrypted[BLOCK_SIZE * 2 + 4];
    
    // Encrypt and Decrypt in ECB mode
    aes_encrypt(plaintext, ciphertext, key, length, "ECB");
    print_hex("ECB Ciphertext", ciphertext, length);
    aes_decrypt(ciphertext, decrypted, key, length, "ECB");
    unpad_plaintext(decrypted, &length);
    print_hex("ECB Decrypted", decrypted, length);
    
    // Encrypt and Decrypt in CBC mode
    uint8_t iv[AES_BLOCK_SIZE] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };
    aes_encrypt(plaintext, ciphertext, key, length, "CBC");
    print_hex("CBC Ciphertext", ciphertext, length);
    aes_decrypt(ciphertext, decrypted, key, length, "CBC");
    unpad_plaintext(decrypted, &length);
    print_hex("CBC Decrypted", decrypted, length);

    // Encrypt and Decrypt in CFB mode
    aes_encrypt(plaintext, ciphertext, key, length, "CFB");
    print_hex("CFB Ciphertext", ciphertext, length);
    aes_decrypt(ciphertext, decrypted, key, length, "CFB");
    unpad_plaintext(decrypted, &length);
    print_hex("CFB Decrypted", decrypted, length);

    return 0;
}

// Encrypt using AES in ECB, CBC, or CFB mode
void aes_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, const uint8_t *key, size_t length, const char *mode) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    if (strcmp(mode, "ECB") == 0) {
        for (size_t i = 0; i < length; i += BLOCK_SIZE) {
            AES_encrypt(plaintext + i, ciphertext + i, &aes_key);
        }
    } else if (strcmp(mode, "CBC") == 0) {
        AES_cbc_encrypt(plaintext, ciphertext, length, &aes_key, (unsigned char *)key, AES_ENCRYPT);
    } else if (strcmp(mode, "CFB") == 0) {
        AES_cfb128_encrypt(plaintext, ciphertext, length, &aes_key, (unsigned char *)key, NULL, AES_ENCRYPT);
    }
}

// Decrypt using AES in ECB, CBC, or CFB mode
void aes_decrypt(const uint8_t *ciphertext, uint8_t *plaintext, const uint8_t *key, size_t length, const char *mode) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);
    if (strcmp(mode, "ECB") == 0) {
        for (size_t i = 0; i < length; i += BLOCK_SIZE) {
            AES_decrypt(ciphertext + i, plaintext + i, &aes_key);
        }
    } else if (strcmp(mode, "CBC") == 0) {
        AES_cbc_encrypt(ciphertext, plaintext, length, &aes_key, (unsigned char *)key, AES_DECRYPT);
    } else if (strcmp(mode, "CFB") == 0) {
        AES_cfb128_encrypt(ciphertext, plaintext, length, &aes_key, (unsigned char *)key, NULL, AES_DECRYPT);
    }
}

// Pad plaintext to be a multiple of BLOCK_SIZE
void pad_plaintext(uint8_t *data, size_t *length) {
    size_t padding = BLOCK_SIZE - (*length % BLOCK_SIZE);
    memset(data + *length, padding, padding);
    *length += padding;
}

// Unpad plaintext
void unpad_plaintext(uint8_t *data, size_t *length) {
    size_t padding = data[*length - 1];
    *length -= padding;
}

// Print hex representation of data
void print_hex(const char *label, const uint8_t *data, size_t length) {
    printf("%s: ", label);
    for (size_t i = 0; i < length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

