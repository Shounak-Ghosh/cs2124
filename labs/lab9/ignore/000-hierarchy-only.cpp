#include <iostream>
using namespace std;

class PrintedMaterial {
public:
private:
};

class Magazine : public PrintedMaterial {
public:
private:
};

class Book : public PrintedMaterial {
public:
private:
};

class TextBook : public Book {
public:
private:
};

class Novel : public Book {
public:
private:
};

// tester/modeler code
int main() {
    TextBook text;
    Novel novel;
    Magazine mag;
}
