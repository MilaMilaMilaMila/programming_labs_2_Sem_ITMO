//
// Created by user on 18.03.2022.
//

#include "ClosedPolyLine.h"


// конструктор
ClosedPolyLine::ClosedPolyLine(const std::vector<Point> &pointsInit)
: PolyLine(pointsInit)
{}

// конструктор копирования
ClosedPolyLine::ClosedPolyLine(const ClosedPolyLine &closedPolyline) : PolyLine(closedPolyline)
{}

// переопределене оператора присваивания
ClosedPolyLine& ClosedPolyLine::operator=(const ClosedPolyLine &closedPolyline)
{
    if (this == &closedPolyline)
        return *this;

    pointsAmount = closedPolyline.pointsAmount;
    points = closedPolyline.points;
    methods = closedPolyline.methods;

    return *this;
}

double ClosedPolyLine::getLength()
{
    return PolyLine::getLength() + sqrt(pow((points[pointsAmount - 1].getX() - points[0].getX()), 2)
                                        + pow((points[pointsAmount - 1].getY() - points[0].getY()), 2));;
}

void ClosedPolyLine::printCoords()
{
    std::cout << "PolyLine is closed" << std::endl;
    PolyLine::printCoords();
}