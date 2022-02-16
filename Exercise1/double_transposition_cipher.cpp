#include<iostream>
#include<vector>
using namespace std;

string decrypt(string s, vector<int> &row_per, vector<int> &col_per, int m, int n)
{
    string dec = "";
    vector<vector<char>> v(m,vector<char>(n));
    vector<vector<char>> v1(m,vector<char>(n));
    int k=0;

    for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
    v[i][j] = s[k++];

    
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            v1[i][col_per[j]-1] = v[i][j];
        }
    }

    for(int i=0;i<m;i++)
    {
        v[row_per[i]-1] = v1[i]; 
    }

    for(int i=0;i<m;i++)
    {
        string s1(v[i].begin(), v[i].end());
        dec+=s1; 
    }

    return dec;
}

string encrypt(string s, vector<int> &row_per, vector<int> &col_per, int m, int n)
{
    string enc = "";
    vector<vector<char>> v(m,vector<char>(n));
    vector<vector<char>> v1;
    int k=0;

    for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
    if(k<s.length())
    v[i][j] = s[k++];
    else
    v[i][j] = '*';

    for(int i=0;i<m;i++)
    {
        v1.push_back(v[row_per[i]-1]);
    }

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            v[i][j] = v1[i][col_per[j]-1];
            enc+=v1[i][col_per[j]-1];
        }
    }

    return enc;
}

int main(int argc, char const *argv[])
{
    string msg;
    int m,n;

    cout<<"Enter message: \n";
    cin>>msg;
    cout<<"Enter matrix size in m*n format: \n";
    cin>>m>>n;

    vector<int> row_per(m);
    vector<int> col_per(n);

    cout<<"Enter row permutations: \n";    
    for(int i=0;i<m;i++)
    cin>>row_per[i];

    cout<<"Enter column permutations: \n";    
    for(int i=0;i<n;i++)
    cin>>col_per[i];

    string enc = encrypt(msg,row_per,col_per,m,n);
    cout<<"\nThe encrypted message is: "<<enc<<"\n";

    string dec = decrypt(enc,row_per,col_per,m,n);
    cout<<"\nThe decrypted message is: "<<dec<<"\n";
    return 0;
}
