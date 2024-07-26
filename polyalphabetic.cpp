#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateKey(char text[], char key[]) {
    int textLen = strlen(text), keyLen = strlen(key), i, j;
    for (i = 0, j = 0; i < textLen; i++, j++) {
        if (j == keyLen) j = 0;
        key[i] = key[j];
    }
    key[i] = '\0';
}

void cipherText(char text[], char key[], int decrypt) {
    int i, shift;
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            shift = (decrypt ? -1 : 1) * (toupper(key[i]) - 'A');
            text[i] = isupper(text[i]) ? ((text[i] - 'A' + shift + 26) % 26 + 'A') : ((text[i] - 'a' + shift + 26) % 26 + 'a');
        }
    }
}

int main() {
    char text[100], key[100];
    printf("Enter the text: ");
    gets(text);
    printf("Enter the key: ");
    gets(key);
    generateKey(text, key);
    cipherText(text, key, 0);  // Encrypt
    printf("Encrypted text: %s\n", text);
    cipherText(text, key, 1);  // Decrypt
    printf("Decrypted text: %s\n", text);
    return 0;
}

