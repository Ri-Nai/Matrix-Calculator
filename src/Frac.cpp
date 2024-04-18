/*
 * @Author: Reina__
 * @Date: 2024-04-18 13:43:55
 * @Last Modified by: Reina__
 * @Last Modified time: 2024-04-18 21:54:43
 */
#include "Frac.h"
Frac::Frac()
{
    numerator = 0;
    denominator = 1;
}
Frac::Frac(double dec)
{
    int base = 1e6;
    int num = round(dec * base);
    *this = Frac(num, base);
}
template <typename number>
Frac::Frac(number num, number den)
{
    if (den < 0)
        den = -den, num = -num;
    numerator = num;
    denominator = den;
    int gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
}

int Frac::Get_Numerator() const
{
    return numerator;
}

int Frac::Get_Denominator() const
{
    return denominator;
}

Frac Frac::operator+(const Frac &other) const
{
    int newNumerator = numerator * other.denominator + other.numerator * denominator;
    int newDenominator = denominator * other.denominator;
    return Frac(newNumerator, newDenominator);
}

Frac Frac::operator-(const Frac &other) const
{
    int newNumerator = numerator * other.denominator - other.numerator * denominator;
    int newDenominator = denominator * other.denominator;
    return Frac(newNumerator, newDenominator);
}

Frac Frac::operator*(const Frac &other) const
{
    int newNumerator = numerator * other.numerator;
    int newDenominator = denominator * other.denominator;
    return Frac(newNumerator, newDenominator);
}

Frac Frac::operator/(const Frac &other) const
{
    int newNumerator = numerator * other.denominator;
    int newDenominator = denominator * other.numerator;
    return Frac(newNumerator, newDenominator);
}

Frac Frac::operator*(const int &p) const
{
    return Frac(numerator * p, denominator);
}

Frac operator*(const int &p, const Frac &frac)
{
    return frac * p;
}

Frac Frac::operator-() const
{
    return Frac(-numerator, denominator);
}

bool Frac::operator<(const Frac &other) const
{
    return numerator * other.denominator - other.numerator * denominator < 0;
}
bool Frac::operator>(const Frac &other) const
{
    return other < *this;
}
bool Frac::operator<=(const Frac &other) const
{
    return !(*this > other);
}
bool Frac::operator>=(const Frac &other) const
{
    return !(*this < other);
}
bool Frac::operator==(const Frac &other) const
{
    return *this >= other && *this <= other;
}
bool Frac::operator!=(const Frac &other) const
{
    return !(*this == other);
}

Frac abs(const Frac &frac)
{
    if (frac.Get_Numerator() < 0)
        return Frac(-frac.Get_Numerator(), -frac.Get_Denominator());
    return frac;
}
// 使分数比较格式化地输出
// 由于难以调教std::format,自己写了一个很丑陋的
std::string Frac::Format_Output(const int &place) const
{
    std::stringstream ss;
    std::string result = "";
    ss << *this;
    ss >> result;
    int length = result.size();
    if (length >= place)
        return " " + result + " ";
    int rest = place - length;
    int middle = rest / 2;
    result = std::string(middle, ' ') + result + std::string(rest - middle, ' ');
    return result;
}

std::ostream &operator<<(std::ostream &os, const Frac &frac)
{
    if (frac.denominator == 1)
        os << frac.numerator;
    else if (frac.numerator == 0)
        os << 0;
    else
        os << frac.numerator << "/" << frac.denominator;
    return os;
}

std::istream &operator>>(std::istream &is, Frac &frac)
{
    std::string input;
    is >> input;

    // 将输入字符串解析为分子和分母
    std::istringstream iss(input);
    char slash;
    int num, den;
    if (iss >> num >> slash >> den && slash == '/')
    {
        frac = Frac(num, den);
        // 成功解析为分数
        // Ciallo～(∠・ω< )⌒★
    }
    else
    {
        double decimal;
        iss.clear();
        iss.seekg(0);
        // 解析为小数
        if (iss >> decimal)
        {
            frac = Frac(decimal);
        }
        else
        {
            // 解析无法解析成数值返回错误
            frac = Frac(0);
            is.setstate(std::ios::failbit);
        }
    }

    return is;
}
