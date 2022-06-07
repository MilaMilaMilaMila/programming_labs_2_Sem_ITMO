//
// Created by user on 18.03.2022.
//

#include "Triangle.h"

bool Triangle::checkCorrectInputData()
{
    double length1 = sqrt(pow(points[0].getX() - points[1].getX(), 2) + pow((points[0].getY() - points[1].getY()), 2));
    double length2 = sqrt(pow(points[1].getX() - points[2].getX(), 2) + pow((points[1].getY() - points[2].getY()), 2));
    double length3 = sqrt(pow(points[2].getX() - points[0].getX(), 2) + pow((points[2].getY() - points[0].getY()), 2));

    try
    {
        if (!(length1 + length2 > length3 && length2 + length3 > length1 && length3 + length1 > length2))
        {
            throw std::logic_error("The shape is not a triangle.");
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
Triangle::Triangle() : Polygon(3)
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
    } // проверка, что это треугольник
}

// конструктор копирования
Triangle::Triangle(const Triangle &triangle) : Polygon(triangle)
{
}

// оператор присваивания
Triangle& Triangle::operator=(const Triangle &triangle)
{
    if (this == &triangle)
        return *this;

    pointsAmount = triangle.pointsAmount;
    points = triangle.points;

    return *this;
}

Triangle:: ~Triangle()=default;

double Triangle::getSquare()
{
    return Polygon::getSquare();
}

double Triangle::getPerimetr()
{
    return Polygon::getPerimetr();
}

void Triangle::printCoords()
{
    std::cout << "Polygon is triangle" << std::endl;
    Polygon::printCoords();
}