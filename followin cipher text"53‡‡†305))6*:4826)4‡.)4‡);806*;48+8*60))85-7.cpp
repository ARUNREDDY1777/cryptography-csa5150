#include <stdio.h>
#include <string.h>
#include <ctype.h>
void countFrequency(char text[], int freq[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            freq[text[i] - 'A']++;
        }
    }
}
void printMapping(char mapping[]) {
    for (int i = 0; i < 26; i++) {
        printf("%c -> %c\n", 'A' + i, mapping[i]);
    }
}
void decryptMessage(char text[], char mapping[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            text[i] = mapping[text[i] - 'A'];
        }
    }
}

int main() {
    char ciphertext[] = "53‡‡†305))6*:4826)4‡.)4‡);806*;48+8*60))85;;]8*::*8+83 (88)5*†:46(:88*96*?:8)*‡(:485);5*†2:*‡(:4956*2(5-4)88*4069285):)6+8)4‡‡:1($9:48081:8:811:48+85;4)485+528806*81 ($9:48:(88;4(‡?34:48)41:161::188:‡?;";
    int freq[26] = {0};
    char mapping[26];
    for (int i = 0; i < 26; i++) {
        mapping[i] = '*';
    }
    countFrequency(ciphertext, freq);
    char commonLetters[] = "ETAOIN";
    for (int i = 0; i < 6; i++) {
        int maxIndex = -1;
        int maxFreq = -1;
        for (int j = 0; j < 26; j++) {
            if (freq[j] > maxFreq) {
                maxFreq = freq[j];
                maxIndex = j;
            }
        }
        if (maxIndex != -1) {
            mapping[maxIndex] = commonLetters[i];
            freq[maxIndex] = -1; 
        }
    }
    printMapping(mapping);
    char decryptedText[256];
    strcpy(decryptedText, ciphertext);
    decryptMessage(decryptedText, mapping);

    printf("Initial Decryption Attempt: \n%s\n", decryptedText);
    mapping['‡' - 'A'] = 'E';
    mapping['4' - 'A'] = 'H';
    printMapping(mapping);
    strcpy(decryptedText, ciphertext);
    decryptMessage(decryptedText, mapping);

    printf("Refined Decryption Attempt: \n%s\n", decryptedText);
    return 0;
}

