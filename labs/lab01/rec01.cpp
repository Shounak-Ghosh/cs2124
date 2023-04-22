/*
  Author: Shounak Ghosh
  rec01.cpp
  spring 2023
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
//
// Function prototypes for tasks 15-17
//

// Task 15. Function to display a vector of ints
void display_vector(const std::vector<int>& v);

// Task 16. Function to modify the vector, using indices
void double_vector(std::vector<int>& v);

// Task 17. Function to modify the vector, using a ranged for
void double_vector_ranged(std::vector<int>& v);

//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    std::cout << "Hello, world!" << std::endl;


    // Task 2  Printing hello ...  Using "using namespace"

    cout << "Hello, world!" << endl;

    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    cout << "Uninitialized int: " << x << endl;
    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;

    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    cout << "Size of x: " << sizeof(x) << endl;
    cout << "Size of y: " << sizeof(y) << endl;
    cout << "Size of z: " << sizeof(z) << endl;
    cout << "Size of pie: " << sizeof(pie) << endl;

    // Task 5  Attempt to assign the wrong type of thing to a variable

    // x = "felix" // compilation error

    //
    // Conditions
    //

    // Task 6  Testing for a range
    if (y >= 10 && y <= 20) {
        cout << "y is between 10 and 20" << endl;
    }
    else {
        cout << "y is not between 10 and 20" << endl;
    }

    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
    for (int i = 10; i <= 20; i++) {
        cout << i << " ";
    }
    cout << endl;

    // Then with a while loop
    int i = 10;
    while (i <= 20) {
        cout << i << " ";
        i++;
    }
    cout << endl;

    // Finally with a do-while loop
    i = 10;
    do {
        cout << i << " ";
        i++;
    } while (i <= 20);
    cout << endl;


    // Task 8  Looping to successfully open a file, asking user for the name
    string filename;
    ifstream file(filename);
    while (!file) {
        cout << "Enter a filename: ";
        cin >> filename;
        file.open(filename);

    }




    // Task 9  Looping, reading file word by "word".
    string word;
    while (file >> word) {
        cout << word << endl;
    }
    file.close();


    // Task 10 Open a file of integers, read it in, and display the sum.
    file.open("integers.txt");
    int sum = 0;
    while (file >> x) {
        sum += x;
    }
    file.close();
    cout << "Sum: " << sum << endl;




    // Tasks 11 Open and read a file of integers and words. Display the sum.
    file.open("mixed.txt");
    sum = 0;
    while (file >> x) {
        sum += x;
    }
    file.close();
    cout << "Sum: " << sum << endl;

    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> range;
    for (int i = 10; i <= 100; i += 2) {
        range.push_back(i);
    }


    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for (size_t i = 0; i < range.size(); i++) {
        cout << range[i] << " ";
    }
    cout << endl;

    //         b) using a "ranged for"
    for (int i : range) {
        cout << i << " ";
    }
    cout << endl;

    //         c) using indices again but backwards
    for (size_t i = range.size(); i > 0; i--) {
        cout << range[i - 1] << " ";
    }
    cout << endl;


    // Task 14. Initialize a vector with the primes less than 20. 
    vector<int> primes{ 2, 3, 5, 7, 11, 13, 17, 19 };

    for (int i : primes) {
        cout << i << " ";
    }
    cout << endl;

    //
    // Function calls
    //

    // Task 15  Function to print a vector
    display_vector(primes);

    // // Task 16  Function to double the values in a vector
    double_vector(primes);
    display_vector(primes);


    // // Task 17  Function to double the values in a vector, using a ranged for
    double_vector_ranged(primes);
    display_vector(primes);
}

using namespace std;

//
// Function definitions for tasks 15-17
//

// Task 15. Function to display a vector of ints
void display_vector(const vector<int>& v) {
    for (int i : v) {
        cout << i << " ";
    }
    cout << endl;
}



// Task 16. Function to modify the vector, using indices
void double_vector(vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        v[i] *= 2;
    }
}

// Task 17. Function to modify the vector, using a ranged for
void double_vector_ranged(vector<int>& v) {
    for (int& i : v) {
        i *= 2;
    }
}


