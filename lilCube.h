//
// Created by user on 12.05.2022.
//
#pragma once
#include <iostream>
#include "exception"
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <fstream>
#include "windows.h"



class LilCube {
public:
    const int N = 6;

    std::map<std::string, int> coloursToInt = {{"green", 0}, {"blue", 1}, {"yellow", 2},
                                               {"white", 3}, {"red", 4}, {"orange", 5}, {"none", -1}};
    std::map<int, std::string> coloursToStr = {{0, "green"}, {1, "blue"}, {2, "yellow"},
                                               {3, "white"}, {4, "red"}, {5, "orange"}, {-1, "none"}};
    enum {
        BLACK             = 0,
        DARKBLUE          = FOREGROUND_BLUE,
        DARKGREEN         = FOREGROUND_GREEN,
        DARKCYAN          = FOREGROUND_GREEN | FOREGROUND_BLUE,
        DARKRED           = FOREGROUND_RED,
        DARKMAGENTA       = FOREGROUND_RED | FOREGROUND_BLUE,
        DARKYELLOW        = FOREGROUND_RED | FOREGROUND_GREEN,
        DARKGRAY          = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
        GRAY              = FOREGROUND_INTENSITY,
        BLUE              = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
        GREEN             = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
        CYAN              = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
        RED               = FOREGROUND_INTENSITY | FOREGROUND_RED,
        MAGENTA           = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
        YELLOW            = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
        WHITE             = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    };

    std::map<std::string, int> edgesToInt = {{"front", 0}, {"back", 1}, {"top", 2},
                                             {"button", 3}, {"left", 4}, {"right", 5}};
    std::map<int, std::string> edgesToStr = {{0, "front"}, {1, "back"}, {2, "top"},
                                             {3, "button"}, {4, "left"}, {5, "right"}};

    int front = 0;
    int back = 1;
    int top = 2;
    int button = 3;
    int left = 4;
    int right = 5;

    std::vector<int> workEdge; // для каждого элемента свои

    //test.edges[i - 1].operator int &() = i; - вот так менять значения
    std::vector<std::reference_wrapper<int>> edges = { std::ref(front), std::ref(back), std::ref(top),
                                                       std::ref(button), std::ref(left), std::ref(right)};

    void initLilCubik(std::ifstream &input)
    {


        for(int i = 0;i < N; i++)
        {
            edges[i].operator int &() = -1;
        }

        int n;
        input >> n;

        for(int i = 0; i < n; i++)
        {
            std::string edge;
            std::string colour;

            input >> edge;
            input >> colour;

            workEdge.push_back(edgesToInt[edge]);
            edges[edgesToInt[edge]].operator int &() = coloursToInt[colour];
        }

    }

    void printSide(std::string side, int number, int &getColor)
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        getColor = edges[edgesToInt[side]];
        switch (edges[edgesToInt[side]]) {
            case 0:
                SetConsoleTextAttribute(handle, GREEN);
                break;

            case 1:
                SetConsoleTextAttribute(handle, BLUE);
                break;

            case 2:
                SetConsoleTextAttribute(handle, YELLOW);
                break;

            case 3:
                SetConsoleTextAttribute(handle, WHITE);
                break;

            case 4:
                SetConsoleTextAttribute(handle, RED);
                break;

            case 5:
                SetConsoleTextAttribute(handle,  DARKMAGENTA);
                break;

            case -1:
                SetConsoleTextAttribute(handle, BLACK);
                break;
        }
        std::cout << number;

    }

    void printLilCubik()
    {

        for(int i = 0; i < N; i++)
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            switch (edges[i].get()) {
                case 0:
                    SetConsoleTextAttribute(handle, GREEN);
                    break;

                case 1:
                    SetConsoleTextAttribute(handle, BLUE);
                    break;

                case 2:
                    SetConsoleTextAttribute(handle, YELLOW);
                    break;

                case 3:
                    SetConsoleTextAttribute(handle, WHITE);
                    break;

                case 4:
                    SetConsoleTextAttribute(handle, RED);
                    break;

                case 5:
                    SetConsoleTextAttribute(handle,  DARKMAGENTA);
                    break;

                case -1:
                    SetConsoleTextAttribute(handle, BLACK);
                    break;
            }
            std::cout << edgesToStr[i] << " = " << coloursToStr[edges[i].get()] << std::endl;
        }
        std::cout << std::endl;
    }

};

