#include "PolyLine.h"
#include "ClosedPolyLine.h"
#include "Polygon.h"
#include "RegularPolygon.h"
#include "Triangle.h"
#include "Trapezoid.h"

std::vector<Point> makePolyLine()
{
    int pointsAmount;
    std::cout << "input point's amount." << std::endl;
    std::cin >> pointsAmount;
    while(pointsAmount < 2)
    {
        std::cout << "input correct point's amount." << std::endl;
        std::cin >> pointsAmount;
    }

    std::vector<Point> points;
    points.resize(pointsAmount);

    std::cout << "input coords" << std::endl;
    for (int i = 0; i < pointsAmount; i++)
    {
        double x;
        double y;

        std::cin >> x >> y;
        Point point(x, y);

        points[i] = point;
    }

    return points;
}

int main() {
//    тест точки
//    Point point(3, 7.89);
//    point.printCoords();
//    std::cout << "point X = " << point.getX() << " point Y = " << point.getY() << std::endl;

//    тест ломаная
//    //3 0 0 3.3 -4 5 78.89
//    PolyLine polyLine1(makePolyLine());
//    std::cout << "Polyline1 coords: " << std::endl;
//    polyLine1.printCoords();
//    std::cout << "Polyline length = " << polyLine1.getLength() << std::endl;
//
//    PolyLine polyLineCopy = polyLine1;
//    std::cout << "Polyline copy coords: " << std::endl;
//    polyLineCopy.printCoords();
//
//    //4 5 6 7 8 -9 67 7.55 -0.89 0 0
//    PolyLine polyLine2(makePolyLine());
//    std::cout << "Polyline2 coords: " << std::endl;
//    polyLine2.printCoords();
//
//    polyLineCopy = polyLine2;
//    std::cout << "Polyline copy coords: " << std::endl;
//    polyLineCopy.printCoords();

//    тест замкнутая ломаная
//    //4 5 6 7 8 -9 67 7.55 -0.89 0 0
//    ClosedPolyLine closedPolyLine(makePolyLine());
//    closedPolyLine.printCoords();
//    std::cout << "closedPolyline length = " << closedPolyLine.getLength() << std::endl;

//   тест многоугольник
//    // 3 0 0 1 1 0 3
//    Polygon polygon1(0);
//    std::cout << "Polygon1 coords:" << std::endl;
//    polygon1.printCoords();
//    std::cout << "polygon1's Perimetr = " << polygon1.getPerimetr() << " polygon1's Square = " << polygon1.getSquare();

//    тест правильный многоугольник
//    //0 0 3 4 5 6 1 2 different lengths
//    //0 2 1 0 0 -2 -1 0 different angels (ромб)
//    //0 0 1 0 1 1 0 1
//    RegularPolygon regularPolygon1(4);
//    std::cout << "RegularPolygon1 coords:" << std::endl;
//    regularPolygon1.printCoords();
//    std::cout << "Regularpolygon1's Perimetr = " << regularPolygon1.getPerimetr()
//    << " polygon1's Square = " << regularPolygon1.getSquare();

//    тест треугольник
//    //0 0 0 2 2 0
//    Triangle triangle1;
//    std::cout << "Triangles1 coords:" << std::endl;
//    triangle1.printCoords();
//    std::cout << "Triangle1 Perimetr = " << triangle1.getPerimetr()
//    << " Triangle1 Square = " << triangle1.getSquare() << std::endl;

//    тест трапеция
//    //0 0 1 0 1 1 0 1 квадрат
//    //0 0 2.13 2 5 2 4.67 0 норм
//    //0 0 5 6 7 8 -10 0 точно не трапеция
//    Trapezoid trapezoid1;
//    std::cout << "Trapezoid1 coords:" << std::endl;
//    trapezoid1.printCoords();
//    std::cout << "Trapezoid1 Perimetr = " << trapezoid1.getPerimetr()
//    << " Trapezoid1 Square = " << trapezoid1.getSquare() << std::endl;

    return 0;
}