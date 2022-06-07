//
// Created by user on 18.03.2022.
//

#include "Polygon.h"

bool Polygon::checkInputData(const std::set<std::pair<double, double>> &pointsSet)
{
    try
    {
        //проверка, что все точки разные
        if (pointsSet.size() != pointsAmount)
        {
            throw std::logic_error("The shape is not a polygon.\nSimilar points.");
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
Polygon::Polygon(int pointsAmountInit)
        : pointsAmount(pointsAmountInit)
{
    while(pointsAmount < 3)
    {
        std::cout << "input correct point's amount." << std::endl;
        std::cin >> pointsAmount;
    }

    points.resize(pointsAmount);
    std::set<std::pair<double, double>> pointsSet;

    do
    {
        std::cout << "input coords" << std::endl;
        pointsSet.clear();
        for (int i = 0; i < pointsAmount; i++)
        {
            double x;
            double y;

            std::cin >> x >> y;
            Point point(x, y);

            points[i] = point;
            pointsSet.insert({x, y});
        }
    } while (!checkInputData(pointsSet));
}

// конструктор копирования
Polygon::Polygon(const Polygon &polygon)=default;


// оператор присваивания
Polygon& Polygon::operator=(const Polygon &polygon)
{
    if (this == &polygon)
        return *this;

    pointsAmount = polygon.pointsAmount;
    points = polygon.points;
    methods = polygon.methods;

    return *this;
}

Polygon:: ~Polygon()=default;

double Polygon::getSquare()
{
    return methods.findShapeSquare(points);
}

double Polygon::getPerimetr()
{
    return methods.findShapePerimetr(points);
}

void Polygon::printCoords()
{
    std::cout << "Polygon's coords:" << std::endl;
    methods.printShapeCoords(points);
}
