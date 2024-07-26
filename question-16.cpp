#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define TOP_N 10
void calculateFrequency(const char *text, int *frequency) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            frequency[toupper(text[i]) - 'A']++;
        }
    }
}
int scoreText(const int *frequency) {
    static const double englishFrequency[ALPHABET_SIZE] = {
        8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
        0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.317, 9.056,
        2.758, 0.978, 2.560, 0.150, 1.929, 0.074
    };
    
    double score = 0.0;
    int totalLetters = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        totalLetters += frequency[i];
    }

    if (totalLetters == 0) return 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double observedFrequency = (double)frequency[i] / totalLetters * 100.0;
        score += observedFrequency * englishFrequency[i];
    }

    return (int)score;
}
void decryptSubstitution(const char *ciphertext, const char *key, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            int index = toupper(ciphertext[i]) - 'A';
            plaintext[i] = key[index];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0'; 
}
void generatePermutation(int *perm, int start, int end, char *currentKey, int *bestScore, char *bestKey) {
    if (start == end) {
        char key[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            key[i] = 'A' + perm[i];
        }
        key[ALPHABET_SIZE] = '\0';

        int frequency[ALPHABET_SIZE] = {0};
        char decryptedText[1024];
        decryptSubstitution("Uifsf jt b tfdsfu!", key, decryptedText); 

        calculateFrequency(decryptedText, frequency);
        int score = scoreText(frequency);

        if (score > *bestScore) {
            *bestScore = score;
            strcpy(bestKey, key);
        }
        return;
    }

    for (int i = start; i <= end; i++) {
        int temp = perm[start];
        perm[start] = perm[i];
        perm[i] = temp;

        generatePermutation(perm, start + 1, end, currentKey, bestScore, bestKey);

        temp = perm[start];
        perm[start] = perm[i];
        perm[i] = temp;
    }
}


void letterFrequencyAttack(const char *ciphertext, int topN) {
    int bestScore = 0;
    char bestKey[ALPHABET_SIZE + 1] = {0};

    int perm[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        perm[i] = i;
    }

    generatePermutation(perm, 0, ALPHABET_SIZE - 1, NULL, &bestScore, bestKey);

    printf("Top %d possible plaintexts:\n", topN);

    char decryptedText[1024];
    decryptSubstitution(ciphertext, bestKey, decryptedText);
    printf("Key: %s\n", bestKey);
    printf("Plaintext: %s\n", decryptedText);
}

int main() {
    char ciphertext[] = "Uifsf jt b tfdsfu!";
    int topN = TOP_N;

    letterFrequencyAttack(ciphertext, topN);

    return 0;
}

