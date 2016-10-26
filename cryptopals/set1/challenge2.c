#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crypto-utils.h"

/* Compile with: gcc challenge2.c crypto-utils.c -o challenge2 */

static char *sInputStr1 = "1c0111001f010100061a024b53535009181c";
static char *sInputStr2 = "686974207468652062756c6c277320657965";

static char *sOutputStr = "746865206b696420646f6e277420706c6179";


int main(int argc, char *argv[])
{
    int bytesLen1 = 0;
    char *bytes1 = hexStrToBytes(sInputStr1, &bytesLen1);
    if (!bytes1) {
        printf("Failure! Couldn't convert hex to bytes for first input.\n");
        return 1;
    }

    int bytesLen2 = 0;
    char *bytes2 = hexStrToBytes(sInputStr2, &bytesLen2);
    if (!bytes2) {
        printf("Failure! Couldn't convert hex to bytes for second input.\n");
        return 1;
    }

    char *xorResultStr = malloc(bytesLen1);
    if (!xorResultStr) {
        printf("Failure! Couldn't alloc buffer for xor result string.\n");
        return 1;
    }

    if (bytesLen1 != bytesLen2) {
        printf("Failure! The lengths of both inputs are different.\n");
        return 1;
    }

    xorBytes(bytes1, bytes2, xorResultStr, bytesLen1);

    char *aHexStr = malloc(bytesLen1 * 2);
    if (!aHexStr) {
        printf("Failure! Couldn't alloc buffer for hex string.\n");
        return 1;
    }

    bytesToHexStr(xorResultStr, aHexStr, bytesLen1);

    if (strcmp(aHexStr, sOutputStr) == 0) {
        printf("Success!\n");
    } else {
        printf("Failure!\n");
    }

    free(xorResultStr);
    free(aHexStr);

    return 0;
}
