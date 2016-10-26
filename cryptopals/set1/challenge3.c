#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crypto-utils.h"

/* Compile with: gcc challenge3.c crypto-utils.c -o challenge3 */

#define ASCII_LEN 256

static char *sInputStr = "1b37373331363f78151b7f2b783431333d"
                         "78397828372d363c78373e783a393b3736";


int main(int argc, char *argv[])
{
    int bytesLen = 0;
    char *bytes = hexStrToBytes(sInputStr, &bytesLen);
    if (!bytes) {
        printf("Failure! Couldn't convert hex to bytes.\n");
        return 1;
    }

    int bestScore = 0;
    char *bestScoreStr = malloc(bytesLen);
    if (!bestScoreStr) {
        printf("Failure! Couldn't alloc buffer for best score string.\n");
        return 1;
    }

    for (int i = 0; i < ASCII_LEN; i++) {
        char character = (char) i;

        char *xorResultStr = malloc(bytesLen);
        if (!xorResultStr) {
            printf("Failure! Couldn't alloc buffer for xor result string.\n");
            return 1;
        }

        xorByteToChar(bytes, character, xorResultStr, bytesLen);

        int currentScore = scoreEnglishText(xorResultStr, bytesLen);
        if (currentScore > bestScore) {
            bestScore = currentScore;
            strcpy(bestScoreStr, xorResultStr);
        }

        free(xorResultStr);
    }

    printf("The string with the best score is: %s\n", bestScoreStr);

    free(bestScoreStr);

    return 0;
}
