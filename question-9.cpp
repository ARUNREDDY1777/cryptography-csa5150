#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
void createKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int used[26] = {0};
    int x = 0, y = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        if (isalpha(key[i])) {
            char ch = toupper(key[i]);
            if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'
            if (!used[ch - 'A']) {
                keyTable[x][y++] = ch;
                used[ch - 'A'] = 1;
                if (y == SIZE) {
                    y = 0;
                    x++;
                }
            }
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; // Skip 'J'
        if (!used[ch - 'A']) {
            keyTable[x][y++] = ch;
            used[ch - 'A'] = 1;
            if (y == SIZE) {
                y = 0;
                x++;
            }
        }
    }
}
void searchInTable(char keyTable[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void decryptPlayfair(char ciphertext[], char keyTable[SIZE][SIZE], char plaintext[]) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        searchInTable(keyTable, toupper(ciphertext[i]), &row1, &col1);
        searchInTable(keyTable, toupper(ciphertext[i+1]), &row2, &col2);

        if (row1 == row2) {
            plaintext[i] = keyTable[row1][(col1 + SIZE - 1) % SIZE];
            plaintext[i+1] = keyTable[row2][(col2 + SIZE - 1) % SIZE];
        } else if (col1 == col2) {
            plaintext[i] = keyTable[(row1 + SIZE - 1) % SIZE][col1];
            plaintext[i+1] = keyTable[(row2 + SIZE - 1) % SIZE][col2];
        } else {
            plaintext[i] = keyTable[row1][col2];
            plaintext[i+1] = keyTable[row2][col1];
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char key[] = "KEYWORD"; 
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPO???????NTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char keyTable[SIZE][SIZE];
    char plaintext[1024];

    createKeyTable(key, keyTable);
    decryptPlayfair(ciphertext, keyTable, plaintext);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}

