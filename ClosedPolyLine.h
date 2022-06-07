//
// Created by user on 18.03.2022.
//

#pragma once
#include "PolyLine.h"

class ClosedPolyLine: public PolyLine
{
public:
    // конструктор
    explicit ClosedPolyLine(const std::vector<Point> &pointsInit);

    // конструктор копирования
    ClosedPolyLine(const ClosedPolyLine &closedPolyline);

    // переопределене оператора присваивания
    ClosedPolyLine &operator=(const ClosedPolyLine &closedPolyline);

    virtual double getLength();

    virtual void printCoords();
};
