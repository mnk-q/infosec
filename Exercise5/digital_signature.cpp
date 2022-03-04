
// Digital Signature in nature is similiar to mutual authentication except it differs in 2 ways

// The order of encryption-decryption is reversed
// This needs to happen only one-way, because only one party needs to prove it's authenticity. Digital Signature is not applied in Communication protocol.

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
    cout << "Alice created random challange R1 " << alice.random_challange_generator() << " And encrypts it with her public key to get ";
    buffer[bob.id].push_back(alice.encrypt(alice.R));
    cout << buffer[bob.id][1] << endl << endl;

    cout << "Alice sent her id " << buffer[bob.id][0] << " and her challange R1 " << buffer[bob.id][1] << " To Bob" << endl
         << endl;

    bob.S = buffer[bob.id].back();
    buffer[bob.id].pop_back();
    bob.S = bob.decrypt(bob.S, alice.public_key, alice.n);


    ll return_id = buffer[bob.id].back();
    cout << "Bob receives the sender's ID " << return_id << ". This can be used to find the public key of sender." << endl << endl;
    cout << "Bob decrypts the challange with sender's public key and gets " << bob.S << endl << endl;

    buffer[bob.id].pop_back();

    cout << "Bob creates a random challange R2 " << bob.random_challange_generator() << " and encrypts it with his private key to get ";

    buffer[return_id].push_back(bob.encrypt(bob.R));
    buffer[return_id].push_back(bob.S);

    cout << buffer[return_id][0] << endl << endl;


    cout << "Bob sends his encryped challange R2 " << buffer[alice.id][0] << " and decrypted challange R1 " << buffer[alice.id][1] << " To Alice" << endl
         << endl;
    alice.S = buffer[alice.id].back();
    buffer[alice.id].pop_back();

    cout << "Alice recevies the decrypted challange R1 " << alice.R << " which she encrypted in first place, and verifies it with R1 " 
         << alice.S << " received from bob " << endl << endl;
    if (alice.S == alice.R)
    {
        cout << "Alice Authenticated Bob using Bob's Digital Signature" << endl << endl;
    }
    else
    {
        cout << "Alice does not authenticate Bob" << endl << endl;
    }

    cout << "Alice decrypts the received challange R2 with bob's Public key to get " << alice.decrypt(buffer[alice.id].back(), bob.public_key, bob.n)
         << " and sends it back to bob" << endl << endl;
    buffer[bob.id].push_back(alice.decrypt(buffer[alice.id].back(), bob.public_key, bob.n));
    buffer[alice.id].pop_back();
    bob.S = buffer[bob.id].back();

    cout << "Bob verifies his own R2 " << bob.R << " and decrpyed R2 " << bob.S << " receieved from Alice " << endl << endl;

    if (bob.S == bob.R)
    {
        cout << "Bob Authenticated Alice using Alice's Digital Signature" << endl << endl;
    }
    else
    {
        cout << "Bob does not authenticate Alice" << endl << endl;
    }

    return 0;
}