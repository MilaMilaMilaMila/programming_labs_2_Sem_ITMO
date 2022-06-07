//
// Created by user on 18.03.2022.
//

#include "RegularPolygon.h"

double RegularPolygon::findAngle(const double &x1, const double &y1, const double &x2, const double &y2)
{
    double len1 = sqrt(x1 * x1 + y1 * y1);
    double len2 = sqrt(x2 * x2 + y2 * y2);
    double len12 = len1 * len2;
    return (x1 * x2 + y1 * y2) / len12;;
}

double RegularPolygon::findLength(const double &x1, const double &y1, const double &x2, const double &y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

bool RegularPolygon::checkInputData()
{
    try
    {
        double angle = findAngle(points[1].getX() - points[0].getX(), points[1].getY() - points[0].getY(), points[2].getX() - points[1].getX(), points[2].getY() - points[1].getY());
        double length = findLength(points[0].getX(), points[0].getY(), points[1].getX(), points[1].getY());

        // проверка  равенства длин
        for (int i = 0; i < pointsAmount; i++)
        {
            int first = i;
            int second = i + 1 == pointsAmount ? 0 : i + 1;
            double lengthCur = findLength(points[first].getX(), points[first].getY(), points[second].getX(), points[second].getY());
            if (length != lengthCur)
            {
                throw std::logic_error("The shape is not a regular polygon.\nDifferent lengths.");
            }
        }

        // проверка равенства углов
        for (int i = 0; i < pointsAmount; i++)
        {
            int first = i;
            int second = i + 1 >= pointsAmount ? (i + 1) % pointsAmount : i + 1;
            int third = i + 2 >= pointsAmount ? (i + 2) % pointsAmount : i + 2;
            double angleCur = findAngle(points[second].getX() - points[first].getX(), points[second].getY() - points[first].getY(), points[third].getX() - points[second].getX(), points[third].getY() - points[second].getY());
            if (angle != angleCur)
            {
                throw std::logic_error("The shape is not a regular polygon.\nDifferent angles.");
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
RegularPolygon::RegularPolygon(int pointsAmountInit)
        : Polygon(pointsAmountInit)
{

    while (!checkInputData())// отлов ошибок
    {
        std::cout << "input coords " << std::endl;
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
RegularPolygon::RegularPolygon(const RegularPolygon &regularPolygon) : Polygon(regularPolygon)
{
}

// оператор присваивания
RegularPolygon& RegularPolygon::operator=(const RegularPolygon &regularPolygon)
{
    if (this == &regularPolygon)
        return *this;

    pointsAmount = regularPolygon.pointsAmount;
    points = regularPolygon.points;

    return *this;
}

RegularPolygon:: ~RegularPolygon()=default;

double RegularPolygon::getSquare()
{
    return Polygon::getSquare();
}

double RegularPolygon::getPerimetr()
{
    return Polygon::getPerimetr();
}

void RegularPolygon::printCoords()
{
    std::cout << "Polygon is regular" << std::endl;
    Polygon::printCoords();
}