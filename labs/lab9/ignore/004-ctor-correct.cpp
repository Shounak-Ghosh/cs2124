#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numPages)
	: numOfPages(numPages)
    {}
private:
    unsigned numOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages)
	: PrintedMaterial(numPages)
    {}
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages)
	: PrintedMaterial(numPages)
    {}
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages)
	: Book(numPages)
    {}
private:
};

class Novel : public Book {
public:
    Novel(unsigned numPages)
	: Book(numPages)
    {}
private:
};

// tester/modeler code
int main() {
    TextBook t(5430);
    Novel n(213);
    Magazine m(6);
}
