#include <bits/stdc++.h>
using namespace std;
map<char, int> charToCode;
map<int, char> codeToChar;

string encode(string msg, string key)
{
    string cipherText;
    int n = key.length();
    for (int i = 0; i < msg.length(); i++)
    {
        cipherText.push_back(codeToChar[charToCode[msg[i]] ^ charToCode[key[i % n]]]);
    }
    return cipherText;
}
string decode(string cipherCode, string key)
{
    return encode(cipherCode, key);
}
void preProcess()
{
    for (int i = 0; i < 32; i++)
    {
        charToCode['A' + i] = i;
        codeToChar[i] = 'A' + i;
    }
}
int main()
{
    preProcess();
    string msg = "HEILHITLER";
    string key = "MEGABUCK";
    string ciphertext = encode(msg, key);
    cout << "Plaintext : " + msg;
    cout << "\nEncrypted Text : " << ciphertext << endl;
    cout << "Decrypted Text : " << decode(ciphertext, key) << endl;
    return 0;
}