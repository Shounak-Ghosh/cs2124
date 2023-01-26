// h101.cpp
// Author: Shounak Ghosh
// Decrypt a caesar cypher message

#include <iostream>
#include <string>
#include <vector>

using namespace std;

char decrypt_char(char c, int shift) // TODO check if this works for negative shift
{
    if (isalpha(c) && isupper(c)) 
        return (c - 'A' - shift + 26) % 26 + 'A';
    else 
        return c;
}


void decrypt_string(string &s, int shift)
{
    for (int i = 0; i < s.length(); i++)
        s[i] = decrypt_char(s[i], shift);
}

int main() 
{
    int shift;
    string line;
    vector<string> lines;

    
    

    cout << decrypt_char('B', 3) << endl;
}

