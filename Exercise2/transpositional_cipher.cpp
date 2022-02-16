#include<bits/stdc++.h>
using namespace std;

string transposition_cipher_encrypt(string message, string key){    
    int msg_size = message.size();
    int key_size = key.size();
    int rows = (msg_size+key_size - 1)/key_size;
    int cols = key_size;
    char mat[rows][cols];
    int idx = 0;
    int i,j;
    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            if(idx >= msg_size) {
                mat[i][j]='*';
                continue;
            }
            mat[i][j]=message[idx];
            idx++;
        }
    }
    string enc_msg;
    vector<pair<char, int>> p;
    for(i=0; i<cols; i++){
        p.push_back({key[i], i});
    }
    sort(p.begin(), p.end());
    for(auto j: p){
        for(i=0; i<rows; i++){
            if(mat[i][j.second]=='*')
                continue;
            enc_msg += mat[i][j.second];
        }
    }
    

    return enc_msg;

}

string transposition_cipher_decrypt(string msg, string key){


    int msg_size = msg.size(), cols = key.size();
    int rows = (msg_size+cols-1)/cols,i,j;

    char mat[rows][cols];
    int ub = msg_size % cols;
    if(ub==0){
        ub = cols+1;
    }
    vector<pair<char, int>> p;
    for(i=0; i<cols; i++){
        p.push_back({key[i], i});
    }
    sort(p.begin(), p.end());
    int idx=0;
    for(auto j: p){
        for(i=0; i<rows; i++){
            if(i==rows-1 && j.second >= ub){
                continue;
            }
            mat[i][j.second] = msg[idx];
            idx++;
        }
    }
    string dec_msg ="";
    for(i=0; i<rows;i++){
        for(j=0;j<cols;j++){
            dec_msg+=mat[i][j];
        }
    }

    return dec_msg;



}

int main(){
    string message = "we are discussingnwsinroomno#410";
    string key = "megabuck";

    string enc_msg = transposition_cipher_encrypt(message, key);
    cout<<"Plaintext : " + message+"\n";
    cout<<"Encrypted Text : "+enc_msg+"\n";

    string dec_msg = transposition_cipher_decrypt(enc_msg, key);
    cout<<"Decrypted Text : "+dec_msg;
    return 0;
}