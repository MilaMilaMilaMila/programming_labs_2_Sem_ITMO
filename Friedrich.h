//
// Created by user on 15.05.2022.
//

#pragma once
#include "interface.h"

class Friedrich {
public:

    void putWhiteEdgeCorrect(Cube &cube, Interface &user)
    {
        for(int k = 0; k < 4; k++) {
            for (int i = 0; i < 3; i++) {

                for (int j = 0; j < 3; j++) {

                    if (cube.cubik[i][2][j].front == 3) {

                        if (i == 0 && j == 1) {

                            user.turnPlane(cube, "frontDown");

                            while (cube.cubik[0][1][2].top == 3) {

                                user.turnPlane(cube, "topLeft");

                            }

                            user.turnPlane(cube, "rightUp");
                        }

                        if (i == 1) {

                            if (j == 0) {

                                while (cube.cubik[0][1][0].top == 3) {

                                    user.turnPlane(cube, "topLeft");

                                }

                                user.turnPlane(cube, "leftUp");

                            }

                            if (j == 2) {

                                while (cube.cubik[0][1][2].top == 3) {

                                    user.turnPlane(cube, "topLeft");

                                }

                                user.turnPlane(cube, "rightUp");

                            }

                        }

                        if (i == 2 && j == 1) {

                            while (cube.cubik[0][2][1].top == 3) {

                                user.turnPlane(cube, "topLeft");

                            }

                            user.turnPlane(cube, "frontDown");

                            while (cube.cubik[0][1][0].top == 3) {

                                user.turnPlane(cube, "topLeft");

                            }

                            user.turnPlane(cube, "leftUp");

                        }

                    }

                    if (cube.cubik[i][2][j].button == 3 && j == 1) {

                        while (cube.cubik[0][2][1].top == 3) {

                            user.turnPlane(cube, "topLeft");

                        }

                        user.turnPlane(cube, "frontUp");
                    }
                }
            }

            user.turnPlane(cube, "perehvatLeft");
        }
    }

    bool checkCross(Cube &cube, Interface &user)
    {
        if (cube.cubik[0][1][1].top == cube.cubik[0][1][0].top &&
            cube.cubik[0][1][1].top == cube.cubik[0][1][2].top &&
            cube.cubik[0][1][1].top == cube.cubik[0][0][1].top &&
            cube.cubik[0][1][1].top == cube.cubik[0][2][1].top) {

            return true;

        }

        return false;
    }

    void makeWhiteCross(Cube &cube, Interface &user)
    {
        // find white side

        for (int i = 0; i < 4; i++) {

            if (cube.cubik[0][1][1].top != 3) {  //white == 3

                user.turnPlane(cube, "putOnTheLeftSide");

            } else {

                break;

            }

        }

        if (cube.cubik[0][1][1].top != 3) {  //white == 3

            user.turnPlane(cube, "perehvatLeft");

        }

        for (int i = 0; i < 4; i++) {

            if (cube.cubik[0][1][1].top != 3) {  //white == 3

                user.turnPlane(cube, "putOnTheLeftSide");

            } else {

                break;

            }

        }

        //обрабатываем каждое ребро сразу, как нашли

        for (int i = 0; i < 4; i++) {

            if (checkCross(cube, user)) {
                break;
            }

            putWhiteEdgeCorrect(cube, user);
            user.turnPlane(cube, "perehvatLeft");

        }
    }

    void putCrossRight(Cube &cube, Interface &user)
    {
        int cnt = 0;

        while (cnt < 2) {

            cnt = 0;

            if (cube.cubik[0][0][1].back == cube.cubik[1][0][1].back) {

                cnt++;
            }

            if (cube.cubik[0][1][0].left == cube.cubik[1][1][0].left) {

                cnt++;

            }

            if (cube.cubik[0][2][1].front == cube.cubik[1][2][1].front) {

                cnt++;

            }

            if (cube.cubik[0][1][2].right == cube.cubik[1][1][2].right) {

                cnt++;

            }

            if (cnt == 2) {

                break;

            }

            user.turnPlane(cube, "topLeft");

        }

        while(!((cube.cubik[0][0][1].back == cube.cubik[1][0][1].back && cube.cubik[0][2][1].front == cube.cubik[1][2][1].front) ||
                (cube.cubik[0][1][0].left == cube.cubik[1][1][0].left && cube.cubik[0][1][2].right == cube.cubik[1][1][2].right) ||
                (cube.cubik[0][1][0].left == cube.cubik[1][1][0].left && cube.cubik[0][0][1].back == cube.cubik[1][0][1].back)   ||
                (cube.cubik[0][0][1].back == cube.cubik[1][0][1].back && cube.cubik[0][1][2].right == cube.cubik[1][1][2].right) ||
                (cube.cubik[0][1][2].right == cube.cubik[1][1][2].right && cube.cubik[0][2][1].front == cube.cubik[1][2][1].front)||
                (cube.cubik[0][2][1].front == cube.cubik[1][2][1].front && cube.cubik[0][1][0].left == cube.cubik[1][1][0].left)))
        {
            user.turnPlane(cube, "topLeft");
        }

        if ((cube.cubik[0][0][1].back == cube.cubik[1][0][1].back && cube.cubik[0][2][1].front == cube.cubik[1][2][1].front)||
            (cube.cubik[0][1][0].left == cube.cubik[1][1][0].left && cube.cubik[0][1][2].right == cube.cubik[1][1][2].right)) {

            if (cube.cubik[0][1][0].left == cube.cubik[1][1][0].left && cube.cubik[0][1][2].right == cube.cubik[1][1][2].right) {

                user.turnPlane(cube, "perehvatLeft");

            }

            user.turnPlane(cube, "pifPaf");
            user.turnPlane(cube, "rightUp");

        }

        while(!((cube.cubik[0][0][1].back == cube.cubik[1][0][1].back && cube.cubik[0][2][1].front == cube.cubik[1][2][1].front) ||
                (cube.cubik[0][1][0].left == cube.cubik[1][1][0].left && cube.cubik[0][1][2].right == cube.cubik[1][1][2].right) ||
                (cube.cubik[0][1][0].left == cube.cubik[1][1][0].left && cube.cubik[0][0][1].back == cube.cubik[1][0][1].back)   ||
                (cube.cubik[0][0][1].back == cube.cubik[1][0][1].back && cube.cubik[0][1][2].right == cube.cubik[1][1][2].right) ||
                (cube.cubik[0][1][2].right == cube.cubik[1][1][2].right && cube.cubik[0][2][1].front == cube.cubik[1][2][1].front)||
                (cube.cubik[0][2][1].front == cube.cubik[1][2][1].front && cube.cubik[0][1][0].left == cube.cubik[1][1][0].left)))
        {
            user.turnPlane(cube, "topLeft");
        }

        while (!(cube.cubik[0][2][1].front == cube.cubik[1][2][1].front && cube.cubik[0][1][0].left == cube.cubik[1][1][0].left)) {

            user.turnPlane(cube, "perehvatLeft");
        }

        user.turnPlane(cube, "pifPaf");
        user.turnPlane(cube, "rightUp");

    }

    bool checkWhiteCorners(Cube &cube, Interface &user)
    {
        if (cube.cubik[2][1][1].button == cube.cubik[2][0][0].button &&
           cube.cubik[2][1][1].button == cube.cubik[2][0][2].button &&
           cube.cubik[2][1][1].button == cube.cubik[2][2][0].button &&
           cube.cubik[2][1][1].button == cube.cubik[2][2][2].button) {

            return true;

        }

        return false;
    }

    int findWhiteOnCorner(Cube &cube, int z, int y, int x)
    {
        if (cube.cubik[z][y][x].front == 3) {

            return 1;

        }

        if (cube.cubik[z][y][x].top == 3) {

            return 2;

        }

        if (cube.cubik[z][y][x].button == 3) {

            return 3;

        }

        if (cube.cubik[z][y][x].right == 3) {

            return 4;

        }

        return 0;
    }

    bool isNeedTop(Cube &cube, int colour1, int colour2)
    {
        if ((cube.cubik[0][2][2].top == colour1 || cube.cubik[0][2][2].top == colour2) &&
            (cube.cubik[0][2][2].front == colour1 || cube.cubik[0][2][2].front == colour2)) {

            return true;

        }

        if ((cube.cubik[0][2][2].top == colour1 || cube.cubik[0][2][2].top == colour2) &&
           (cube.cubik[0][2][2].right == colour1 || cube.cubik[0][2][2].right == colour2)) {

            return true;

        }

        if ((cube.cubik[0][2][2].right == colour1 || cube.cubik[0][2][2].right == colour2) &&
           (cube.cubik[0][2][2].front == colour1 || cube.cubik[0][2][2].front == colour2)) {

            return true;

        }

        return false;

    }

    bool isNeedButton(Cube &cube, int colour1, int colour2)
    {
        if ((cube.cubik[2][2][2].button == colour1 || cube.cubik[2][2][2].button == colour2) &&
            (cube.cubik[2][2][2].front == colour1 || cube.cubik[2][2][2].front == colour2)) {

            return true;

        }

        if ((cube.cubik[2][2][2].button == colour1 || cube.cubik[2][2][2].button == colour2) &&
           (cube.cubik[2][2][2].right == colour1 || cube.cubik[2][2][2].right == colour2)) {

            return true;

        }

        if ((cube.cubik[2][2][2].right == colour1 || cube.cubik[2][2][2].right == colour2) &&
            (cube.cubik[2][2][2].front == colour1 || cube.cubik[2][2][2].front == colour2)) {

            return true;

        }

        return false;

    }

    void putWhiteCornersCorrect(Cube &cube, Interface &user) {

        user.turnPlane(cube, "putOnTheLeftSide");
        user.turnPlane(cube, "putOnTheLeftSide");

        for (int i = 0; i < 4; i++) {

            int colour1 = cube.cubik[1][2][1].front;
            int colour2 = cube.cubik[1][1][2].right;

            for (int j = 0; j < 4; j++) {

                if (findWhiteOnCorner(cube, 2, 2, 2) != 0 && isNeedButton(cube, colour1, colour2)) {

                    user.turnPlane(cube, "pifPaf");
                    break;

                } else {

                    user.turnPlane(cube, "perehvatLeft");
                }
            }

            while (!(cube.cubik[1][2][1].front == colour1 && cube.cubik[1][1][2].right == colour2)) {

                user.turnPlane(cube, "perehvatLeft");

            }

            for (int j = 0; j < 4; j++) {

                if (findWhiteOnCorner(cube, 0, 2, 2) && isNeedTop(cube, colour1, colour2)) {

                    switch (findWhiteOnCorner(cube, 0, 2, 2)) {

                        case 1:

                            for (int k = 0; k < 5; k++) {

                                user.turnPlane(cube, "pifPaf");

                            }

                            break;

                        case 2:

                            for (int k = 0; k < 3; k++) {

                                user.turnPlane(cube, "pifPaf");
                            }

                            break;

                        case 4:

                            user.turnPlane(cube, "pifPaf");

                            break;
                    }

                } else {

                    user.turnPlane(cube, "topLeft");

                }
            }

            user.turnPlane(cube, "perehvatLeft");

        }

    }

    void putCoourfulEdgeCorrect(Cube &cube, Interface &user)
    {
        for (int i = 0; i < 8; i++) {

            int colour1 = cube.cubik[1][2][1].front;
            int colour2 = cube.cubik[1][1][2].right;

            if (!(cube.cubik[1][2][2].front == colour1 && cube.cubik[1][2][2].right == colour2)) {

                for (int j = 0; j < 4; j++) {

                    if ((cube.cubik[1][2][2].front == colour1 || cube.cubik[1][2][2].front == colour2) &&
                        (cube.cubik[1][2][2].right == colour1 || cube.cubik[1][2][2].right == colour2)) {

                        user.turnPlane(cube, "pifPaf");

                        user.turnPlane(cube, "perehvatLeft");

                        user.turnPlane(cube, "leftPifPaf");

                        break;

                    } else {

                        user.turnPlane(cube, "perehvatLeft");

                    }

                }

                while (!(cube.cubik[1][2][1].front == colour1 && cube.cubik[1][1][2].right == colour2)) {

                    user.turnPlane(cube, "perehvatLeft");

                }

                for (int j = 0; j < 4; j++) {

                    if (cube.cubik[0][2][1].front == cube.cubik[1][2][1].front &&
                       cube.cubik[0][2][1].top == cube.cubik[1][1][2].right) {

                        break;

                    } else if (cube.cubik[0][1][2].right == cube.cubik[1][1][2].right &&
                            cube.cubik[0][1][2].top == cube.cubik[1][2][1].front) {

                        user.turnPlane(cube, "perehvatLeft");
                        break;

                    } else {

                        user.turnPlane(cube, "topLeft");

                    }
                }

                if (cube.cubik[0][2][1].front == cube.cubik[1][2][1].front &&
                    cube.cubik[0][2][1].top == cube.cubik[1][1][2].right) {

                    user.turnPlane(cube, "topLeft");
                    user.turnPlane(cube, "pifPaf");
                    user.turnPlane(cube, "perehvatLeft");
                    user.turnPlane(cube, "leftPifPaf");

                } else if (cube.cubik[0][2][1].front == cube.cubik[1][2][1].front &&
                           cube.cubik[0][2][1].top == cube.cubik[1][1][0].left) {

                    user.turnPlane(cube, "topRight");
                    user.turnPlane(cube, "leftPifPaf");
                    user.turnPlane(cube, "perehvatRight");
                    user.turnPlane(cube, "pifPaf");

                }

            }

            user.turnPlane(cube, "perehvatLeft");

        }

    }

    void makeYellowCross(Cube &cube, Interface &user)
    {
        if (checkCross(cube, user)) {
            return;
        }

        for (int i = 0; i < 2; i++) {

            if (cube.cubik[0][1][0].top == 2 && cube.cubik[0][1][1].top == 2 && cube.cubik[0][1][2].top == 2) {

                user.turnPlane(cube, "frontDown");
                user.turnPlane(cube, "pifPaf");
                user.turnPlane(cube, "frontUp");

                return;

            } else {

                user.turnPlane(cube, "perehvatLeft");

            }

        }

        for (int i = 0; i < 4; i++) {

            if (cube.cubik[0][0][1].top == 2 && cube.cubik[0][1][1].top == 2 && cube.cubik[0][1][0].top == 2) {

                user.turnPlane(cube, "frontDown");
                user.turnPlane(cube, "pifPaf");
                user.turnPlane(cube, "pifPaf");
                user.turnPlane(cube, "frontUp");

                return;

            } else {

                user.turnPlane(cube, "perehvatLeft");

            }

        }

        user.turnPlane(cube, "frontDown");
        user.turnPlane(cube, "pifPaf");
        user.turnPlane(cube, "frontUp");

        user.turnPlane(cube, "topLeft");
        user.turnPlane(cube, "topLeft");

        user.turnPlane(cube, "frontDown");
        user.turnPlane(cube, "pifPaf");
        user.turnPlane(cube, "pifPaf");
        user.turnPlane(cube, "frontUp");

    }

    void putYellowCornersCorrect(Cube &cube, Interface &user)
    {
        user.turnPlane(cube, "putOnTheLeftSide");

        for (int i = 0; i < 4; i++) {

            if (cube.cubik[0][0][0].left != 2) {

                if (cube.cubik[0][0][0].top == 2) {

                    for(int k = 0; k < 4; k++) {

                        user.turnPlane(cube, "pifPaf");

                    }

                } else {

                    for (int k = 0; k < 2; k++) {

                        user.turnPlane(cube, "pifPaf");

                    }

                }

            }

            user.turnPlane(cube, "leftDown");

        }

        user.turnPlane(cube, "putOnRightSide");

    }

    void putLastEdgesCorrect(Cube &cube, Interface &user)
    {

        bool flag = 1;

        for (int i = 0; i < 4; i++) {

            if (cube.cubik[0][2][1].front != cube.cubik[1][2][1].front) {

                flag = 0;

                break;

            }

            user.turnPlane(cube, "perehvatLeft");

        }

        if (flag) {

            return;

        }

        int cnt = 0;

        while (cnt < 2) {

            cnt = 0;
            if (cube.cubik[0][0][1].back == cube.cubik[1][0][1].back) {

                cnt++;

            }

            if (cube.cubik[0][1][0].left == cube.cubik[1][1][0].left) {

                cnt++;

            }

            if (cube.cubik[0][2][1].front == cube.cubik[1][2][1].front) {

                cnt++;

            }

            if (cube.cubik[0][1][2].right == cube.cubik[1][1][2].right) {

                cnt++;

            }

            if (cnt == 2) {

                break;

            }

            user.turnPlane(cube, "topLeft");

        }

        int variant = 0;

        for (int i = 0; i < 4; i++) {

            if (cube.cubik[0][0][1].back == cube.cubik[1][0][1].back &&
                cube.cubik[0][1][0].left == cube.cubik[1][1][0].left) {

                variant = 1;

                break;

            }

            if (cube.cubik[0][0][1].back == cube.cubik[1][0][1].back &&
                cube.cubik[0][2][1].front == cube.cubik[1][2][1].front) {

                variant = 2;

                break;

            }

            user.turnPlane(cube, "perehvatLeft");

        }

        // R U R'   F'   R U R'   U' R' F   R2  U' R' U'
        if (variant == 1) {

            user.turnPlane(cube, "rightUp"); // R
            user.turnPlane(cube, "topLeft"); // U
            user.turnPlane(cube, "rightDown"); // R'

            user.turnPlane(cube, "frontUp");// F'

            user.turnPlane(cube, "rightUp"); //R
            user.turnPlane(cube, "topLeft"); // U
            user.turnPlane(cube, "rightDown"); // R'

            user.turnPlane(cube, "topRight"); // U'
            user.turnPlane(cube, "rightDown"); // R'
            user.turnPlane(cube, "frontDown"); // F

            user.turnPlane(cube, "rightUp"); // R2
            user.turnPlane(cube, "rightUp");

            user.turnPlane(cube, "topRight"); // U'
            user.turnPlane(cube, "rightDown"); // R'
            user.turnPlane(cube, "topRight"); // U'

        }

        if (variant == 2) {

            user.turnPlane(cube, "rightUp"); // R
            user.turnPlane(cube, "topLeft"); // U
            user.turnPlane(cube, "rightDown"); // R'

            user.turnPlane(cube, "frontUp");// F'

            user.turnPlane(cube, "rightUp"); //R
            user.turnPlane(cube, "topLeft"); // U
            user.turnPlane(cube, "rightDown"); // R'

            user.turnPlane(cube, "topRight"); // U'
            user.turnPlane(cube, "rightDown"); // R'
            user.turnPlane(cube, "frontDown"); // F

            user.turnPlane(cube, "rightUp"); // R2
            user.turnPlane(cube, "rightUp");

            user.turnPlane(cube, "topRight"); // U'
            user.turnPlane(cube, "rightDown"); // R'
            user.turnPlane(cube, "topRight"); // U'

            user.turnPlane(cube, "topLeft"); // U2
            user.turnPlane(cube, "topLeft");

            user.turnPlane(cube, "rightUp"); // R
            user.turnPlane(cube, "topLeft"); // U
            user.turnPlane(cube, "rightDown"); // R'

            user.turnPlane(cube, "frontUp");// F'

            user.turnPlane(cube, "rightUp"); //R
            user.turnPlane(cube, "topLeft"); // U
            user.turnPlane(cube, "rightDown"); // R'

            user.turnPlane(cube, "topRight"); // U'
            user.turnPlane(cube, "rightDown"); // R'
            user.turnPlane(cube, "frontDown"); // F

            user.turnPlane(cube, "rightUp"); // R2
            user.turnPlane(cube, "rightUp");

            user.turnPlane(cube, "topRight"); // U'
            user.turnPlane(cube, "rightDown"); // R'
            user.turnPlane(cube, "topRight"); // U'

            user.turnPlane(cube, "topRight"); // U'

        }

    }

    bool isCorrectCorners(Cube &cube, Interface &user) {

        user.turnPlane(cube, "putOnRightSide");

        for (int i = 0; i < 4; i++) {

            if (!(cube.cubik[0][2][2].front == cube.cubik[0][2][1].front &&
                  cube.cubik[0][2][2].right == cube.cubik[0][1][2].right)) {

                return false;

            }

            user.turnPlane(cube, "perehvatLeft");

        }

        return true;

    }

    void putLastCornersCorrect(Cube &cube, Interface &user) {

        bool correct = 1;

        for (int i = 0; i < 4; i++) {

            if (!(cube.cubik[0][2][2].front == cube.cubik[0][2][1].front &&
                  cube.cubik[0][2][2].right == cube.cubik[0][1][2].right)) {

                correct = 0;

                break;

            }

            user.turnPlane(cube, "perehvatLeft");

        }

        if (correct) {

            return;

        }

        bool isCorrectCorner = 0;

        for (int i = 0; i < 4; i++) {

            if (cube.cubik[0][2][2].front == cube.cubik[0][2][1].front &&
                cube.cubik[0][2][2].right == cube.cubik[0][1][2].right) {

                isCorrectCorner = 1;

                user.turnPlane(cube, "perehvatLeft");
                user.turnPlane(cube, "perehvatLeft");

                break;
            }

            user.turnPlane(cube, "perehvatLeft");

        }

        user.turnPlane(cube, "putOnTheLeftSide");

        if (!isCorrectCorner) {

            user.turnPlane(cube, "topLeft"); // U2
            user.turnPlane(cube, "topLeft");

            user.turnPlane(cube, "rightUp"); //R

            user.turnPlane(cube, "topLeft"); // U2
            user.turnPlane(cube, "topLeft");

            user.turnPlane(cube, "rightDown"); // R'

            user.turnPlane(cube, "frontDown"); // F2
            user.turnPlane(cube, "frontDown");

            user.turnPlane(cube, "topLeft"); // U2
            user.turnPlane(cube, "topLeft");

            user.turnPlane(cube, "leftUp"); // L'

            user.turnPlane(cube, "topLeft"); // U2
            user.turnPlane(cube, "topLeft");

            user.turnPlane(cube, "leftDown"); // L

            user.turnPlane(cube, "frontDown"); // F2
            user.turnPlane(cube, "frontDown");

        }

        user.turnPlane(cube, "putOnRightSide");

        for (int i = 0; i < 4; i++) {

            if (cube.cubik[0][2][2].front == cube.cubik[0][2][1].front &&
                cube.cubik[0][2][2].right == cube.cubik[0][1][2].right) {

                isCorrectCorner = 1;
                user.turnPlane(cube, "perehvatLeft");
                user.turnPlane(cube, "perehvatLeft");

                break;

            }

            user.turnPlane(cube, "perehvatLeft");

        }

        user.turnPlane(cube, "putOnTheLeftSide");

        while (!isCorrectCorners(cube, user)) {

            user.turnPlane(cube, "putOnTheLeftSide");

            //U2 R U2 R’ F2 U2 L’ U2 L F2
            user.turnPlane(cube, "topLeft"); // U2
            user.turnPlane(cube, "topLeft");

            user.turnPlane(cube, "rightUp"); //R

            user.turnPlane(cube, "topLeft"); // U2
            user.turnPlane(cube, "topLeft");

            user.turnPlane(cube, "rightDown"); // R'

            user.turnPlane(cube, "frontDown"); // F2
            user.turnPlane(cube, "frontDown");

            user.turnPlane(cube, "topLeft"); // U2
            user.turnPlane(cube, "topLeft");

            user.turnPlane(cube, "leftUp"); // L'

            user.turnPlane(cube, "topLeft"); // U2
            user.turnPlane(cube, "topLeft");

            user.turnPlane(cube, "leftDown"); // L

            user.turnPlane(cube, "frontDown"); // F2
            user.turnPlane(cube, "frontDown");

        }

        while(cube.cubik[0][2][1].front != cube.cubik[1][2][1].front)
        {
            user.turnPlane(cube, "topLeft");
        }

    }
};

