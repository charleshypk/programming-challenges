#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crypto-utils.h"

/* Compile with: gcc challenge5.c crypto-utils.c -o challenge5 */

static char *sInputStr = "Burning 'em, if you ain't quick and nimble\n"
                         "I go crazy when I hear a cymbal";

static char *sRepeatingKey = "ICE";

static char *sOutputStr = "0b3637272a2b2e63622c2e69692a23693a2a3"
                          "c6324202d623d63343c2a2622632427276527"
                          "2a282b2f20430a652e2c652a3124333a653e2"
                          "b2027630c692b20283165286326302e27282f";


int main(int argc, char *argv[])
{
    int inputLen = strlen(sInputStr);
    
    char *encryptedStr = malloc(inputLen);
    if (!encryptedStr) {
        printf("Failure! Couldn't alloc buffer for encrypted string.\n");
        return 1;
    }

    xorStrToRepeatingKey(sInputStr, sRepeatingKey, encryptedStr, inputLen);

    char *aHexStr = malloc(inputLen * 2);
    if (!aHexStr) {
        printf("Failure! Couldn't alloc buffer for hex string.\n");
        return 1;
    }

    bytesToHexStr(encryptedStr, aHexStr, inputLen);

    if (strcmp(aHexStr, sOutputStr) == 0) {
        printf("Success!\n");
    } else {
        printf("Failure!\n");
    }

    free(encryptedStr);
    free(aHexStr);

    return 0;
}
