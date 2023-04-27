/**
 * @file Polynomial.h
 * @author Shounak Ghosh
 * @brief Header file for the Polynomial class
 * @date 2023-04-27
 * 
 */
#include <iostream>
#include <vector>

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
class Polynomial {
private:
    struct Node {
        double coeff;
        int exp;
        Node* next;
        Node(int coeff, int exp, Node* next = nullptr): coeff(coeff), exp(exp), next(next) {}
    };
    Node* head;
    int degree;
public:
    Polynomial(const std::vector<int>& coeffs);
    Polynomial();
    Polynomial(const Polynomial& other);
    Polynomial& operator=(const Polynomial& other);
    Polynomial operator+(const Polynomial& other) const;
    Polynomial& operator+=(const Polynomial& other);
    bool operator==(const Polynomial& other) const;
    bool operator!=(const Polynomial& other) const;
    double evaluate(double x) const;
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
};
#endif