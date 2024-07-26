#include <stdio.h>

// Function to calculate gcd of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find modular multiplicative inverse of a under modulo m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Function to encrypt text using affine cipher
void affineEncrypt(char text[], int a, int b) {
    if (gcd(a, 26) != 1) {
        printf("Invalid value for a: %d. It must be coprime with 26.\n", a);
        return;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (char) ((((a * (text[i] - 'A')) + b) % 26) + 'A');
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (char) ((((a * (text[i] - 'a')) + b) % 26) + 'a');
        }
    }
}

// Function to decrypt text using affine cipher
void affineDecrypt(char text[], int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Invalid value for a: %d. It has no modular inverse under modulo 26.\n", a);
        return;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (char) (((a_inv * ((text[i] - 'A' - b + 26)) % 26) + 'A'));
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (char) (((a_inv * ((text[i] - 'a' - b + 26)) % 26) + 'a'));
        }
    }
}

int main() {
    char text[100];
    int a, b, choice;

    printf("Enter the text: ");
    gets(text);

    printf("Enter the value for a: ");
    scanf("%d", &a);

    printf("Enter the value for b: ");
    scanf("%d", &b);

    printf("Enter 1 to Encrypt or 2 to Decrypt: ");
    scanf("%d", &choice);

    if (choice == 1) {
        affineEncrypt(text, a, b);
        printf("Encrypted text: %s\n", text);
    } else if (choice == 2) {
        affineDecrypt(text, a, b);
        printf("Decrypted text: %s\n", text);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}

