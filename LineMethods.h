//
// Created by user on 18.03.2022.
//

#pragma once
#include <vector>
#include <cmath>
#include "Point.h"

class LineMethods {
public:
    double findLineLength(const std::vector<Point> &points);

    void printLineCoords(const std::vector<Point> &points);
};

