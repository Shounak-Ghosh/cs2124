#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    void displayNumPages() const { cout << numOfPages; }
private:
    unsigned numOfPages;
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

    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();
    cout << "===========\n";
}
