#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void swap(char *a, char *b){
    char c = *a;
    *a = *b;
    *b = c;
}
void swapi(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}


int main(){

    // To provide Double transpositional Cipher we need 3 things.
    // 1. Message , 2. Key Word 1, 3. Key word 2
    // Moreover , we can also change the transposition type from row to column and vice versa
    // For simplicity, we will keep both the transpositions to columns only
    // Although Row transpositions would have been waayyyy easier to implement

    char msg[] = {'a','t','t','a','c','k','a','t','d','a','r','k'};
    char key1[] = {'r','u','s','t'};
    char key2[] = {'g','o','l','d'};

    int rows = (sizeof(msg)+sizeof(key1)-1)/sizeof(key1);
    int cols = sizeof(key1);
    char mat1[rows][cols];
    for(int i=0; i<sizeof(msg); i++){
        mat1[i/sizeof(key1)][i%sizeof(key1)] = msg[i];
    }

    char mat2[rows][cols];
    int perm[cols];
    for(int i=0; i<cols; i++)
        perm[i]=i;
    
    // Sorting with bubble sort
    for(int i=0; i<cols-1; i++){
        for(int j=0; j<cols-i-1; j++){
            if (key1[j] > key1[j+1]){
                swap(&key1[j], &key1[j+1]);
                swap(&perm[j], &perm[j+1]);
            }
        }
    }

    for(int j=0; j<cols; j++){
        int colno = perm[j];
        for(int i=0; i<rows; i++){
            mat2[i][j] = mat1[i][colno];
        }
    }
    char enc_msg[sizeof(msg)];
    int idx=0;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            enc_msg[idx] = mat2[i][j];
            idx++;
        }
    }
    
    for(int i=0; i<sizeof(msg); i++){
        printf("%c",enc_msg[i]);
    }
    printf("\n\n\n");
    // At this Step, The first transposition is complete. 

    rows = (sizeof(enc_msg)+sizeof(key2)-1)/sizeof(key2);
    cols = sizeof(key2);
    char mat3[rows][cols];
    for(int i=0; i<sizeof(enc_msg); i++){
        mat3[i/sizeof(key2)][i%sizeof(key2)] = enc_msg[i];
    }

    char mat4[rows][cols];
    
    for(int i=0; i<cols; i++)
        perm[i]=i;
    
    // Sorting with bubble sort
    for(int i=0; i<cols-1; i++){
        for(int j=0; j<cols-i-1; j++){
            if (key2[j] > key2[j+1]){
                swap(&key2[j], &key2[j+1]);
                swap(&perm[j], &perm[j+1]);
            }
        }
    }

    for(int j=0; j<cols; j++){
        int colno = perm[j];
        for(int i=0; i<rows; i++){
            mat4[i][j] = mat3[i][colno];
        }
    }
    char enc_msg2[sizeof(enc_msg)];
    idx=0;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            enc_msg2[idx] = mat4[i][j];
            idx++;
        }
    }


    printf("Plaintext : ");
    for(int i=0; i<sizeof(enc_msg2); i++){
        printf("%c",msg[i]);
    }

    printf("\nEncryted Text  : ");
    
    for(int i=0; i<sizeof(enc_msg2); i++){
        printf("%c",enc_msg2[i]);
    }

    return 0;
}