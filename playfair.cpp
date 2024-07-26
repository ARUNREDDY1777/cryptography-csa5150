#include <stdio.h>
#include <string.h>
#define SIZE 5

void generateKeyTable(char key[], char table[SIZE][SIZE]) {
    int flag[26] = {0}, i, k = 0;
    for (i = 0; key[i]; i++) if (!flag[key[i] - 'a']) table[k/SIZE][k%SIZE] = key[i], flag[key[i]-'a'] = 1, k++;
    for (i = 0; i < 26; i++) if (!flag[i] && i != 'j'-'a') table[k/SIZE][k%SIZE] = 'a'+i, k++;
}

void search(char table[SIZE][SIZE], char a, char b, int pos[]) {
    int i, j;
    for (i = 0; i < SIZE; i++) for (j = 0; j < SIZE; j++) {
        if (table[i][j] == a) pos[0] = i, pos[1] = j;
        if (table[i][j] == b) pos[2] = i, pos[3] = j;
    }
}

void cipher(char text[], char table[SIZE][SIZE], int decrypt) {
    int i, a[4];
    for (i = 0; text[i]; i += 2) {
        if (!text[i+1]) text[i+1] = 'x';
        search(table, text[i], text[i+1], a);
        if (a[0] == a[2]) text[i] = table[a[0]][(a[1] + 1 - decrypt*2 + SIZE) % SIZE], text[i+1] = table[a[2]][(a[3] + 1 - decrypt*2 + SIZE) % SIZE];
        else if (a[1] == a[3]) text[i] = table[(a[0] + 1 - decrypt*2 + SIZE) % SIZE][a[1]], text[i+1] = table[(a[2] + 1 - decrypt*2 + SIZE) % SIZE][a[3]];
        else text[i] = table[a[0]][a[3]], text[i+1] = table[a[2]][a[1]];
    }
}

int main() {
    char text[100], key[27] = "keywordexample", table[SIZE][SIZE];
    printf("Enter text: ");
    gets(text);
    generateKeyTable(key, table);
    cipher(text, table, 0);
    printf("Encrypted: %s\n", text);
    cipher(text, table, 1);
    printf("Decrypted: %s\n", text);
    return 0;
}

