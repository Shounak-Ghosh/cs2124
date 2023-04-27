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
Polynomial::Polynomial(): degree(0) {
    // TODO: fix issue when head is new Node in default constructor
    head =  nullptr;// new Node(0,0,nullptr);
}

/**
 * @brief Constructor for a Polynomial object
 * 
 * @param coeffs a vector of coefficients for the polynomial 
 *               with the first element being the coefficient 
 *               of the highest degree term
 */
Polynomial::Polynomial(const vector<int>& coeffs) {
    Node* temp = nullptr;
    for (int i = coeffs.size() - 1; i >= 0; i--) {
        if (coeffs[i] != 0) {
            temp = new Node(coeffs[i], (coeffs.size() - 1) - i, temp);
        }
    }
    head = temp;
    degree = head->exp;
}

/**
 * @brief Copy constructor for a Polynomial object
 * 
 * @param other the Polynomial object to be copied from
 */
Polynomial::Polynomial(const Polynomial& other): degree(other.degree) {
    Node* temp = nullptr;
    Node* otherTemp = other.head;
    while (otherTemp != nullptr) {
        temp = new Node(otherTemp->coeff, otherTemp->exp, temp);
        otherTemp = otherTemp->next;
    }
    head = temp;
    // reverse the order of the nodes so largest exponent is first
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        Node* next = curr->next;
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
        Node* temp = head;
        while (temp != nullptr) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
        temp = nullptr;
        Node* otherTemp = other.head;
        while (otherTemp != nullptr) {
            temp = new Node(otherTemp->coeff, otherTemp->exp, temp);
            otherTemp = otherTemp->next;
        }
        head = temp;
        // reverse the order of the nodes so largest exponent is first
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }
    return *this;
}

/**
 * @brief Overloaded addition operator for a Polynomial object
 * 
 * @param other the Polynomial object to be added to this 
 * @return Polynomial the Polynomial object that is the sum of this and other
 */
Polynomial Polynomial::operator+(const Polynomial& other) const {
    Polynomial result;
    Node* temp = head;
    Node* otherTemp = other.head;
    while (temp != nullptr && otherTemp != nullptr) {
        if (temp->exp == otherTemp->exp) {
            if (temp->coeff + otherTemp->coeff != 0) {
                result.head = new Node(temp->coeff + otherTemp->coeff, temp->exp, result.head);
            }
            temp = temp->next;
            otherTemp = otherTemp->next;
        }
        else if (temp->exp > otherTemp->exp) {
            result.head = new Node(temp->coeff, temp->exp, result.head);
            temp = temp->next;
        }
        else {
            result.head = new Node(otherTemp->coeff, otherTemp->exp, result.head);
            otherTemp = otherTemp->next;
        }
    }
    while (temp != nullptr) {
        result.head = new Node(temp->coeff, temp->exp, result.head);
        temp = temp->next;
    }
    while (otherTemp != nullptr) {
        result.head = new Node(otherTemp->coeff, otherTemp->exp, result.head);
        otherTemp = otherTemp->next;
    }
    // reverse the nodes so that the largest exponent is first
    Node* prev = nullptr;
    Node* curr = result.head;
    while (curr != nullptr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    result.head = prev;
    result.degree = result.head->exp;
    return result;
}

/**
 * @brief Overloaded addition assignment operator for a Polynomial object
 * 
 * @param other the Polynomial object to be added to this
 * @return Polynomial& the Polynomial object that was added to
 */
Polynomial& Polynomial::operator+=(const Polynomial& other) {
    *this = *this + other;
    // reverse the nodes so that the largest exponent is first
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return *this;
}

/**
 * @brief Overloaded equality operator for a Polynomial object
 * 
 * @param other the Polynomial object to be compared to this
 * @return true if the two polynomials match 
 * @return false otherwise
 */
bool Polynomial::operator==(const Polynomial& other) const {
    if (degree != other.degree) {
        return false;
    }
    Node* temp = head;
    Node* otherTemp = other.head;
    while (temp != nullptr && otherTemp != nullptr) {
        if (temp->coeff != otherTemp->coeff || temp->exp != otherTemp->exp) {
            return false;
        }
        temp = temp->next;
        otherTemp = otherTemp->next;
    }
    return temp == nullptr && otherTemp == nullptr;
}

/**
 * @brief Overloaded inequality operator for a Polynomial object
 * 
 * @param other the Polynomial object to be compared to this
 * @return true if the two polynomials do not match
 * @return false otherwise
 */
bool Polynomial::operator!=(const Polynomial& other) const {
    return !(*this == other);
}

/**
 * @brief Evaluates this polynomial using Horner's method
 * 
 * @param x the value to be evaluated at
 * @return int 
 */
double Polynomial::evaluate(double x) const {
    double result = 0;
    Node* temp = head;
    while (temp != nullptr) {
        result = result * x + temp->coeff;
        temp = temp->next;
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
    Polynomial::Node* temp = poly.head;
    while (temp != nullptr) {
        if (temp->coeff > 0 && temp != poly.head) {
            os << "+";
        }
        if (temp->coeff == -1 && temp->exp != 0) {
            os << "-";
        }
        else if (temp->coeff != 1 || temp->exp == 0) {
            os << temp->coeff;
        }
        if (temp->exp != 0) {
            os << "x";
            if (temp->exp != 1) {
                os << "^" << temp->exp;
            }
        }
        temp = temp->next;
    }
    os << "\tdegree: " << poly.degree;
    // TODO remove
    // while (temp != nullptr) {
    //     os << "(" << temp->coeff << " " << temp->exp << ")";
    //     temp = temp->next;
    // }
    return os;
}
