char hexCharToByte(char aHexChar);

char* hexStrToBytes(char* aHexStr, int* aOutLen);

char byteToHexChar(char byte);

char* bytesToHexStr(char *aBytes, char *aHexStr, int aBytesLen);

void xorBytes(char *aBytes1, char *aBytes2, char *aOutStr, int aOutLen);
