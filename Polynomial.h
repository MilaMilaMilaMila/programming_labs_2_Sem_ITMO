//
// Created by user on 19.03.2022.
//

#pragma once
#include <iostream>
#include <map>
#include <cmath>
#include <ostream>
#include <istream>

class Polynomial {
private:
    std::map<int, double> polynom;

public:
    //конструктор
    explicit Polynomial (int termAmount = 1);

    //конструктор
    explicit Polynomial(std::map<int, double> polynomInit);

    // конструктор копирования
    Polynomial(const Polynomial &polynomial);

    //оператор присваивания
    Polynomial &operator=(const Polynomial &polynomial);

    //оператор равенства ==
    bool operator==(const Polynomial &polynomOther);

    //оператор не равенства !=
    bool operator!=(const Polynomial &polynomOther);

    //оператор сложения +
    Polynomial operator+(const Polynomial &polynomOther);

    //оператор вычитания -
    Polynomial operator-(const Polynomial &polynomOther);

    //оператор унарный -
    Polynomial operator-();

    //оператор сложение с присваивание +=
    Polynomial &operator+=(const Polynomial &polynomial);

    //оператор вычитание с присваиванием -=
    Polynomial &operator-=(const Polynomial &polynomial);

    //оператор умножение на многочлен *
    Polynomial operator*(const Polynomial &polynomOther);

    //оператор деление на число /
    Polynomial operator/(double numb);

    //оператор умножение c присваиванием *=
    Polynomial &operator*=(const Polynomial &polynomial);

    //оператор деление c присваиванием /=
    Polynomial &operator/=(double numb);

    //оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial);

    //оператор ввода
    friend std::istream& operator>>(std::istream& os, Polynomial& polynomial);

    //оператор взятия коеффициеента X в стпени power
    double operator[](int power);

    ~Polynomial();

};

std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial);

std::istream& operator>>(std::istream& is, Polynomial& polynomial);