/**
 * @file Polynomial.cpp
 * @author Shounak Ghosh
 * @brief Implementation of the Polynomial class
 * @date 2023-04-27
 *
 */
#include <iostream>
#include <vector>
#include "polynomial.h"

using namespace std;

/**
 * @brief Default constructor for a Polynomial object
 *
 */
Polynomial::Polynomial(): degree(0), head(new Term(0, 0, nullptr)) {}

/**
 * @brief Constructor for a Polynomial object
 *
 * @param coeffs a vector of coefficients for the polynomial
 *               with the first element being the coefficient
 *               of the highest degree term
 */
Polynomial::Polynomial(const vector<int>& coeffs) {
    int numZeroes = 0;
    for (size_t i = 0; i < coeffs.size(); ++i) {
        if (coeffs[i] == 0) {
            numZeroes++;
        }
        else {
            break;
        }
    }
    Term* curs = nullptr; // short for cursor
    for (size_t i = numZeroes; i < coeffs.size(); ++i) {
        curs = new Term(coeffs[i], (coeffs.size() - 1) - i, curs);
    }

    // reverse the order of the nodes so largest exponent is first
    Term* prev = nullptr;
    Term* curr = curs;
    while (curr != nullptr) {
        Term* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    degree = coeffs.size() - numZeroes - 1;
}

/**
 * @brief Destructor for Polynomial object
 * 
 */
Polynomial::~Polynomial() {
    Term* curs = head;
    while (curs != nullptr) {
        Term* next = curs->next;
        delete curs;
        curs = next;
    }
    head = nullptr;
}

/**
 * @brief Copy constructor for a Polynomial object
 *
 * @param other the Polynomial object to be copied from
 */
Polynomial::Polynomial(const Polynomial& other): degree(other.degree) {
    Term* curs = nullptr;
    Term* otherCurs = other.head;
    while (otherCurs != nullptr) {
        curs = new Term(otherCurs->coeff, otherCurs->exp, curs);
        otherCurs = otherCurs->next;
    }
    head = curs;
    // reverse the order of the nodes so largest exponent is first
    Term* prev = nullptr;
    Term* curr = head;
    while (curr != nullptr) {
        Term* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

/**
 * @brief Assignment operator for a Polynomial object
 *
 * @param other the Polynomial object to be copied from
 * @return Polynomial& the Polynomial object that was assigned to
 */
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        degree = other.degree;
        Term* curs = head;
        while (curs != nullptr) {
            Term* next = curs->next;
            delete curs;
            curs = next;
        }
        curs = nullptr;
        Term* otherCurs = other.head;
        while (otherCurs != nullptr) {
            curs = new Term(otherCurs->coeff, otherCurs->exp, curs);
            otherCurs = otherCurs->next;
        }
        head = curs;
        // reverse the order of the nodes so largest exponent is first
        Term* prev = nullptr;
        Term* curr = head;
        while (curr != nullptr) {
            Term* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }
    return *this;
}

/**
 * @brief Overloaded addition operator for two Polynomial objects
 *
 * @param lhs the first Polynomial object to be added
 * @param rhs the second Polynomial object to be added
 * @return Polynomial the Polynomial object that is the sum of lhs and rhs
 */
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial result = lhs;
    result += rhs;
    return result;
}

/**
 * @brief Overloaded addition assignment operator for a Polynomial object
 *
 * @param other the Polynomial object to be added to this
 * @return Polynomial& the Polynomial object that was added to
 */
Polynomial& Polynomial::operator+=(const Polynomial& other) {
    Term* curs = head;
    Term* otherCurs = other.head;
    // perform addition
    while (curs != nullptr && otherCurs != nullptr) {
        if (curs->exp == otherCurs->exp) {
            curs->coeff += otherCurs->coeff;
            curs = curs->next;
            otherCurs = otherCurs->next;
        }
        else if (curs->exp > otherCurs->exp) {
            curs = curs->next;
        }
        else {
            Term* newNode = new Term(otherCurs->coeff, otherCurs->exp, curs);
            if (curs == head) {
                head = newNode;
            }
            else {
                Term* prev = head;
                while (prev->next != curs) {
                    prev = prev->next;
                }
                prev->next = newNode;
            }
            otherCurs = otherCurs->next;
        }
    }
    // add remaining terms
    while (otherCurs != nullptr) {
        Term* newTerm = new Term(otherCurs->coeff, otherCurs->exp, curs);
        if (curs == head) {
            head = newTerm;
        }
        else {
            Term* prev = head;
            while (prev->next != curs) {
                prev = prev->next;
            }
            prev->next = newTerm;
        }
        otherCurs = otherCurs->next;
    }
    // remove leading 0 coefficients
    curs = head;
    Term* prev = nullptr;
    while (curs != nullptr) {
        if (curs->coeff == 0) {
            Term* next = curs->next;
            delete curs;
            curs = next;
            if (prev == nullptr) {
                head = curs;
            }
            else {
                prev->next = curs;
            }
        }
        else {
            prev = curs;
            curs = curs->next;
        }
    }
    degree = head->exp;
    return *this;
}

/**
 * @brief Checks if two Polynomial objects are equal
 *
 * @param lhs the first Polynomial object to be compared
 * @param rhs the second Polynomial object to be compared
 * @return true if the two polynomials match
 * @return false otherwise
 */
bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    if (lhs.degree != rhs.degree) {
        return false;
    }
    Polynomial::Term* lhsCurs = lhs.head;
    Polynomial::Term* rhsCurs = rhs.head;
    while (lhsCurs != nullptr && rhsCurs != nullptr) {
        if (lhsCurs->coeff != rhsCurs->coeff || lhsCurs->exp != rhsCurs->exp) {
            return false;
        }
        lhsCurs = lhsCurs->next;
        rhsCurs = rhsCurs->next;
    }
    return true;
}

/**
 * @brief Checks if two Polynomial objects are not equal
 * 
 * @param lhs the first Polynomial object to be compared
 * @param rhs the second Polynomial object to be compared
 * @return true if the two polynomials do not match
 * @return false otherwise
 */
bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
    return !(lhs == rhs);
}

/**
 * @brief Evaluates this polynomial using Horner's method
 *
 * @param x the value to be evaluated at
 * @return int
 */
double Polynomial::evaluate(double x) const {
    double result = 0;
    Term* curs = head;
    while (curs != nullptr) {
        result = result * x + curs->coeff;
        curs = curs->next;
    }
    return result;
}

/**
 * @brief Overloaded output operator for a Polynomial object
 *
 * @param os the output stream
 * @param poly the Polynomial object to be output
 * @return ostream& the output stream
 */
ostream& operator<<(ostream& os, const Polynomial& poly) {
    for (Polynomial::Term* curs = poly.head; curs != nullptr; curs = curs->next) {
        if (curs->coeff != 0 || curs->exp == 0) {
            if (curs->coeff > 0 && curs != poly.head && curs->coeff > 0) {
                os << "+";
            }
            if (curs->coeff == -1 && curs->exp != 0) {
                os << "-";
            }
            else if (curs->coeff != 1 || curs->exp == 0) {
                os << curs->coeff;
            }
            if (curs->exp != 0) {
                os << "x";
                if (curs->exp != 1) {
                    os << "^" << curs->exp;
                }
            }
        }
    }
    return os;
}
