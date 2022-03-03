// User X encrypts random challenge R2 using the public key of Y and sends it to User Y with his user name.

// User Y decrypts the random challenge R2 with his private key. User Y creates its own random
// challenge R1 and encrypt it using public key X and send both (encrypted R1 and decrypted R2) to X.

// User X decrypt random challenge R1 with his private key and send it to Y. User Y verifies R1.

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
    ll encrypt(ll msg, ll other_public_key, ll other_n)
    {
        return power(msg, other_public_key, other_n);
    }
    ll decrypt(ll cipher)
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
    buffer[bob.id].push_back(alice.encrypt(alice.R, bob.public_key, bob.n));

    bob.S = buffer[bob.id].back();
    buffer[bob.id].pop_back();
    bob.S = bob.decrypt(bob.S);

    ll return_id = buffer[bob.id].back();
    buffer[bob.id].pop_back();
    buffer[return_id].push_back(bob.encrypt(bob.random_challange_generator(), alice.public_key, alice.n));
    buffer[return_id].push_back(bob.S);

    alice.S = buffer[alice.id].back();
    buffer[alice.id].pop_back();
    if (alice.S == alice.R)
    {
        cout << "Alice Authenticated Bob" << endl;
    }
    else
    {
        cout << "Alice does not authenticate Bob" << endl;
    }
    buffer[bob.id].push_back(alice.decrypt(buffer[alice.id].back()));
    buffer[alice.id].pop_back();
    bob.S = buffer[bob.id].back();
    if (bob.S == bob.R)
    {
        cout << "Bob Authenticated Alice " << endl;
    }
    else
    {
        cout << "Bob does not authenticate Alice" << endl;
    }

    return 0;
}