//
// Created by user on 15.05.2022.
//

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Cube.h"
#include <time.h>
#include <fstream>

class Interface {
public:

    void checkInvariant(Cube &cube)
    {

        std::map<std::string, int> check = {{"green", 0}, {"blue", 0}, {"yellow", 0},
                                            {"white", 0}, {"red", 0}, {"orange", 0}};

        std::string colour;
        for (int i = 0; i < 3; i++) {

            for (int j = 0; j < 3; j++) {
                colour = cube.cubik[0][i][j].coloursToStr[cube.cubik[0][i][j].top];
                check[colour]++;
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                colour = cube.cubik[i][k][0].coloursToStr[cube.cubik[i][k][0].left];
                check[colour]++;
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                colour = cube.cubik[i][2][k].coloursToStr[cube.cubik[i][2][k].front];
                check[colour]++;
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                colour = cube.cubik[i][k][2].coloursToStr[cube.cubik[i][k][2].right];
                check[colour]++;
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                colour = cube.cubik[i][0][k].coloursToStr[cube.cubik[i][0][k].back];
                check[colour]++;
            }
        }

        for(int i = 2; i >= 0; i--)
        {
            for(int j = 0; j < 3; j++)
            {
                colour = cube.cubik[2][i][j].coloursToStr[cube.cubik[2][i][j].button];
                check[colour]++;
            }
        }

        try {
            for (auto i : check) {
                if (i.second != 9)
                {
                    throw std::logic_error("Incorrect cubik's colours.");
                }
            }

            std::map<std::string, std::string> cross = {{"yellow", "white"}, {"white", "yellow"},
                                                        {"red", "orange"}, {"orange", "red"},
                                                        {"green", "blue"}, {"blue", "green"}};

            std::string colour1, colour2;
            colour1 = cube.cubik[0][1][1].coloursToStr[cube.cubik[0][1][1].top];
            colour2 = cube.cubik[2][1][1].coloursToStr[cube.cubik[2][1][1].button];

            if(colour1 != cross[colour2])
            {
                throw std::logic_error("Incorrect cubik's colours.");
            }

            colour1 = cube.cubik[1][0][1].coloursToStr[cube.cubik[1][0][1].back];
            colour2 = cube.cubik[1][0][1].coloursToStr[cube.cubik[1][2][1].front];

            if(colour1 != cross[colour2])
            {
                throw std::logic_error("Incorrect cubik's colours.");
            }

            colour1 = cube.cubik[1][1][0].coloursToStr[cube.cubik[1][1][0].left];
            colour2 = cube.cubik[1][1][2].coloursToStr[cube.cubik[1][1][2].right];

            if(colour1 != cross[colour2])
            {
                throw std::logic_error("Incorrect cubik's colours.");
            }

        }
        catch (const std::logic_error &err) {
            std::cerr << err.what() << std::endl;
            exit(0);
        }


    }

    Cube createCubik()
    {
        Cube cube;
        cube.initCubik();
        checkInvariant(cube);
        return cube;
    }

    void saveCubik(Cube &cube)
    {
        std::ofstream output("cubikSaved");
        output << 27 << '\n';
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                for(int k = 0; k < 3;  k++)
                {
                    output << i << " " << j << " " << k << '\n';
                    output << cube.cubik[i][j][k].workEdge.size() << '\n';
                    for(int cnt = 0; cnt < cube.cubik[i][j][k].workEdge.size(); cnt++)
                    {
                        output << cube.cubik[i][j][k].edgesToStr[cube.cubik[i][j][k].workEdge[cnt]] << " "
                               << cube.cubik[i][j][k].coloursToStr[cube.cubik[i][j][k].edges[cube.cubik[i][j][k].workEdge[cnt]].get()] << '\n';
                    }
                }
            }
        }
    }

    void showCubik(Cube &cube)
    {
        cube.printCubikColour();
        std::cout << std::endl;
    }

    void userManage(Cube &cube)
    {
        std::cout << "User manage switch on" << std::endl;
        std::string command = "";
        while(1)
        {
            std::cout << "Input command" << std::endl;
            std::cin >> command;
            if(command == "stop")
            {
                std::cout << "User manage switch off" << std::endl;
                return;
            }

            turnPlane(cube, command);

        }

    }

    void turnPlane(Cube &cube, std::string turnType)
    {
        std::ofstream output("L", std::ofstream::app);

        std::map<std::string, int> turnTypeToInt = {{"leftDown", 0}, {"leftUp", 1}, {"left180", 2},
                                                    {"rightDown", 3}, {"rightUp", 4}, {"right180", 5},
                                                    {"frontDown", 6}, {"frontUp", 7}, {"front180", 8},
                                                    {"backDown", 9}, {"backUp", 10}, {"back180", 11},
                                                    {"topLeft", 12}, {"topRight", 13}, {"top180", 14},
                                                    {"buttonLeft", 15}, {"buttonRight", 16}, {"button180", 17},
                                                    {"pifPaf", 18}, {"leftPifPaf", 19},
                                                    {"perehvatLeft", 20}, {"perehvatRight", 21},
                                                    {"putOnTheLeftSide", 22}, {"putOnRightSide", 23}};


        switch (turnTypeToInt[turnType]) {
            case 0:
                cube.L();
                break;
            case 1:
                cube.L_();
                break;
            case 2:
                cube.L2();
                break;
            case 3:
                cube.R_();
                break;
            case 4:
                cube.R();
                break;
            case 5:
                cube.R2();
                break;
            case 6:
                cube.F();
                break;
            case 7:
                cube.F_();
                break;
            case 8:
                cube.F2();
                break;
            case 9:
                cube.B_();
                break;
            case 10:
                cube.B();
                break;
            case 11:
                cube.B2();
                break;
            case 12:
                cube.U();
                break;
            case 13:
                cube.U_();
                break;
            case 14:
                cube.U2();
                break;
            case 15:
                cube.D_();
                break;
            case 16:
                cube.D();
                break;
            case 17:
                cube.D2();
                break;
            case 18:
                cube.R();
                cube.U();
                cube.R_();
                cube.U_();
                break;
            case 19:
                cube.L_();
                cube.U_();
                cube.L();
                cube.U();
                break;
            case 20:
                cube.middleU();
                cube.U();
                cube.D_();
                break;
            case 21:
                cube.middleU_();
                cube.U_();
                cube.D();
                break;
            case 22:
                cube.middleF_();
                cube.F_();
                cube.B();
                break;
            case 23:
                cube.middleF();
                cube.F();
                cube.B_();
                break;
        }
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
        std::cout << "MOVE: " << turnType << std::endl;
        showCubik(cube);

        std::vector<int> colorSide(54);
        int ind = 0;
        int cnt = 1;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                colorSide[ind++] = cube.cubik[0][i][j].top;
            }
        }

        for(int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                colorSide[ind++] = cube.cubik[i][k][0].left;
            }
        }
        for(int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                colorSide[ind++] = cube.cubik[i][2][k].front;
            }
        }
        for(int i = 0; i < 3; i++) {
            for (int k = 2; k >= 0; k--) {
                colorSide[ind++] = cube.cubik[i][k][2].right;
            }
        }

        for(int i = 0; i < 3; i++) {
            for(int k = 2; k >= 0; k--)
            {
                colorSide[ind++] = cube.cubik[i][0][k].back;
            }
        }

        for(int i = 2; i >= 0; i--)
        {
            for(int j = 0; j < 3; j++)
            {
                colorSide[ind++] = cube.cubik[2][i][j].button;
            }
        }

        for(auto i : colorSide)
        {
            output << i << ' ';
        }
        output << std::endl;

        output.close();


    }

    void shaffleCube(Cube &cube)
    {
        srand(time(NULL));
        std::vector<std::string> command = {"leftDown", "leftUp", "left180",
                                            "rightDown", "rightUp", "right180",
                                            "frontDown", "frontUp", "front180",
                                            "backDown", "backUp", "back180",
                                            "topLeft","topRight", "top180",
                                            "buttonLeft", "buttonRight","button180",
                                            "pifPaf", "leftPifPaf",
                                            "perehvatLeft", "perehvatRight",
                                            "putOnTheLeftSide", "putOnRightSide"};

        for(int i = 0; i < 20; i++)
        {
            turnPlane(cube, command[rand() % 23]);
        }

    }

    void inputCubikInConsole(Cube &cube) {
        std::string colour;
        std::cout << "input squares from left to right from first str  to last str.\n";

        std::cout << "TOP\n";
        for (int i = 0; i < 3; i++) {

            for (int j = 0; j < 3; j++) {
                std::cin >> colour;
                cube.cubik[0][i][j].top = cube.cubik[0][i][j].coloursToInt[colour];

            }
        }

        std::cout << "LEFT\n";
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                std::cin >> colour;
                cube.cubik[i][k][0].left = cube.cubik[i][k][0].coloursToInt[colour];
            }
        }

        std::cout << "FRONT\n";
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                std::cin >> colour;
                cube.cubik[i][2][k].front = cube.cubik[i][2][k].coloursToInt[colour];
            }
        }

        std::cout << "RIGHT\n";
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                std::cin >> colour;
                cube.cubik[i][k][2].right = cube.cubik[i][k][2].coloursToInt[colour];
            }
        }

        std::cout << "BACK\n";
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                std::cin >> colour;
                cube.cubik[i][0][k].back = cube.cubik[i][0][k].coloursToInt[colour];
            }
        }

        std::cout << "BOTTON\n";
        for(int i = 2; i >= 0; i--)
        {
            for(int j = 0; j < 3; j++)
            {
                std::cin >> colour;
                cube.cubik[2][i][j].button = cube.cubik[2][i][j].coloursToInt[colour];
            }
        }

        checkInvariant(cube);

    }


};


