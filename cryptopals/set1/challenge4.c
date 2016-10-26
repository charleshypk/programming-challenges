#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crypto-utils.h"

/* Compile with: gcc challenge4.c crypto-utils.c -o challenge4 */

#define ASCII_LEN  256

static char *sInputFile = "challenge4.txt";

static size_t bufferLen = 32;


int main(int argc, char *argv[])
{
    FILE *file = fopen(sInputFile, "r");

    char *buffer;
    size_t characters;

    buffer = malloc(bufferLen * sizeof(*buffer));
    characters = getline(&buffer, &bufferLen, file);

    int inputLen = (int) characters - 1;

    rewind(file);

    char sInputStr[inputLen + 1];

    int bestScore = 0;
    char *bestScoreStr = malloc(inputLen / 2);
    if (!bestScoreStr) {
        printf("Failure! Couldn't alloc buffer for best score string.\n");
        return 1;
    }

    while (fgets(sInputStr, inputLen + 1, file)) {
        if (strlen(sInputStr) != inputLen) {
            continue;
        }

        for (int i = 0; i < ASCII_LEN; i++) {
            char character = (char) i;

            int bytesLen = 0;
            char *bytes = hexStrToBytes(sInputStr, &bytesLen);
            if (!bytes) {
                printf("Failure! Couldn't convert hex to bytes.\n");
                return 1;
            }

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
    }

    printf("The string with the best score is: %s", bestScoreStr);

    free(buffer);
    free(bestScoreStr);

    fclose(file);

    return 0;
}
