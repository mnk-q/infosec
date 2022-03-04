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
    cout << "Alice created random challange R1 " << alice.random_challange_generator() << " And encrypts it with Bob's public key to get ";
    buffer[bob.id].push_back(alice.encrypt(alice.R, bob.public_key, bob.n));
    cout << buffer[bob.id][1] << endl
         << endl;

    cout << "Alice sent her id " << buffer[bob.id][0] << " and her challange R1 " << buffer[bob.id][1] << " To Bob" << endl
         << endl;
    bob.S = buffer[bob.id].back();
    buffer[bob.id].pop_back();
    bob.S = bob.decrypt(bob.S);

    cout << "Bob decrypts the challange with his private key and gets " << bob.S << endl << endl;

    ll return_id = buffer[bob.id].back();
    cout << "Bob receives the sender's ID " << return_id << ". This can be used to find the public key of sender." << endl << endl;

    buffer[bob.id].pop_back();

    cout << "Bob creates a random challange R2 " << bob.random_challange_generator() << " and encrypts it with sender's public key to get ";

    buffer[return_id].push_back(bob.encrypt(bob.R, alice.public_key, alice.n));
    buffer[return_id].push_back(bob.S);
    cout << buffer[alice.id][0] << endl
         << endl;

    cout << "Bob sends his encryped challange R2 " << buffer[alice.id][0] << " and decrypted challange R1 " << buffer[alice.id][1] << " To Alice" << endl
         << endl;

    alice.S = buffer[alice.id].back();
    buffer[alice.id].pop_back();

    cout << "Alice recevies the decrypted challange R1 " << alice.R << " which she encrypted in first place, and verifies it with R1 " 
         << alice.S << " received from bob " << endl << endl;

    if (alice.S == alice.R)
    {
        cout << "Alice Authenticated Bob" << endl << endl;
    }
    else
    {
        cout << "Alice does not authenticate Bob" << endl << endl;
    }

    cout << "Alice decrypts the received challange R2 with her private key to get " << alice.decrypt(buffer[alice.id].back()) 
         << " and sends it back to bob" << endl << endl;

    buffer[bob.id].push_back(alice.decrypt(buffer[alice.id].back()));
    buffer[alice.id].pop_back();

    bob.S = buffer[bob.id].back();
    cout << "Bob verifies his own R2 " << bob.R << " and decrpyed R2 " << bob.S << " receieved from Alice " << endl << endl;
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