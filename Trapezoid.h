//
// Created by user on 19.03.2022.
//

#pragma once
#include "Polygon.h"

class Trapezoid : public Polygon
{
private:

    double triangleSignedSquare(const int &ind1, const int &ind2, const int &ind3);//a - 1 b - 2 c - 3

    bool checkCorrectInputData();

public:
    // конструктор
    Trapezoid();

    // конструктор копирования
    Trapezoid(const Trapezoid &trapezoid);

    // оператор присваивания
    Trapezoid &operator=(const Trapezoid &trapezoid);

    virtual ~Trapezoid();

    virtual double getSquare();

    virtual double getPerimetr();

    virtual void printCoords();
};

