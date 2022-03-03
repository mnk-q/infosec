#include<iostream>
#include<utility>
#define ll long long int
using namespace std;

string ceaser_cipher(string msg, int key){
    key %= 26;
    for(int i=0; i<msg.size(); i++){
        
        if(msg[i] > 96){
            msg[i] = ((msg[i] - 97)+key)%26 + 97; 
        } else {
            msg[i] = ((msg[i] - 65)+key)%26 + 65;
        }
    }
    return msg;
}

ll gcd(ll a, ll b)
{
    if (a < b)
        swap(a, b);
    if (b == 0)
        return a;
    return gcd(b, a % b);
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


ll get_random_prime(){
    ll primes[] = {
        101, 103, 107, 
        113, 127, 131, 137,	139, 149, 151, 157, 163, 167,
        173, 179, 181, 191,	193, 197, 199, 211, 223, 227,
        229, 233, 239, 241,	251, 257, 263, 269, 271, 277,
        281, 283, 293, 307,	311, 313, 317, 331, 337, 347,
        349, 353, 359, 367,	373, 379, 383, 389, 397, 401,
        409, 419, 421, 431,	433, 439, 443, 449, 457, 461,
        463, 467, 479, 487,	491, 499, 503, 509, 521, 523,
        541, 547, 557, 563,	569, 571, 577, 587, 593, 599,
        601, 607, 613, 617,	619, 631, 641, 643, 647, 653,
        659, 661, 673, 677,	683, 691, 701, 709, 719, 727,
        733, 739, 743, 751,	757, 761, 769, 773, 787, 797,
        809, 811, 821, 823,	827, 829, 839, 853, 857, 859,
        863, 877, 881, 883,	887, 907, 911, 919, 929, 937,
        941, 947, 953, 967,	971, 977, 983, 991, 997, 109,  
    };
    return primes[rand()%143];
}

pair<pair<ll,ll>, ll> rsa(){


    ll p = get_random_prime();
    ll q = get_random_prime();

    ll n = p*q;
    ll z = (p-1)*(q-1);

    // bruteforcing for e
    ll e = 2;
    while( gcd(e,z) != 1)
        e++;
    
    ll d = modInverse(e, z);

    return {{e,d},n};
    // ENCRYPT with Plain^e mod n
    // DECRYPT with Cipher^d mod n


}

