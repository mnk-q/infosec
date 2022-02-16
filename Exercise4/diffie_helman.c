#include<stdio.h>
#define ll long long int

struct person {
    ll g;
    ll n;

    ll p;
    ll send;
    ll recv;
    ll key;
};


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

int main(){ 

    ll g = 3;
    ll n = 47;
    struct person alice,bob;

    printf("g: %lld, n: %lld\n", g, n);
    
    alice.g=g;
    alice.n=n;
    alice.p = 10;
    alice.send = power(alice.g, alice.p, alice.n);
    printf("Alice send g: %lld, n: %lld, g^x mod n: %lld\n", alice.g, alice.n, alice.send);

    
    bob.g = g, bob.n=n;
    bob.p = 12;
    bob.recv = alice.send;
    printf("Bob Received\n");
    bob.send = power(bob.g, bob.p, bob.n);
    printf("Bob send g: %lld, n: %lld, g^y mod n: %lld\n", bob.g, bob.n, bob.send);

    alice.recv = bob.send;
    printf("Alice Received\n");


    alice.key = power(alice.recv, alice.p, n); 
    printf("Alice Key : %lld\n",alice.key);

    bob.key = power(bob.recv, bob.p, n); 
    printf("Bob Key : %lld\n",bob.key);





    return 0;
}