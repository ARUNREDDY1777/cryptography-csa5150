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

// Function to solve the equations and find a and b
void solveAffineCipher(int c1, int p1, int c2, int p2, int *a, int *b) {
    int a_val, b_val;
    for (a_val = 0; a_val < 26; a_val++) {
        if (gcd(a_val, 26) == 1) {
            b_val = (c1 - a_val * p1) % 26;
            if (b_val < 0) b_val += 26;
            if ((a_val * p2 + b_val) % 26 == c2) {
                *a = a_val;
                *b = b_val;
                return;
            }
        }
    }
    *a = -1;
    *b = -1;
}

int main() {
    char text[100];
    int a, b;

    printf("Enter the ciphertext: ");
    gets(text);

    int c1 = 'B' - 'A';
    int p1 = 'E' - 'A';
    int c2 = 'U' - 'A';
    int p2 = 'T' - 'A';

    solveAffineCipher(c1, p1, c2, p2, &a, &b);

    if (a == -1 || b == -1) {
        printf("Unable to find valid values for a and b.\n");
        return 1;
    }

    printf("Found values: a = %d, b = %d\n", a, b);

    affineDecrypt(text, a, b);
    printf("Decrypted text: %s\n", text);

    return 0;
}

