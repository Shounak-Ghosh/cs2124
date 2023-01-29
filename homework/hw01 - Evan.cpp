// Evan Lee
// CS-UY 2124 
// Omar Mansour
// Homework 1

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char decryptCharacter(int rotDist, char origChar);
void decryptString(int rotDist, string& origString);


int main(){ 
    int cypherDist;
    string fileLine;
    vector<string> lineList;
    ifstream encryptStream("encrypted.txt");

    if (!encryptStream){
        cerr << "Mixed file not at location" << endl;
        exit(1);
    }

    encryptStream >> cypherDist;
    while (getline(encryptStream, fileLine)){
        lineList.push_back(fileLine);
    }

    encryptStream.close();

    for (int i = lineList.size()-1; i > 0; i--){
        decryptString(cypherDist, lineList[i]);
        cout << lineList[i] << endl;
    }
    
}

char decryptCharacter(int rotDist, char origChar){
    return (((origChar -'A') + 26 - rotDist)%26 + 'A');
}

void decryptString(int rotDist, string& origString){
    for (char& index : origString){
        if (index >= 'A' && index <= 'Z'){
            index = decryptCharacter(rotDist, index);
        }
    }
}