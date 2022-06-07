//
// Created by user on 18.05.2022.
//

#pragma once
#define GLAD_GL_IMPLEMENTATION
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "Friedrich.h"
#include "interface.h"
#include "Cube.h"


class programInterface {
public:
    void buildCubik(Cube &cube, Interface &user, Friedrich algo)
    {
        algo.makeWhiteCross(cube, user);
        user.showCubik(cube);
        algo.putCrossRight(cube, user);
        std::cout << "____CORRECT__CROSS__IS__READY____" << std::endl;
        user.showCubik(cube);
        algo.putWhiteCornersCorrect(cube, user);
        std::cout << "____FIRST__LAYER__IS__READY____" << std::endl;
        user.showCubik(cube);
        algo.putCoourfulEdgeCorrect(cube, user);
        std::cout << "____SECOND__LAYER__IS__READY____" << std::endl;
        user.showCubik(cube);
        algo.makeYellowCross(cube, user);
        std::cout << "____YELLOW__CROSS__READY____" << std::endl;
        user.showCubik(cube);
        algo.putYellowCornersCorrect(cube, user);
        std::cout << "____YELLOW__CORNERS__READY____" << std::endl;
        user.showCubik(cube);
        algo.putLastEdgesCorrect(cube, user);
        std::cout << "____LAST__EDGES__CORRECT____" << std::endl;
        user.showCubik(cube);
        algo.putLastCornersCorrect(cube, user);
        std::cout << "______CORRECT____" << std::endl;
        user.showCubik(cube);

        std::cout << "If cubik is incorrect - start cubik condition was incorrect\n";
    }


    void startWork(Cube &cube, Interface &user, Friedrich &algo)
    {
        std::string command = "";

        std::map<std::string, int> commandToInt = {{"stop", 0}, {"userManage", 1}, {"assembly", 2},
                                                   {"save", 3}, {"input", 4}, {"shaffle", 5},
                                                   {"show", 6}};

        while(1)
        {
            std::cout << "Input command\n";
            std::cout << "command stop - switch off game\n";
            std::cout << "command userManage - manual control\n";
            std::cout << "command assembly - assembly cubik by program\n";
            std::cout << "command shaffle - generate random condition\n";
            std::cout << "command show - show cubik\n";
            std::cout << "command save - save current condition\n";
            std::cout << "command input - input cibik condition\n";

            std::cin >> command;

            switch (commandToInt[command]) {
                case 0:
                    exit(0);
                    break;
                case 1:
                    user.userManage(cube);
                    break;
                case 2:
                    buildCubik(cube, user, algo);
                    break;
                case 3:
                    user.saveCubik(cube);
                    break;
                case 4:
                    user.inputCubikInConsole(cube);
                    break;
                case 5:
                    user.shaffleCube(cube);
                    break;
                case 6:
                    user.showCubik(cube);
                    break;
                default:
                    std::cout << "incorrect command.\n";
                    break;
            }
        }
    }
};


