#include<stdio.h>
#include<stdlib.h>

int majority(int x, int y, int z)
{
    int m;
    if (x == 0){
        if (y == 0 || z == 0){
            m = 0;
        }
        else{
            m = 1;
        }
    }
    else{
        if (y == 1 || z == 1){
            m = 1;
        }
        else{
            m = 0;
        }
    }
    return m;
}

int *encrypt(int *msg, int msg_size, int *key, int key_size, int required_keystrem_size)
{
    // Key_size is fixed to 64
    // We create 3 registers X, Y, Z with size 19, 22, 23 respectively
    int size_x = 19, size_y = 22, size_z = 23;
    int x[size_x], y[size_y], z[size_z];
    for (int i = 0; i < key_size; i++)
    {
        if (i < 19)
            x[i] = key[i];
        else if (i < 41)
            y[i-19] = key[i];
        else
            z[i-19-22] = key[i];
    }
    printf("\nX: ");
    for(int i=0; i<size_x; i++){
        printf("%d", x[i]);
    }
    printf("\nY: ");
    for(int i=0; i<size_y; i++){
        printf("%d", y[i]);
    }
    printf("\nZ: ");
    for(int i=0; i<size_z; i++){
        printf("%d", z[i]);
    }

    int key_stream[required_keystrem_size];

    int m,t;
    for (int i = 0; i < required_keystrem_size; i++){
        m = majority(x[8], y[10], z[10]);
        if (x[8] == m){ // shift the bits of x if x[8] is majority
            t = x[13] ^ x[16] ^ x[17] ^ x[18];
            for (int j = size_x - 1; j > 0; j--)
                x[j] = x[j - 1];
            x[0] = t;
        }
        if(y[10] == m){
            t = y[20]^y[21];
            for(int j=size_y-1; j>0; j--)
                y[j] = y[j-1];
            y[0] = t;
        }
        if(z[10] == m){
            t = z[20] ^ z[21];
            for(int j=size_z-1; j>0; j--)
                z[j] = z[j-1];
            z[0] = t;
        }

        key_stream[i] = x[size_x-1]^y[size_y-1]^z[size_z-1];
    }
    int *enc_msg;
    enc_msg = (int*)malloc(msg_size*sizeof(int));
    for(int i=0; i<msg_size; i++){
        enc_msg[i] = msg[i]^key_stream[i%required_keystrem_size];
    }

    
    return enc_msg;
}

int main(){
    int msg[] = {1,0,1,1,0,1,0,1,0,1,1,1,0,0,0,1,0,1,0,1};
    int key[] = {1,0,1,1,0,1,0,1,0,1,0,1,1,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0};
    
    int * enc;
    int msg_size = sizeof(msg)/sizeof(msg[0]);
    int key_size = 64;
    int required_keystream = msg_size;
    printf("Message : ");
    for(int i=0; i<msg_size; i++)
        printf("%d ", msg[i]);
    enc = encrypt(msg, msg_size, key, key_size, required_keystream);

    printf("\nEncrypted Message : ");
    for(int i=0; i<msg_size; i++)
        printf("%d ", enc[i]);
    

    int *dec_msg;
    dec_msg = encrypt(enc, msg_size, key, key_size, required_keystream);

    printf("\nDecrypted Message : ");
    for(int i=0; i<msg_size; i++)
        printf("%d ", dec_msg[i]);
    
    free(enc);
    free(dec_msg);
    return 0;
}