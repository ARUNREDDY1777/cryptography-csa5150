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
void decryptAdditiveCipher(const char *ciphertext, int shift, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            int offset = toupper(ciphertext[i]) - 'A';
            int decryptedChar = (offset - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
            plaintext[i] = decryptedChar + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}
void letterFrequencyAttack(const char *ciphertext, int topN) {
    char decryptedText[1024];
    int frequency[ALPHABET_SIZE];
    int scores[ALPHABET_SIZE];
    int shifts[ALPHABET_SIZE];
    int len = strlen(ciphertext);
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        memset(frequency, 0, sizeof(frequency));
        decryptAdditiveCipher(ciphertext, shift, decryptedText);
        calculateFrequency(decryptedText, frequency);
        scores[shift] = scoreText(frequency);
        shifts[shift] = shift;
    }
    for (int i = 0; i < topN && i < ALPHABET_SIZE; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (scores[j] > scores[maxIndex]) {
                maxIndex = j;
            }
        }
        int tempScore = scores[i];
        scores[i] = scores[maxIndex];
        scores[maxIndex] = tempScore;
        int tempShift = shifts[i];
        shifts[i] = shifts[maxIndex];
        shifts[maxIndex] = tempShift;
    }
    for (int i = 0; i < topN && i < ALPHABET_SIZE; i++) {
        decryptAdditiveCipher(ciphertext, shifts[i], decryptedText);
        printf("Shift: %d\n", shifts[i]);
        printf("Plaintext: %s\n", decryptedText);
        printf("Score: %d\n", scores[i]);
        printf("\n");
    }
}

int main() {
    char ciphertext[] = "Uifsf jt b tfdsfu!"; 
    int topN = TOP_N;

    printf("Top %d possible plaintexts:\n", topN);
    letterFrequencyAttack(ciphertext, topN);

    return 0;
}

