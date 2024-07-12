// Omer Cohen
// omer7530@gmail.com

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <string>
#include <iostream>

class Complex {
    double real;
    double imag;

public:
    // Constructor
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    std::string to_string() const {
        return std::to_string(real) + " + " + std::to_string(imag) + "i";
    }

    bool operator==(const Complex &c) const
    {
        return real == c.real && imag == c.imag;
    }

    bool operator!=(const Complex &c) const
    {
        return !(*this == c);
    }

    friend std::ostream &operator<<(std::ostream &os, const Complex &c)
    {
        os << c.real << "+" << c.imag << "i";
        return os;
    }
};


#endif // COMPLEX_HPP