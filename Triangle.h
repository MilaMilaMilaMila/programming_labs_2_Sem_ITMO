//
// Created by user on 18.03.2022.
//

#pragma once
#include "Polygon.h"

class Triangle : public Polygon
{
private:

    bool checkCorrectInputData();

public:
    // конструктор
    Triangle();

    // конструктор копирования
    Triangle(const Triangle &triangle);

    // оператор присваивания
    Triangle &operator=(const Triangle &triangle);

    virtual ~Triangle();

    virtual double getSquare();

    virtual double getPerimetr();

    virtual void printCoords();
};
