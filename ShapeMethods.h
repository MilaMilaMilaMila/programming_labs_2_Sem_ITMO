//
// Created by user on 18.03.2022.
//

#pragma once
#include "Point.h"
#include <vector>
#include <cmath>

class ShapeMethods {
public:
    double findParallelogramSquare(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3);

    double findShapeSquare(const std::vector<Point> &points);

    double findShapePerimetr(const std::vector<Point> &points);

    void printShapeCoords(const std::vector<Point> &points);

};

