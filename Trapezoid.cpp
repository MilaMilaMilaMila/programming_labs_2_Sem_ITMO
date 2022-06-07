//
// Created by user on 19.03.2022.
//

#include "Trapezoid.h"


double Trapezoid::triangleSignedSquare(const int &ind1, const int &ind2, const int &ind3)//a - 1 b - 2 c - 3
{
    //(b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return (points[ind2].getX() - points[ind1].getX()) * (points[ind3].getY() - points[ind1].getY())
           - (points[ind2].getY() - points[ind1].getY()) * (points[ind3].getX() - points[ind1].getX());
}

bool Trapezoid::checkCorrectInputData()
{
    double x1 = points[0].getX() - points[1].getX();
    double x2 = points[2].getX() - points[3].getX();
    double y1 = points[0].getY() - points[1].getY();
    double y2 = points[2].getY() - points[3].getY();

    double x3 = points[1].getX() - points[2].getX();
    double x4 = points[0].getX() - points[3].getX();
    double y3 = points[1].getY() - points[2].getY();
    double y4 = points[0].getY() - points[3].getY();


    try
    {
        //проверка на параллельность
        if (!((x1 * y2 - x2 * y1 == 0 && x3 * y4 - x4 * y3 != 0) || (x1 * y2 - x2 * y1 != 0 && x3 * y4 - x4 * y3 == 0)))
        {
            throw std::logic_error("The shape is not a trapezoid.");
        }

        //проверка на самопересечения
        if(x1 * y2 - x2 * y1 == 0 && x3 * y4 - x4 * y3 != 0)
        {
            if(triangleSignedSquare(0, 3, 1) * triangleSignedSquare(0, 3, 2) < 0
               && triangleSignedSquare(2, 1, 0) * triangleSignedSquare(2, 1, 3) < 0)
            {
                throw std::logic_error("The shape is not a trapezoid.");
            }
        }

        if(x1 * y2 - x2 * y1 != 0 && x3 * y4 - x4 * y3 == 0)
        {
            if(triangleSignedSquare(1, 0, 3) * triangleSignedSquare(1, 0, 2) < 0
               && triangleSignedSquare(3, 2, 1) * triangleSignedSquare(3, 2, 0) < 0)
            {
                throw std::logic_error("The shape is not a trapezoid.");
            }
        }

        return true;
    }
    catch (const std::logic_error &err)
    {
        std::cerr << err.what() << std::endl;
        return false;
    }
}

// конструктор
Trapezoid::Trapezoid() : Polygon(4)
{
    while (!checkCorrectInputData())
    {
        std::cout << "input coords" << std::endl;
        for (int i = 0; i < pointsAmount; i++)
        {
            double x;
            double y;

            std::cin >> x >> y;
            Point point(x, y);

            points[i] = point;
        }
    }
}

// конструктор копирования
Trapezoid::Trapezoid(const Trapezoid &trapezoid) : Polygon(trapezoid)
{}

// оператор присваивания
Trapezoid& Trapezoid::operator=(const Trapezoid &trapezoid)
{
    if (this == &trapezoid)
        return *this;

    pointsAmount = trapezoid.pointsAmount;
    points = trapezoid.points;

    return *this;
}

Trapezoid:: ~Trapezoid()=default;

double Trapezoid::getSquare()
{
    return Polygon::getSquare();
}

double Trapezoid::getPerimetr()
{
    return Polygon::getPerimetr();
}

void Trapezoid::printCoords()
{
    std::cout << "Polygon is trapezoid" << std::endl;
    Polygon::printCoords();
}