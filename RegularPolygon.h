//
// Created by user on 18.03.2022.
//

#pragma once
#include "Polygon.h"


class RegularPolygon : public Polygon
{
private:

    double findAngle(const double &x1, const double &y1, const double &x2, const double &y2);

    double findLength(const double &x1, const double &y1, const double &x2, const double &y2);

    bool checkInputData();


public:
    // конструктор
    RegularPolygon(int pointsAmountInit = 3);

    // конструктор копирования
    RegularPolygon(const RegularPolygon &regularPolygon);

    // оператор присваивания
    RegularPolygon &operator=(const RegularPolygon &regularPolygon);

    virtual ~RegularPolygon();

    virtual double getSquare();

    virtual double getPerimetr();

    virtual void printCoords();
};

