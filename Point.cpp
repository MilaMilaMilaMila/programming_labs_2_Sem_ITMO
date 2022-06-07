//
// Created by user on 18.03.2022.
//

#include "Point.h"
// конструктор
Point::Point(double X, double Y)
        : x(X), y(Y)
{}

// конструктор копирования
Point::Point(const Point &point)=default;


// оператор присвваивания
Point& Point::operator=(const Point &point)
{
    if (this == &point)
        return *this;

    x = point.x;
    y = point.y;

    return *this;
}

void Point::printCoords()
{
    std::cout << "( " << x << " ; " << y << " )" << std::endl;
}

std::pair<double, double> Point::getCoords() const
{
    return {x, y};
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}
