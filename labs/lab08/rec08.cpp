// TODO: implement seperate compilation
/*
    rec08.cpp
    Author: Shounak Ghosh
    March 24 2023
    CS2124
    Implement the class Rational, so that the following program works.
 */

#include <iostream>

 // If time allows use separate compilation, otherwise just define the
 // class below with the methods / functions defined after main.
 // #include "Rational.h"

using namespace std;

// If time allows after implementing separate compilation, then wrap
// the class in a namespace.
// using namespace CS2124;

class Rational {
public:
    // member function prototypes
    Rational(int numerator = 0, int denominator = 1);
    Rational& operator+=(const Rational& rhs);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
    Rational& operator++();	// Pre-increment
    Rational operator++(int);	// Post-increment
    explicit operator bool() const;
    friend ostream& operator<<(ostream& os, const Rational& rhs);
    friend istream& operator>>(istream& is, Rational& rhs);
private:
    int greatestCommonDivisor(int x, int y) {
        while (y != 0) {
            int temp = x % y;
            x = y;
            y = temp;
        }
        return x;
    }

    int numerator;
    int denominator;
};

// non-member function prototypes
Rational operator+(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& rhs);
Rational operator--(Rational& rhs, int);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);

int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;

    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    //It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    }
    else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    }
    else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
        << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
        << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
        << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
        << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
        << (minusFive >= threeHalves) << endl;
}

Rational::Rational(int numerator, int denominator) {
    int gcd = greatestCommonDivisor(numerator, denominator);
    this->numerator = numerator / gcd;
    this->denominator = denominator / gcd;
    if (this->denominator < 0) {
        this->numerator *= -1;
        this->denominator *= -1;
    }
}

Rational& Rational::operator+=(const Rational& rhs) {
    numerator = numerator * rhs.denominator + rhs.numerator * denominator;
    denominator *= rhs.denominator;
    int gcd = greatestCommonDivisor(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
    return *this;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);
    result += rhs;
    return result;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator;
}

Rational& Rational::operator++() {
    numerator += denominator;
    return *this;
}

Rational Rational::operator++(int) {
    Rational result(*this);
    ++(*this);
    return result;
}

Rational& operator--(Rational& rhs) {
    rhs += -1;
    return rhs;
}

Rational operator--(Rational& rhs, int) {
    Rational result(rhs);
    --rhs;
    return result;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

Rational::operator bool() const {
    return numerator != 0;
}   

ostream& operator<<(ostream& out, const Rational& rhs) {
    out << rhs.numerator << "/" << rhs.denominator;
    return out;
}

istream& operator>>(istream& in, Rational& rhs) {
    char slash;
    in >> rhs.numerator >> slash >> rhs.denominator;
    rhs = Rational(rhs.numerator, rhs.denominator);
    return in;
}














