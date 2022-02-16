#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main(){
    char ars[26];
    char prs[26];
    for(int i=0; i<26; i++){
        ars[i]='a'+i;
        prs[i]='a'+i;
    }
    
    //shuffling
    
    for(int i=0; i<100; i++){
        int id1 = rand()%26;
        int id2 = rand()%26;
        char p = prs[id1];
        prs[id1] = prs[id2];
        prs[id2] = p;
    }
    

    char msg[] = {'e','n','e','m','y','i','s','w','e','a','k'};
    char enc_msg[sizeof(msg)];
    for(int i=0; i<sizeof(msg); i++){
        enc_msg[i] = prs[msg[i]-'a'];
    }

    printf("Plaintext Message : ");
    for(int i=0; i<sizeof(msg); i++){
        printf("%c", msg[i]);
    }
    printf("\nEncrypted Message : ");
    for(int i=0; i<sizeof(msg); i++){
        printf("%c", enc_msg[i]);
    }

    printf("\n\nKey : ");
    for(int i=0; i<26; i++){
        printf("%c",prs[i]);
    }
    return 0;
}