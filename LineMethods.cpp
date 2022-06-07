//
// Created by user on 18.03.2022.
//

#include "LineMethods.h"

double LineMethods::findLineLength(const std::vector<Point> &points)
{
    double P = 0;
    int pointsAmount = points.size();
    for (int i = 0; i + 1 < pointsAmount; i++)
    {
        auto coords1 = points[i].getCoords();
        auto coords2 = points[i + 1].getCoords();

        P += sqrt(pow((coords1.first - coords2.first), 2) + pow((coords1.second - coords2.second), 2));
    }

    return P;
}

void LineMethods::printLineCoords(const std::vector<Point> &points)
{
    for (auto point : points)
    {
        point.printCoords();
    }
}