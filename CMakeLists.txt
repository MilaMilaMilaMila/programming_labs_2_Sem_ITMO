cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(untitled1)
add_executable(untitled1 main.cpp)

project(lab10)
add_executable(lab10 filename.cpp Point.cpp Point.h LineMethods.cpp LineMethods.h PolyLine.cpp PolyLine.h
        ClosedPolyLine.cpp ClosedPolyLine.h ShapeMethods.cpp ShapeMethods.h Polygon.cpp Polygon.h RegularPolygon.cpp
        RegularPolygon.h Triangle.cpp Triangle.h Trapezoid.cpp Trapezoid.h)

project(lab10Polynomial)
add_executable(lab10Polynomial mainPolynom.cpp Polynomial/Polynomial.cpp Polynomial/Polynomial.h)