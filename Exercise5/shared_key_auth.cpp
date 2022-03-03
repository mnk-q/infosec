// User X and Y both have secret key KAB

// User X sends the user name and random challenge R2 to user Y.


// User Y encrypts the R2 using symmetric key KAB. Y generates its own random 
//- challenge R1 and sends both R1 and encrypted R2 to X.

// User X verify encrypted R2. and encrypt the R1 with symmetric key KAB and 
//- send it to Y. user Y verifies encrypted R1.  

#include<iostream>
#include<vector>
#include "algos.h"
using namespace std;

vector<string> buffer;

class Person{
    private :
        int key;
        string send_challange;
    public:
        string other,rcv_challange;
        string name; 

        Person(int k, string n){
            key = k;
            name = n;
        }
        string encrypt(string message){
            return ceaser_cipher(message, key%26);
        }
        string decrypt(string msg){
            return ceaser_cipher(msg, 26-(key%26));
        }
        string generate_random_challange(int size = 8){
            string word;
            for(int i=0; i<size; i++)   
                word += 'a'+((rand()%26));
            send_challange = word;

            return word;
        }
        void accept_connection(string party_name, string party_challange){
            other = party_name;
            rcv_challange = encrypt(party_challange);
        }

        bool compare(string recevied){
            cout << "Object word " << send_challange << " Recevied " << recevied << endl << endl; 
            if(decrypt(recevied) == send_challange)
                return true;
            return false;
        }
        
};

int main(){

    Person alice(3, "Alice"), bob(3, "Bob");

    buffer.push_back(alice.name);
    buffer.push_back(alice.generate_random_challange());

    cout << "Bob Received : " << buffer[0] << " " << buffer[1] << endl << endl;
    

    bob.accept_connection(buffer[0], buffer[1]);
    buffer.clear();

    buffer.push_back(bob.generate_random_challange());
    buffer.push_back(bob.rcv_challange);

    cout << "Alice Received : " << buffer[0] << " " << buffer[1] << endl << endl;;

    alice.accept_connection(bob.name, buffer[0]);

    
    bool ok1 = alice.compare(buffer[1]);
    buffer.clear();

    buffer.push_back(alice.rcv_challange);

    bool ok2 = bob.compare(buffer[0]);

    buffer.clear();

    if(ok1 && ok2){
        cout << "Authenticated";
    } else {
        cout << "Not Authenticated";
    }




    return 0;
}