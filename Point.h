//
// Created by user on 18.03.2022.
//
#pragma once
#include <iostream>

class Point {
private:
    double x;
    double y;

public:
    // конструктор
    explicit Point(double X = 0, double Y = 0);

    // конструктор копирования
    Point(const Point &point);

    // оператор присвваивания
    Point &operator=(const Point &point);

    std::pair<double, double> getCoords() const;

    double getX() const;

    double getY() const;

    void printCoords();
};
