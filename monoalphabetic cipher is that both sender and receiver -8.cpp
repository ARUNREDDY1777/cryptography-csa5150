#include <stdio.h>
#include <string.h>
#include <ctype.h>
void generateCipher(char keyword[], char cipher[]) {
    int used[26] = {0};
    int idx = 0;
    for (int i = 0; keyword[i] != '\0'; i++) {
        if (isalpha(keyword[i])) {
            char ch = toupper(keyword[i]);
            if (!used[ch - 'A']) {
                cipher[idx++] = ch;
                used[ch - 'A'] = 1;
            }
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher[idx++] = ch;
        }
    }

    cipher[idx] = '\0'; 
}

void encrypt(char plaintext[], char cipher[], char encrypted[]) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            encrypted[i] = cipher[ch - 'A'];
        } else {
            encrypted[i] = plaintext[i];
        }
    }
    encrypted[strlen(plaintext)] = '\0'; 
}
void decrypt(char ciphertext[], char cipher[], char decrypted[]) {
    char reverseCipher[26];
    for (int i = 0; i < 26; i++) {
        reverseCipher[cipher[i] - 'A'] = 'A' + i;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]);
            decrypted[i] = reverseCipher[ch - 'A'];
        } else {
            decrypted[i] = ciphertext[i];
        }
    }
    decrypted[strlen(ciphertext)] = '\0'; 
}

int main() {
    char keyword[100], plaintext[100], encrypted[100], decrypted[100];
    char cipher[27];

    printf("Enter the keyword: ");
    gets(keyword);
    generateCipher(keyword, cipher);

    printf("Generated cipher sequence: %s\n", cipher);

    printf("Enter the plaintext: ");
    gets(plaintext);
    encrypt(plaintext, cipher, encrypted);
    printf("Encrypted text: %s\n", encrypted);
    decrypt(encrypted, cipher, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}

