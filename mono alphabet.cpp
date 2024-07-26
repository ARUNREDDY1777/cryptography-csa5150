#include <stdio.h>
#include <string.h>
void encrypt(char text[], char key[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (c >= 'A' && c <= 'Z') {
            text[i] = key[c - 'A'];
        }
        else if (c >= 'a' && c <= 'z') {
            text[i] = key[c - 'a'] + ('a' - 'A');
        }
    }
}

void decrypt(char text[], char key[]) {
    char inverseKey[26];
    
    
    for (int i = 0; i < 26; i++) {
        inverseKey[key[i] - 'A'] = 'A' + i;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        
        
        if (c >= 'A' && c <= 'Z') {
            text[i] = inverseKey[c - 'A'];
        }
        
        else if (c >= 'a' && c <= 'z') {
            text[i] = inverseKey[c - 'a'] + ('a' - 'A');
        }
    }
}

int main() {
    char text[100];
    char key[27] = "QWERTYUIOPLKJHGFDSAZXCVBNM";  
    int choice;

    printf("Enter the text: ");
    gets(text);

    printf("Enter 1 to Encrypt or 2 to Decrypt: ");
    scanf("%d", &choice);
    getchar();  

    if (choice == 1) {
        encrypt(text, key);
        printf("Encrypted text: %s\n", text);
    } else if (choice == 2) {
        decrypt(text, key);
        printf("Decrypted text: %s\n", text);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}

