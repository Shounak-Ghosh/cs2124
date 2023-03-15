// hw01.cpp
// Author: Shounak Ghosh
// Decrypt a caesar cypher message given a shift distance 
// and reverse the order of the message lines, as per the problem statement

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char decrypt_char(char, int); // function prototype for decrypt_char
void decrypt_string(string&, int); // function prototype for decrypt_string

/**
 * @brief decrypts a string using a caesar cypher
 *
 * @return int 0 on success
 */
int main() {
    // Read the file, exit if error
    ifstream infile("encrypted.txt");
    if (!infile) {
        cerr << "Error: could not open file" << endl;
        exit(1);
    }

    // initialize variables for storing file contents
    int shift;
    string line;
    vector<string> lines;

    infile >> shift; // read the shift value
    getline(infile, line); // ignore the newline character

    // read the file line by line
    while (getline(infile, line)) {
        lines.push_back(line);
    }
    infile.close(); // close the file

    // TODO: why is the looping not lines.size()-1 and i >= 0 ?
    // size_t is an unsigned integer type used for array indexing
    // loop through the lines in reverse order and decrypt,
    // as per the problem statement
    for (size_t i = lines.size(); i > 0; --i) {
        decrypt_string(lines[i - 1], shift);
        cout << lines[i - 1] << endl;
    }
    return 0;
}

/**
 * @brief Decrypts a single character
 *
 * @param chr the character to decrypt
 * @param shift  the shift value
 * @return char the decrypted character
 */
char decrypt_char(char chr, int shift) {
    // check if the character is an uppercase letter and decrypt it
    // otherwise, return the character as is
    if (chr >= 'A' && chr <= 'Z')
        return (chr - 'A' - shift + 26) % 26 + 'A';
    else
        return chr;
}

/**
 * @brief Decrypts a string using a caesar cypher
 *
 * @param str The string to decrypt
 * @param shift the shift value
 */
void decrypt_string(string& str, int shift) {
    // decrypt each character in the string
    for (int i = 0; i < str.length(); i++)
        str[i] = decrypt_char(str[i], shift);
}

