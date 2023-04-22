#include <iostream>
using namespace std;

class PrintedMaterial {
public:
private:
    unsigned numOfPages;
};

class Magazine : public PrintedMaterial {
public:
private:
    unsigned numOfPages;
};

class Book : public PrintedMaterial {
public:
private:
    unsigned numOfPages;
};

class TextBook : public Book {
public:
private:
    unsigned numOfPages;
};

class Novel : public Book {
public:
private:
    unsigned numOfPages;
};

// tester/modeler code
int main() {
    TextBook text;
    Novel novel;
    Magazine mag;
}
