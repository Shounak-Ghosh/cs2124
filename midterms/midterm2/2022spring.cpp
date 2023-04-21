#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Movie {
    public:
        Movie() {
            title = "cas";
            length = 17;
        }

        Movie (int length, string title): title(title), length(length) {}

        void display() {
            cout << title << " " << length << endl;
        }

    private:
        string title;
        int length;
};

const int INIT_BALANCE = 200;
class Account
{
public:
    Account() : balance(INIT_BALANCE) {}
    virtual void display_balance() { cout << "Balance is " << balance << endl; } // Line 1
protected:
    int get_balance() const { return balance; } // Line 2
private:
    int balance;
};
class CheckingAccount : public Account
{
public:
    CheckingAccount() {}
    void display_balance() override {                                                    // Line 3
        cout << "Checking balance is " << get_balance() << endl; // Line 4
    }
};

class Bird
{
public:
    virtual void chirp() { cout << "chirp"; }
}; // Line 1
class Parrot : public Bird
{
    void chirp(string phrase) { cout << phrase; }
}; // Line 2


class EyeWear {
    public:
        void set_strength(int s) {strength = s;}
        int get_strength() {return strength;}
    private:
        int strength;
};

class ContactLens : public EyeWear {
    public:
        void set_diameter(double d) {diameter = d;}
        double get_diameter() {return diameter;}
    private:
        double diameter;
};

// void output(EyeWear ew) {
//     cout << "diameter is " << ew.get_diameter() << endl;
// }



int main() {
    Movie mov;
    cout << &mov << endl;
    mov = {42,"a"};   
    cout << &mov << endl;
    mov.display();

    Account acct;
    cout << &acct << endl;
    CheckingAccount ca;
    cout << &ca << endl;
    acct = ca;
    acct.display_balance();
    ca.display_balance();

    cout << &acct << endl;
    cout << &ca << endl;

    int val = 7;
    int* arr = new int[5];

    for (int i = 0; i < 5; i++) {
        arr[i] = val + i;
    }

    int* ptr_p = arr + 5 - 2;
    int* ptr_q = ptr_p + 1;

    cout << "X: " << *ptr_q << endl;
    *ptr_p = val;
    ++ptr_p;
    cout << "Y: " << *ptr_p << endl;

    delete[] arr;

    ContactLens obj;
    obj.set_strength(5);
    obj.set_diameter(8.2);
    EyeWear* ew = &obj;
    // cout << (*ew).get_diameter() << endl;
}