#include<stdio.h>
#include<stdlib.h>

char *ceaser(char *word , int key_shift, int size){

    // takes input the string, size of string and key shift
    // returns the shifted arrays
    if(key_shift < 0){
        for(int i=0; i<size; i++){
            word[i] = 26 - abs(word[i]-97+key_shift)%26 + 97;
        }
        return word;
    }
    for(int i=0; i<size; i++){
        word[i] = (word[i]-97+key_shift)%26 + 97;
    }
    return word;
}

int main(){
    char c[] = {'m','a','n','i','s','h','k','u','z'};
    int key = 3;
    int size = 9;
    printf("\nMessage :");
    for(int i=0; i<size; i++){
        printf("%c ", c[i]);
    }
    printf("\n");

    printf("\nEncrypted Message : ");

    char *p = ceaser(c, key, size);
    for(int i=0; i<size; i++){
        printf("%c ", p[i]);
    }
    printf("\n");

    return 0;
}