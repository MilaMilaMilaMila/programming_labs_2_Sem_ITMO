//
// Created by user on 18.03.2022.
//

#pragma once
#include "Point.h"
#include "ShapeMethods.h"
#include <set>


class Polygon {
protected:
    ShapeMethods methods;
    int pointsAmount;
    std::vector<Point> points;

    bool checkInputData(const std::set<std::pair<double, double>> &pointsSet);

public:
    // конструктор
    Polygon(int pointsAmountInit = 3);

    // конструктор копирования
    Polygon(const Polygon &polygon);

    // оператор присваивания
    Polygon &operator=(const Polygon &polygon);

    virtual ~Polygon();

    virtual double getSquare();

    virtual double getPerimetr();

    virtual void printCoords();

};

