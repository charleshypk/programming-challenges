#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crypto-utils.h"


char hexCharToByte(char aHexChar)
{
    if (aHexChar >= '0' && aHexChar <= '9') {
        return aHexChar - '0';
    }

    if (aHexChar >= 'a' && aHexChar <= 'f') {
        return (aHexChar - ('a' - 10));
    }

    printf("Failure! Invalid hex character.\n");
    exit(1);
}

/* Returns a malloc'd byte buffer, caller frees */
char* hexStrToBytes(char* aHexStr, int* aOutLen)
{
    /* Need valid input */
    if (!aHexStr || !aOutLen) {
        return NULL;
    }

    /* Need an even number of hex digits to convert to bytes */
    if (strlen(aHexStr) % 2 != 0) {
        return NULL;
    }

    /* Calculate the length of the output buffer */
    *aOutLen = strlen(aHexStr) / 2;
    if (*aOutLen == 0) {
        return NULL;
    }

    /* Create output buffer */
    char *outBuf = malloc(*aOutLen);
    if (!outBuf) {
        return NULL;
    }

    /* Fill the output buffer */
    int inputLen = strlen(aHexStr);
    for (int i = 0; i < inputLen; i = i + 2) {
        char char1 = aHexStr[i];
        char char2 = aHexStr[i + 1];

        char byte = 0;

        byte = hexCharToByte(char1) << 4;
        byte = byte | hexCharToByte(char2);

        outBuf[i / 2] = byte;
    }

    return outBuf;
}
