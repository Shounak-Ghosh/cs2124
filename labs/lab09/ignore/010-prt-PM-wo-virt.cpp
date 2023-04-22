#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numPages)
	: numOfPages(numPages)
    {}
    void displayNumPages() const { cout << numOfPages << endl; }
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
    TextBook(unsigned numPages, unsigned numIndxPgs )
	: Book(numPages),
	  numOfIndexPages(numIndxPgs)
    {}
    void displayNumPages() const {
	cout << "Pages: ";
	PrintedMaterial::displayNumPages();
	cout << "Index pages: ";
	cout << numOfIndexPages << endl; 
    }
private:
    unsigned numOfIndexPages;
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
    TextBook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);

    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();
    cout << "===========\n";

    cout << "\nA PrintedMaterial material object!\n";
    PrintedMaterial pm(2345);
    pm.displayNumPages();

    cout << "\nA PrintedMaterial variable containing a TextBook value\n";
    pm = text; // like putting a Textbook into a PrintedMaterial
    pm.displayNumPages();

    cout << "Try using pointer to base type\n";
    PrintedMaterial* pmPtr;
    pmPtr = &text; 

    pmPtr->displayNumPages(); 
}
