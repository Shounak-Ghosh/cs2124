#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int data [10] = {0,4,9,16,25,36,49,64,81,100};
    cout << &data[5] << endl;
    cout << (data + 5) << endl;
}