#include<stdio.h>
#include<stdlib.h>
#define ll long long int 


ll gcd(ll a, ll b)
{
    if (a == 0)
       return b;
    if (b == 0)
       return a;
    if (a == b)
        return a;
    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}

ll modInverse(ll a, ll m)
{
    ll m0 = m;
    ll y = 0, x = 1;
 
    if (m == 1)
        return 0;
 
    while (a > 1) {
        ll q = a / m;
        ll t = m;
        m = a % m, a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;
 
    return x;
}
ll power(ll x, ll y, ll p)
{
    ll res = 1;     
 
    x = x % p; 
  
    if (x == 0) return 0; 
 
    while (y > 0)
    {
        if (y & 1)
            res = (res*x) % p;
        y = y>>1; 
        x = (x*x) % p;
    }
    return res;
}


char *encrypt_string(ll n, ll e, char *msg, int msg_size){
    char *enc;
    enc = (char *)malloc(sizeof(char)*msg_size);
    for(int i=0; i<msg_size; i++){
        enc[i] = power(1ll*(msg[i]-96), e, n);
    }
    return enc;
}

char *decrypt_string(ll n, ll e, char *msg, int msg_size){
    char *enc;
    enc = (char *)malloc(sizeof(char)*msg_size);
    for(int i=0; i<msg_size; i++){
        ll p = power(1ll*(msg[i]), e, n);
        enc[i] = p+96;
    }
    return enc;
}


ll encrypt_digit(ll p, ll e, ll n){
    return power(p, e, n);
}


int main(){
    /// Finding P and Q
    ll p = 31, q = 59;

    ll n = p*q;
    ll z = (p-1)*(q-1);

    // bruteforcing for e
    ll e = 2;
    while( gcd(e,z) != 1)
        e++;
    
    ll d = modInverse(e, z);
    printf("P: %lld\nQ: %lld\nN: %lld\ne: %lld\nz: %lld\nd: %lld\n",p,q,n,e,z,d);
    ll plain = 19;
    printf("Plain : %lld\n", plain);
    ll cipher = encrypt_digit(plain, e, n);
    printf("Encrypted with Public Key : %lld\n", cipher);
    ll uncipher = encrypt_digit(cipher, d, n);
    printf("Decrypted with Private key : %lld\n", uncipher);








    // char msg[] = {'a','t','t','a','c','k','a','t','d','a','r','k'};
    
    // printf("\nMessage : ");

    // for(int i=0; i<sizeof(msg); i++)
    //     printf("%c", msg[i]);

    // printf("\nEncrypted Message : ");

    // char *enc;
    // enc = encrypt_string(n, e, msg, sizeof(msg));
    // for(int i=0; i<sizeof(msg); i++)
    //     printf("%c", enc[i]);
    
    // char *dec;
    // printf("\n Decrypted Message : ");

    // dec = decrypt_string(n, d, enc, sizeof(msg));
    // for(int i=0; i<sizeof(msg); i++)
    //     printf("%c", dec[i]);


    return 0;
}


