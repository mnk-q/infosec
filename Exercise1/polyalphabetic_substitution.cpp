#include<iostream>
using namespace std;

string encrypt(string s, string key)
{
    string enc = "";
    int l = key.length();

    int i=0;

    while(s[i]!='\0')
    {
        int s1 = s[i]-97;
        int s2 = key[i%l]-97;

        enc += (s1+s2)%26+97;
        i++;
    }

    return enc;
}

string decrypt(string s, string key)
{
    string dec = "";
    int l = key.length();

    int i=0;

    while(s[i]!='\0')
    {
        int s1 = s[i]-97;
        int s2 = key[i%l]-97;

        for(int j=0;j<26;j++)
        {
            if((s2+j)%26==s1)
            {
                dec += (j+97);
            } 
        }
        i++;
    }

    return dec;
}

int main()
{
    string plaintext = "allhailtheking";
    string key = "megabuck";


    string enc = encrypt(plaintext,key);
    string dec = decrypt(enc,key);

    cout<<"PLaintext : "+ plaintext << endl;
    cout << "Key : " + key << endl;
    cout << "Encrypted Text : " << enc << endl;
    cout << "Decrypted Text : " << dec << endl;
    

    return 0;
}