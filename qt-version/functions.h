#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
using namespace std;

bool isletter(char c);

bool iscapital(const char& c);

string encryptCS(string& text, int key, bool ignoreSpaces, bool ignoreUppercase);

string decryptCS(string& text, int encryption_key, bool ignoreSpaces, bool ignoreUppercase);

string int2Binary(int num);

string encryptBinary(string& text);

char binary2char(string binaryString);

string decryptBinary(const string& text);

#endif // FUNCTIONS_H
