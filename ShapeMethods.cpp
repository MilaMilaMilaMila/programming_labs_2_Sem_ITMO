//
// Created by user on 18.03.2022.
//

#include "ShapeMethods.h"

double ShapeMethods::findParallelogramSquare(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3)
{
    double Ax = x2 - x1;
    double Ay = y2 - y1;
    double Bx = x3 - x1;
    double By = y3 - y1;
    return Ax * By - Ay * Bx;
}

double ShapeMethods::findShapeSquare(const std::vector<Point> &points)
{
    int pointsAmount = points.size();
    double S = 0;
    for (int i = 1; i + 1 < pointsAmount; i++)
    {
        auto P1 = points[0].getCoords();
        auto P2 = points[i].getCoords();
        auto P3 = points[i + 1].getCoords();

        S += findParallelogramSquare(P1.first, P1.second, P2.first, P2.second, P3.first, P3.second);
    }

    if(S < 0)
    {
        S *= -1.0;
    }

    return S / 2.0;
}

double ShapeMethods::findShapePerimetr(const std::vector<Point> &points)
{
    double P = 0;
    int pointsAmount = points.size();
    for (int i = 0; i + 1 < pointsAmount; i++)
    {
        auto coords1 = points[i].getCoords();
        auto coords2 = points[i + 1].getCoords();

        P += sqrt(pow((coords1.first - coords2.first), 2) + pow((coords1.second - coords2.second), 2));
    }

    auto coords1 = points[0].getCoords();
    auto coords2 = points[pointsAmount - 1].getCoords();

    P += sqrt(pow((coords1.first - coords2.first), 2) + pow((coords1.second - coords2.second), 2));

    return P;
}

void ShapeMethods::printShapeCoords(const std::vector<Point> &points)
{
    for (auto point : points)
    {
        point.printCoords();
    }
}
