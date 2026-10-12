#include "functions.h"
#include <cstring>
#include <ctype.h>
#include <cmath>

using namespace std;

const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
const int BITS = 6;

bool isletter(char c){
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool iscapital(const char& c){
    return (c>='A' && c<='Z');
}

string encryptCS(string& text, int key, bool ignoreSpaces, bool ignoreUppercase){
    if(key < -26 || key > 26) key = key % 26;
    if(key < 0) key += 26;

    for(size_t i=0; i<text.size(); i++){
        char c = text[i];
        if(isletter(c)){
            int index = strchr(alphabet, tolower(c)) - alphabet;
            int pos = index + key;
            if (pos >= 26) pos -= 26;

            if(isupper(c) && !ignoreUppercase) text[i] = toupper(alphabet[pos]);
            else text[i] = alphabet[pos];
        }
        else if(c == ' ' && ignoreSpaces){
            text.erase(text.begin() + i);
            i--;
        }
    }

    return text;
}

string decryptCS(string& text, int encryption_key, bool ignoreSpaces, bool ignoreUppercase){
    int key;
    if(encryption_key < -26 || encryption_key > 26) encryption_key = encryption_key % 26;
    if(encryption_key < 0) encryption_key += 26;
    //handles the conversion from encr_key to decr_key
    if (encryption_key>0) key = 26 - encryption_key;
    else if (encryption_key<=0) key = -encryption_key;

    //decrypting is the equivelant of encrypting with a modified key
    encryptCS(text, key, ignoreSpaces, ignoreUppercase);

    return text;
}

string int2Binary(int num){

    string binaryString;

    //edge case - return as many zeros as BITS used
    if(num == 0){
        for(int i=0; i<BITS; i++){
            binaryString.insert(binaryString.begin(), '0');
        }
        return binaryString;
    }

    // classic algorithm to convert decimal to binary numbers
    while(num != 0){
        int rem = num % 2;
        num /= 2;
        binaryString.insert(binaryString.begin(), rem + '0'); // +'0' converts int to char
    }

    // convert the produced binary string to fit in 6 digits
    int remainingBits = BITS - binaryString.size();
    for(int i=0; i<remainingBits; i++){
        binaryString.insert(binaryString.begin(), '0');
    }

    return binaryString;

}

string encryptBinary(string& text){
    /*
        each character is converted to a number value
        digits 0-9 are assigned to numerical values 0-9 correspondingly
        lowercase a-z are assigned to numerical values 10-35 correspondingly
        capitals A-Z are assigned to numerical values 36-61 correspondingly
        note that we have a total of 0-61 that is 62 numbers in decimal
        and we use 6 bits to fit them all since 2^6 = 64 >= 62
    */

    for(size_t i=0; i<text.size(); i++){
        char c = text[i];
        int num;

        if(!isdigit(c) && !isletter(c)) continue; //its special char

        else if(isdigit(c)){
            num = c - '0'; // -'0' converts char to int
            text.replace(i,1,int2Binary(num));
            i += BITS - 1;
        }

        else if (isletter(c)){
            if(iscapital(c)) num = strchr(alphabet, tolower(c)) - alphabet + 10 + 26; //26 digts of the eng alphabet
            else num =  strchr(alphabet, tolower(c)) - alphabet + 10;

            text.replace(i,1,int2Binary(num));
            i += BITS - 1;
        }
    }

    return text;
}

char binary2char(string binaryString){
    int decnum = 0; //the decimal number equivalent of the binary string
    int j=BITS-1; //j is the power of 2 of the corresponding index i when summing
    for(int i=0; i<binaryString.size(); i++){
        if(binaryString[i] == '1'){
            decnum += pow(2,j); //CHECK IF FLOAT FROM pow() BRINGS PROBLEMS!
        }
        j--;
    }

    if(0 <= decnum && decnum <= 9){ //its a number
        return '0' + decnum;
    }
    else if (10 <= decnum && decnum <=35){ // its a lowercase
        return alphabet[decnum-10];
    }
    else if(36<= decnum && decnum <= 61){ // its uppercase
        return toupper(alphabet[decnum-26-10]);
    }

    else return '?'; //unsupported case
}

string decryptBinary(const string& text){

    string decrypted;

    for(size_t i = 0; i < text.size(); i++){

        char c = text[i];

        if(isletter(c)){
            return "ERROR! Binary code can contain only 0,1 and special characters!\n";
        }

        if(c == '0' || c == '1'){
            string binstring;

            for(int j = i; j < i + BITS; j++){
                if(isdigit(text[j])){
                    int c_int = text[j] - '0'; //converts char to int if char is digit
                    if(c_int == 0 || c_int == 1){
                        binstring.push_back(text[j]);
                    }
                    else return "ERROR! Binary code can contain only 0,1 and special characters!\n";
                }
                else return "ERROR! Text contains input that doesn't map to 6-bit binary representation (non 6-digit binary stream)!\n";
            }

            decrypted.push_back(binary2char(binstring));

            i = i + BITS - 1;
        }
        else if(isdigit(c)){
            return "ERROR! Text contains Non binary numbers!";
        }
        else {
            decrypted.push_back(c);
        }
    }

    return decrypted;
}
