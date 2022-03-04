#include <stdio.h>
#define ll long long int

struct person
{
    ll g;
    ll n;

    ll p;
    ll keys[5];
};

ll power(ll x, ll y, ll p)
{
    ll res = 1;

    x = x % p;

    if (x == 0)
        return 0;

    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

int main()
{

    struct person alice, bob, eve;
    // Think of a number G and N
    ll g = 201;
    ll n = 91;

    // Alice generates a number and creates her g^x mod n
    alice.p = 67;
    alice.keys[0] = power(g, alice.p, n);

    // Alice prepares to send these. Eve catches them midway
    eve.keys[1] = alice.keys[0];

    // Eve creates her own number and sends to Bob
    eve.p = 88;
    eve.keys[0] = power(g, eve.p, n);

    // Eve prepares a number to handle encryption from Alice side
    eve.keys[2] = power(eve.keys[1], eve.p, n);

    // Bob receives Eve's numbers, assuming from Alice
    bob.keys[1] = eve.keys[0];

    // Bob creates his own number
    bob.p = 101;
    bob.keys[0] = power(g, bob.p, n);

    // Bob sends these to Alice. Eve catches them midway
    eve.keys[3] = bob.keys[0];

    // Eve prepares to deal with the bob side of encryption-decryption
    eve.keys[4] = power(eve.keys[3], eve.p, n);

    // Eve is now Eavesdropping xD 

    printf("g : %lld\nn : %lld\n",g,n );
    printf("Alice's X : %lld, Alice's g^x mod N : %lld\n", alice.p, alice.keys[0]);
    printf("Eve's z : %lld, Eve's g^z mod n : %lld\n", eve.p, eve.keys[0]);
    printf("Bob's y : %lld, Bob's g^y mod n : %lld\n", bob.p, bob.keys[0]);
    printf("Eve's g^xz mod n : %lld, Eve's g^yz mod n : %lld ", eve.keys[2], eve.keys[4]);

    /*
    Structure of Alice Keys
    [g^x mod n, g^z mod n, g^(xz) mod n]

    Structure of Bob Keys
    [g^y nod n, g^z mod n, g^(yz) mod n]

    Structure of Eve Keys
    [g^z mod n, g^x mod n, g^(xz) mod n, g^y mod n, g^yz mod n]

    */
    return 0;
}