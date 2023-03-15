#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


void func(int z) {
    const int * p = &z;
    z = 9;
    cout << *p << ' ';
    //*p = 22;

}

class Container {
public: 
    double capacity() {
        cout << length << ' ' << width << ' ' << height;
        return length * width * height;
    }
private:
    double length;
    double width;
    double height;
};

int main() {
    int data[10] = {0,1,4,9,16,25,36,49,64,81};
    int* p = &data[5];
     cout << *p << endl;
     cout << p[-2] << endl;

     Container box;

     cout << box.capacity() << endl;

}

