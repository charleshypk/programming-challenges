#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crypto-utils.h"

/*
 * English Letter Frequency Table
 *
 * Obtained October 25, 2016 from
 * www.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
 */
static const int LETTER_FREQ[26] =
{
    812, 149, 271, 432, 1202, 230, 203, 592, 731,  10, 69, 398, 261,
    695, 768, 182,  11,  602, 628, 910, 288, 111, 209, 17, 211,   7
};

/* Average word length / length of english alphabet */
static const int SPACE_FREQ = 1962;


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

char byteToHexChar(char byte)
{
    if (byte >= 0 && byte <= 9) {
        return byte + 48;
    }

    if (byte >= 10 && byte <= 15) {
        return byte + 87;
    }

    printf("Failure! Invalid byte.\n");
    exit(1);
}

/* Converts byte array to a hex string */
char* bytesToHexStr(char *aBytes, char *aHexStr, int aBytesLen)
{
    /* Need valid input */
    if (!aBytes || !aBytesLen) {
        return NULL;
    }

    for (int i = 0; i < aBytesLen; i++) {
        char byte1 = (aBytes[i] >> 4) & 0x0F;
        char byte2 = aBytes[i] & 0x0F;

        aHexStr[i * 2] = byteToHexChar(byte1);
        aHexStr[(i * 2) + 1] = byteToHexChar(byte2);
    }

    return aHexStr;
}

/* Performs XOR operation on two byte arrays of same length */
void xorBytes(char *aBytes1, char *aBytes2, char *aOutStr, int aOutLen)
{
    for (int i = 0; i < aOutLen; i++) {
        aOutStr[i] = aBytes1[i] ^ aBytes2[i];
    }
}

/* Performs XOR operation on a byte array to a single character */
void xorByteToChar(char *aBytes, char character, char *aOutStr, int aOutLen)
{
    for (int i = 0; i < aOutLen; i++) {
        aOutStr[i] = aBytes[i] ^ character;
    }
}

/* Returns a score that uses character frequency to determine if text is English */
int scoreEnglishText(char *aInputStr, int aOutLen)
{
    int score = 0;

    for (int i = 0; i < aOutLen; i++) {
        int asciiCode = tolower(aInputStr[i]) - 'a';

        if (asciiCode >= 0 && asciiCode <= 25) {
            score += LETTER_FREQ[asciiCode];
        } else if (aInputStr[i] == 32) {
            score += SPACE_FREQ;
        }
    }

    score = score / aOutLen;

    return score;
}

/* Encrypts plaintext by performing XOR operation on a repeating-key */
void xorStrToRepeatingKey(char *aInputStr, char *key, char *aOutStr, int aOutLen)
{
    int keyLen = strlen(key);

    for (int i = 0; i < aOutLen; i++) {
        char character = key[i % keyLen];
        aOutStr[i] = aInputStr[i] ^ character;
    }
}
