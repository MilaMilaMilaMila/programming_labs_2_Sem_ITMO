//
// Created by user on 18.03.2022.
//

#pragma once
#include "LineMethods.h"

class PolyLine {
protected:
    LineMethods methods;
    int pointsAmount;
    std::vector<Point> points;

public:
    // конструктор
    explicit PolyLine(const std::vector<Point> &pointsInit);

    // конструктор копирования
    PolyLine(const PolyLine &polyline);

    // переопределение оператора присваивания
    PolyLine &operator=(const PolyLine &polyLine);

    virtual double getLength();

    virtual void printCoords();

    virtual ~PolyLine();
};

