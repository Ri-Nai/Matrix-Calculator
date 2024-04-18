/*
 * @Author: Reina__
 * @Date: 2024-04-18 13:44:09
 * @Last Modified by: Reina__
 * @Last Modified time: 2024-04-18 21:54:34
 */
#ifndef FRAC_H
#define FRAC_H
#include <cmath>
#include <string>
#include <numeric>
#include <sstream>
#include <iostream>

class Frac
{
private:
    int numerator;
    int denominator;

public:
    Frac();
    Frac(double dec);
    template <typename number>
    Frac(number num, number den = 1);

    int Get_Numerator() const;
    int Get_Denominator() const;

    Frac operator+(const Frac &other) const;
    Frac operator-(const Frac &other) const;
    Frac operator/(const Frac &other) const;
    Frac operator*(const Frac &other) const;
    Frac operator*(const int &p) const;
    Frac operator-() const;

    bool operator<(const Frac &other) const;
    bool operator>(const Frac &other) const;
    bool operator<=(const Frac &other) const;
    bool operator>=(const Frac &other) const;
    bool operator==(const Frac &other) const;
    bool operator!=(const Frac &other) const;

    std::string Format_Output(const int &place) const;
    friend std::istream &operator>>(std::istream &is, Frac &frac);
    friend std::ostream &operator<<(std::ostream &os, const Frac &frac);
    friend Frac operator*(const int &p, const Frac &frac);
};
Frac abs(const Frac &frac);

#endif
