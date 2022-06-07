//
// Created by user on 19.03.2022.
//

#include "Polynomial.h"

//    конструктор
Polynomial::Polynomial (int termAmount)
{
    while(termAmount < 1)
    {
        std::cout << "Input correct term's amount" << std::endl;
        std::cin >> termAmount;
    }

    int power;
    double coefficient;

    while (termAmount--)
    {
        std::cout << "input power and coefficient" << std::endl;
        std::cin >> power >> coefficient;

        if(polynom.find(power) != polynom.end())
        {
            polynom[power] += coefficient;
        } else {
            polynom[power] = coefficient;
        }
    }
}

//    конструктор
Polynomial::Polynomial(std::map<int, double> polynomInit) : polynom(polynomInit)
{}

// конструктор копирования
Polynomial::Polynomial (const Polynomial &polynomial)=default;

//оператор присваивания
Polynomial& Polynomial::operator=(const Polynomial &polynomial)
{
    if (this == &polynomial)
        return *this;

    polynom = polynomial.polynom;

    return *this;
}

//оператор равенства ==
bool Polynomial::operator==(const Polynomial &polynomOther)
{
    if (this == &polynomOther)
    {
        return true;
    }

    int thisSize = this->polynom.size();
    int otherSize = polynomOther.polynom.size();

    if(thisSize != otherSize)
    {
        return false;
    }

    for(auto i : this->polynom)
    {
        if(polynomOther.polynom.find(i.first) == polynomOther.polynom.end())
        {
            return false;
        }

        if(polynomOther.polynom.at(i.first) != i.second)
        {
            return false;
        }
    }

    return true;
}

//оператор не равенства !=
bool Polynomial::operator!=(const Polynomial &polynomOther)
{
    if (this == &polynomOther)
    {
        return false;
    }

    int thisSize = this->polynom.size();
    int otherSize = polynomOther.polynom.size();

    if(thisSize != otherSize)
    {
        return true;
    }

    for(auto i : this->polynom)
    {
        if(polynomOther.polynom.find(i.first) == polynomOther.polynom.end())
        {
            return true;
        }

        if(polynomOther.polynom.at(i.first) != i.second)
        {
            return true;
        }
    }

    return false;
}

//оператор сложения +
Polynomial Polynomial::operator+(const Polynomial &polynomOther)
{
    auto sumPolynom = this -> polynom;
    for(auto i : polynomOther.polynom)
    {
        if(sumPolynom.find(i.first) != sumPolynom.end())
        {
            sumPolynom[i.first] += i.second;

        } else {
            sumPolynom[i.first] = i.second;
        }
    }

    return Polynomial(sumPolynom);
}

//оператор вычитания -
Polynomial Polynomial::operator-(const Polynomial &polynomOther)
{
    auto sumPolynom = this -> polynom;
    for(auto i : polynomOther.polynom)
    {
        if(sumPolynom.find(i.first) != sumPolynom.end())
        {
            sumPolynom[i.first] -= i.second;

        } else {
            sumPolynom[i.first] = -1 * i.second;
        }
    }

    return Polynomial(sumPolynom);
}

//оператор унарный -
Polynomial Polynomial::operator-()
{
    auto inversPolynom = this ->polynom;
    for(auto &i : inversPolynom)
    {
        i.second *= -1;
    }

    return Polynomial(inversPolynom);
}

//оператор сложение с присваивание +=
Polynomial& Polynomial::operator+=(const Polynomial &polynomial)
{
    for(auto i : polynomial.polynom)
    {
        if(this -> polynom.find(i.first) != this -> polynom.end())
        {
            this->polynom[i.first] += i.second;

        } else {
            this->polynom[i.first] = i.second;
        }
    }

    return *this;
}

//оператор вычитание с присваиванием -=
Polynomial& Polynomial::operator-=(const Polynomial &polynomial)
{
    for(auto i : polynomial.polynom)
    {
        if(this -> polynom.find(i.first) != this -> polynom.end())
        {
            this->polynom[i.first] -= i.second;

        } else {
            this->polynom[i.first] = -1 * i.second;
        }
    }

    return *this;
}

//оператор умножение на многочлен *
Polynomial Polynomial::operator*(const Polynomial &polynomOther)
{
    std::map<int, double> compPolynom;
    int power;
    double coefficient;
    for(auto i : this -> polynom)
    {
        for(auto j : polynomOther.polynom)
        {
            power = i.first + j.first;
            coefficient = i.second * j.second;
            if(compPolynom.find(power) != compPolynom.end())
            {
                compPolynom[power] += coefficient;

            } else {
                compPolynom[power] = coefficient;
            }
        }
    }

    return Polynomial(compPolynom);
}

//оператор деление на число /
Polynomial Polynomial:: operator/(double numb)
{
    try {
        if(numb == 0)
        {
            throw std::logic_error("Zero division.");
        }

        auto divPolynom = this->polynom;
        for (auto &i : divPolynom) {
            i.second /= numb;
        }

        return Polynomial(divPolynom);
    }
    catch (const std::logic_error &err)
    {
        std::cerr << err.what() << std::endl;
        return Polynomial(this -> polynom);
    }
}

//оператор умножение c присваиванием *=
Polynomial& Polynomial::operator*=(const Polynomial &polynomial)
{
    std::map<int, double> compPolynom;
    int power;
    double coefficient;
    for(auto i : this -> polynom)
    {
        for(auto j : polynomial.polynom)
        {
            power = i.first + j.first;
            coefficient = i.second * j.second;
            if(compPolynom.find(power) != compPolynom.end())
            {
                compPolynom[power] += coefficient;

            } else {
                compPolynom[power] = coefficient;
            }
        }
    }
    this -> polynom = compPolynom;
    return *this;
}

//оператор деление c присваиванием /=
Polynomial& Polynomial::operator/=(double numb)
{
    try {
        if(numb == 0)
        {
            throw std::logic_error("Zero division.");
        }

        for (auto &i : this -> polynom) {
            i.second /= numb;
        }

        return *this;
    }
    catch (const std::logic_error &err)
    {
        std::cerr << err.what() << std::endl;
        return *this;
    }
    return *this;
}

//оператор вывода
std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial)
{
    for(auto i : polynomial.polynom)
    {
        if(i.second == 0) {continue;}
        os << "power: " << i.first << "  Coefficient: " << i.second << std::endl;
    }

    return os;
}

//оператор ввода
std::istream& operator>>(std::istream& is, Polynomial& polynomial)
{
    int termAmount;
    std::cin >> termAmount;
    while(termAmount < 1)
    {
        std::cout << "Input correct term's amount" << std::endl;
        std::cin >> termAmount;
    }
    int power;
    double coefficient;
    while (termAmount--)
    {
        is >> power >> coefficient;
        if(polynomial.polynom.find(power) != polynomial.polynom.end())
        {
            polynomial.polynom[power] += coefficient;
        } else {
            polynomial.polynom[power] = coefficient;
        }
    }

    return is;
}

//оператор взятия коеффициеента X в стпени power
double Polynomial::operator[](int power)
{
    return this->polynom[power];
}

Polynomial:: ~Polynomial()=default;
