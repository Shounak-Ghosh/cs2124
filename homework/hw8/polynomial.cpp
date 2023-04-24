#include <iostream>
#include <vector>
#include "polynomial.h"

using namespace std;

Polynomial::Polynomial(const vector<int>& coeffs) {
    Node* temp = nullptr;
    for (int i = coeffs.size() - 1; i >= 0; i--) {
        if (coeffs[i] != 0) {
            temp = new Node(coeffs[i], (coeffs.size() - 1) - i, temp);
        }
    }
    head = temp;
}

Polynomial::Polynomial() {
    head = nullptr;
}

Polynomial::Polynomial(const Polynomial& other) {
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

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
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
    return result;
}

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

bool Polynomial::operator==(const Polynomial& other) const {
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

bool Polynomial::operator!=(const Polynomial& other) const {
    return !(*this == other);
}

// evaluate the polynomial using Horner's method
int Polynomial::evaluate(int x) const {
    int result = 0;
    Node* temp = head;
    while (temp != nullptr) {
        result = result * x + temp->coeff;
        temp = temp->next;
    }
    return result;
}

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
    // TODO remove
    // while (temp != nullptr) {
    //     os << "(" << temp->coeff << " " << temp->exp << ")";
    //     temp = temp->next;
    // }
    return os;
}
