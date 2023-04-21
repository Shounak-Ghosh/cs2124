#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Widget {
    public:
        virtual void test(const string& status)  const {
            cout << "Widget's status: " << status << endl;
        }
    
};

class Gadget : public Widget {
    public:
        void test(const string& status) {
            cout << "Gadget's status: " << status << endl;
        }
};

void check(const Widget& w, const string& status) {
    w.test(status);
}

int main() {
    Widget * gad = new Gadget();
    string status_str = "Gadget is working.";
    check(*gad, status_str);
}
