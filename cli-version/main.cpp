#include <iostream>
#include <cstring>

using namespace std;

char alphabet[]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};


bool isletter(char c){
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}


string encryptText(string& text, int key){ //maybe remove the &
    if(key < -26 || key > 26) key = key % 26;
    if(key < 0) key += 26;

    for(size_t i=0; i<text.size(); i++){
        char c = text[i];
        if(isletter(c)){
            int index = strchr(alphabet, tolower(c)) - alphabet;
            int pos = index + key;
            if (pos >= 26) pos -= 26;

            if(isupper(c)) text[i] = toupper(alphabet[pos]);
            else text[i] = alphabet[pos];
        }
    }

    return text;
}

string decryptText(string& text, int encryption_key){
    int key;
    if(encryption_key < -26 || encryption_key > 26) encryption_key = encryption_key % 26;
    if(encryption_key < 0) encryption_key += 26;
    //handles the conversion from encr_key to decr_key
    if (encryption_key>0) key = 26 - encryption_key;
    else if (encryption_key<=0) key = -encryption_key;

    //decrypting is the equivelant of encrypting with a modified key
    encryptText(text, key);

    return text;
}


int main(){

    cout << R"(   _____ _____   ____  _____
  / ____|  __ \ / __ \|  __ \
 | (___ | |__) | |  | | |__) |
  \___ \|  ___/| |  | |  _  /
  ____) | |    | |__| | | \ \
 |_____/|_|     \___\_\_|  \_\
        )" << endl;

    bool exits = false;

    while(!exits){
        string input, text, line;
        int key;
        cout << "Enter 1 for encryption, 2 for decryption, 3 to exit: ";
        cin >> input;

        if(input == "1"){
            cout << "Please enter the text you would like to encrypt.\n"
                 <<  "When done press Enter -> Ctrl + Z -> Enter (x2)\n" << endl;

            cout << "> ";

            while (getline(cin, line)) {
                text += line + '\n';
            }
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Please enter the key (shift) for the encryption. It must be an integer." << endl;
            cout << "> ";
            while (!(cin >> key)) {
                cout << "Invalid key input. Try again: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            cout << "Encrypted Text: " << encryptText(text, key) << endl;

        }

        else if (input == "2"){
            cout << "Please enter the text you would like to decrypt.\n"
                 <<  "When done press Enter -> Ctrl + Z -> Enter (x2)\n" << endl;

            cout << "> ";
            
            while (getline(cin, line)) {
                text += line + '\n';
            }
            cin.clear();
            cin.ignore(10000, '\n');            


            cout << "Please enter the key (shift) for the decryption. It must be an integer." << endl;
            cout << "> ";
            while (!(cin >> key)) {
                cout << "Invalid key input. Try again: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            cout << "Decrypted Text: " << decryptText(text, key) << endl;

        }

        else if (input == "3") return 0;

        else {cout << "Invalid choice number input!" << endl;}


    }

    return 0;
}