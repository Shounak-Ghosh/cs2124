#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// #3 mc
void foo(int& x) {
    int* const p = &x;
    x = 17;
    cout << *p << ' ';
    *p = 28;

}

class Thing {
public:
    Thing(int val = 17): n(val) {}

    void display() { cout << "Thing: " << n << endl; }
private:
    int n;
};

class ThingHolder {
public:
    //   ThingHolder() {something = Thing(42);}
    void display() {
        //something.display();
        cout << "ThingHolder\n";
    }
private:
    //Thing something(42);
};

int* foo2() {
    int x = 19230;
    return &x;
}

void num7() {
    int x = 6;
    int* arr = new int[8];
    for (int i = 0; i < 8; ++i) {
        arr[i] = i * i;
    }
    int* p = arr + 1;
    int* q = p + x;
    cout << "A: " << *q << endl;
    *p = x;
    ++p;
    cout << "B: " << *p << endl;
}

struct Thing2 {
    vector<int> stuff;
};

void fill(ifstream& ifs, vector<Thing2>& things) {
    int nStuff;
    while (ifs >> nStuff) {
        Thing2 t;
        int s;
        for(size_t i = 0; i < nStuff; ++i) {
            ifs >> s;
            t.stuff.push_back(s);
        }
        things.push_back(t);
    }
}

int totalStuff(const vector<Thing2>& things) {
    int ans = 0;
    for (size_t i = 0; i < things.size(); i++) {
        for (size_t j = 0; j < things[i].stuff.size(); ++j) {
            ans += things[i].stuff[j];
        }
    }
    return ans;
}


int main() {
    int y = 42;
    foo(y);
    cout << y << endl;

    ThingHolder th;
    th.display();

    int* yy = foo2();
    cout << *yy << endl;

    num7();


    ifstream ifs("fillThing.txt");
    vector<Thing2> v;
    fill(ifs,v);

    for (Thing2& t: v) {
        for (int i: t.stuff) {
            cout << i << " ";
        }
        cout << endl;
    }
    ifs.close();

    cout << totalStuff(v);
}