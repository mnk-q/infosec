// Digital Signature happens one - way
// assume Alice sent a message to bob, she encrypts it with her private key
// If Bob can decrypt the message with Alice's public key , then it will mean that Message came from Alice
// Implemetation : 
// Alice generates a random challange, encrypts it with her private key and send her name with this challange to bob
// Bob upon receving both, decrypts the message with alice's public key.
// If the decryption is successfull, then authentication process is complete.
// To make it two-way, Bob sends her a challange encrpted with his private key, as well as decrypted challange. Alice verifies 
// the decrypted one, then she decryptes the message sent by bob and sends it back to bob, bob verifies it.
#include <iostream>
#include <vector>
#include "algos.h"
#define ll long long int
using namespace std;

vector<ll> buffer[2];
int counter = 0;
class Person
{
private:
    ll private_key;

public:
    ll public_key;
    ll id;
    ll n;

    ll S, R;
    Person()
    {
        pair<pair<int, int>, int> p = rsa();
        n = p.second;
        private_key = p.first.first;
        public_key = p.first.second;
        id = counter;
        counter++;
    }
    ll decrypt(ll msg, ll other_public_key, ll other_n)
    {
        return power(msg, other_public_key, other_n);
    }
    ll encrypt(ll cipher)
    {
        return power(cipher, private_key, n);
    }
    ll random_challange_generator(ll range = 1000)
    {
        R = rand() % range;
        return R;
    }
};

int main()
{

    Person alice, bob;
    ;

    /// Initiating the Mutual Authentication Process
    buffer[bob.id].push_back(alice.id);
    alice.random_challange_generator();
    buffer[bob.id].push_back(alice.encrypt(alice.R));

    bob.S = buffer[bob.id].back();
    buffer[bob.id].pop_back();
    bob.S = bob.decrypt(bob.S, alice.public_key, alice.n);

    ll return_id = buffer[bob.id].back();
    buffer[bob.id].pop_back();
    buffer[return_id].push_back(bob.encrypt(bob.random_challange_generator()));
    buffer[return_id].push_back(bob.S);

    alice.S = buffer[alice.id].back();
    buffer[alice.id].pop_back();
    if (alice.S == alice.R)
    {
        cout << "Alice Authenticated Bob using Bob's Digital Signature" << endl;
    }
    else
    {
        cout << "Alice does not authenticate Bob" << endl;
    }
    buffer[bob.id].push_back(alice.decrypt(buffer[alice.id].back(), bob.public_key, bob.n));
    buffer[alice.id].pop_back();
    bob.S = buffer[bob.id].back();
    if (bob.S == bob.R)
    {
        cout << "Bob Authenticated Alice using Alice's Digital Signature" << endl;
    }
    else
    {
        cout << "Bob does not authenticate Alice" << endl;
    }

    return 0;
}