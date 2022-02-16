#include<bits/stdc++.h>
using namespace std;


string keyGen(string msg, string key){
    int s[256];
    for(int i=0; i<256; i++){
        s[i]=i;
    }
    int k[256];
    for(int i=0; i<256; i++){
        k[i] = key[i%key.size()];
    }
    int j=0;
    for(int i=0; i<256; i++){
        j = (j+s[i]+k[i])%256;
        swap(s[i], s[j]);
    }

    int i=0,t;
    j=0;
    string key_stream="";
    for(int i=0; i<msg.size(); i++){
        j = (j+s[i])%256;
        swap(s[i], s[j]);
        t = (s[i]+s[j])%256;
        key_stream += s[t];
    }
    return key_stream;
}

string encrypt(string msg, string key_stream){
    string cipher = "";
    for(int i=0; i<msg.size(); i++){
        cipher += (msg[i]^key_stream[i]);
    }
    return cipher;

}

int main(){
    string msg = "attackatdawn";
    string key = "megabuck";
    cout<<"Messgage : "<<msg<<endl;

    string key_stream = keyGen(msg, key);
    string enc = encrypt(msg, key_stream);
    cout<<"Encrypted Message : "<<enc<<endl;

    
    string dec = encrypt(enc, key_stream);
    cout<<"Decrypted Message :"<<dec<<endl;

    return 0;
}