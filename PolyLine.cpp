//
// Created by user on 18.03.2022.
//

#include "PolyLine.h"

// конструктор
PolyLine::PolyLine(const std::vector<Point> &pointsInit)
: pointsAmount(pointsInit.size()), points(pointsInit)
{}

// конструктор копирования
PolyLine::PolyLine(const PolyLine &polyline)=default;

// переопределение оператора присваивания
PolyLine& PolyLine::operator=(const PolyLine &polyLine)
{
    if (this == &polyLine)
        return *this;

    pointsAmount = polyLine.pointsAmount;
    points = polyLine.points;
    methods = polyLine.methods;

    return *this;
}

double PolyLine::getLength()
{
    return methods.findLineLength(points);
}

void PolyLine:: printCoords()
{
    std::cout << "PolyLine's coords:" << std::endl;
    methods.printLineCoords(points);
}

PolyLine:: ~PolyLine()=default;