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
    struct Term {
        int coeff;
        int exp;
        Term* next;
        Term(int coeff, int exp, Term* next = nullptr): coeff(coeff), exp(exp), next(next) {}
    };
    Term* head;
    int degree;
public:
    Polynomial(const std::vector<int>& coeffs);
    Polynomial();
    Polynomial(const Polynomial& other);
    ~Polynomial();
    Polynomial& operator=(const Polynomial& other);
    Polynomial& operator+=(const Polynomial& other);
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    double evaluate(double x) const;
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
};
bool operator !=(const Polynomial& lhs, const Polynomial& rhs);
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
#endif