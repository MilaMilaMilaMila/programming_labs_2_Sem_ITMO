//
// Created by user on 12.05.2022.
//
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "lilCube.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <fstream>
#include <windows.h>
#include <random>


class Cube {
public:
    std::vector<std::vector<std::vector<LilCube>>> cubik;

    void cubikResize()
    {
        cubik.resize(3);
        for(auto &i : cubik)
        {
            i.resize(3);
            for(auto &j : i)
            {
                j.resize(3);
            }
        }
    }

    void initCubik()
    {

        cubikResize();
        std::ifstream input("test");
        int lilCubiksAmount;
        input >> lilCubiksAmount;
        for(int i = 0; i < lilCubiksAmount; i++)
        {
            int z, y, x;
            input >> z >> y >> x;
            cubik[z][y][x].initLilCubik(input);
        }
    }

    void printCubik()
    {
        int z = 0, y = 0, x = 0;
        for(auto i : cubik)
        {
            for(auto j : i)
            {
                for(auto k : j)
                {
                    std::cout << z << " " << y << " " << x++ << ":" << std::endl;
                    k.printLilCubik();
                }
                x = 0;
                y++;
            }
            y = 0;
            z++;
        }
    }

    void printCubikColour()
    {
        /*const char *vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";
        const char *fragmentShader1SourceOrange = "#version 330 core\n"
                                                  "out vec4 FragColor;\n"
                                                  "void main()\n"
                                                  "{\n"
                                                  "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                                  "}\n\0";
        const char *fragmentShader2SourceYellow = "#version 330 core\n"
                                                  "out vec4 FragColor;\n"
                                                  "void main()\n"
                                                  "{\n"
                                                  "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                                  "}\n\0";
        const char *fragmentShader3SourceRed = "#version 330 core\n"
                                               "out vec4 FragColor;\n"
                                               "void main()\n"
                                               "{\n"
                                               "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
                                               "}\n\0";
        const char *fragmentShader4SourceWhite = "#version 330 core\n"
                                                 "out vec4 FragColor;\n"
                                                 "void main()\n"
                                                 "{\n"
                                                 "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
                                                 "}\n\0";
        const char *fragmentShader5SourceGreen = "#version 330 core\n"
                                                 "out vec4 FragColor;\n"
                                                 "void main()\n"
                                                 "{\n"
                                                 "   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
                                                 "}\n\0";
        const char *fragmentShader6SourceBlue = "#version 330 core\n"
                                                "out vec4 FragColor;\n"
                                                "void main()\n"
                                                "{\n"
                                                "   FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
                                                "}\n\0";

        const char *colors[6];

        colors[0] = fragmentShader1SourceOrange;
        colors[1] = fragmentShader2SourceYellow;
        colors[2] = fragmentShader3SourceRed;
        colors[3] = fragmentShader4SourceWhite;
        colors[4] = fragmentShader5SourceGreen;
        colors[5] = fragmentShader6SourceBlue;

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentShader[6];
        for(auto &i : fragmentShader)
        {
            i = glCreateShader(GL_FRAGMENT_SHADER);
        }
        unsigned int shaderProgram[6];
        for(auto &i : shaderProgram)
        {
            i = glCreateProgram();
        }

        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        for(int i = 0; i < 6; i++)
        {
            glShaderSource(fragmentShader[i], 1, &colors[i], NULL);
            glCompileShader(fragmentShader[i]);
            glAttachShader(shaderProgram[i], vertexShader);
            glAttachShader(shaderProgram[i], fragmentShader[i]);
            glLinkProgram(shaderProgram[i]);
        }



        // Указывание вершин (и буферов) и настройка вершинных атрибутов
        float vertices[] = {
                0.5f,  0.5f, 0.0f,  // верхняя правая
                0.5f, -0.5f, 0.0f,  // нижняя правая
                -0.5f, -0.5f, 0.0f,  // нижняя левая
                -0.5f,  0.5f, 0.0f   // верхняя левая
        };

        int n = 54;

        float vert[n][12];
        float x = 0.0f, y = 0.6f;
        int ind = 0;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++){
                float vertix[] = {x, y, 0.0f,
                                  x + 0.08f, y, 0.0f,
                                  x + 0.08f, y + 0.1f, 0.0f,
                                  x, y + 0.1f, 0.0f};
                for(int k = 0; k < 12; k++)
                {
                    vert[ind][k] = vertix[k];
                }
                ind++;
                x += 0.08f;
            }
            y -= 0.1f;
            x = 0.0f;
        }

        x = -0.24f;
        y = 0.3f;

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++){
                float vertix[] = {x, y, 0.0f,
                                  x + 0.08f, y, 0.0f,
                                  x + 0.08f, y + 0.1f, 0.0f,
                                  x, y + 0.1f, 0.0f};
                for(int k = 0; k < 12; k++)
                {
                    vert[ind][k] = vertix[k];
                }
                ind++;
                x += 0.08f;
            }
            y -= 0.1f;
            x = -0.24f;
        }


        x = 0.0f;
        y = 0.3f;

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++){
                float vertix[] = {x, y, 0.0f,
                                  x + 0.08f, y, 0.0f,
                                  x + 0.08f, y + 0.1f, 0.0f,
                                  x, y + 0.1f, 0.0f};
                for(int k = 0; k < 12; k++)
                {
                    vert[ind][k] = vertix[k];
                }
                ind++;
                x += 0.08f;
            }
            y -= 0.1f;
            x = 0.0f;
        }

        x = 0.24f;
        y = 0.3f;

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++){
                float vertix[] = {x, y, 0.0f,
                                  x + 0.08f, y, 0.0f,
                                  x + 0.08f, y + 0.1f, 0.0f,
                                  x, y + 0.1f, 0.0f};
                for(int k = 0; k < 12; k++)
                {
                    vert[ind][k] = vertix[k];
                }
                ind++;
                x += 0.08f;
            }
            y -= 0.1f;
            x = 0.24f;
        }

        x = 0.48f;
        y = 0.3f;

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++){
                float vertix[] = {x, y, 0.0f,
                                  x + 0.08f, y, 0.0f,
                                  x + 0.08f, y + 0.1f, 0.0f,
                                  x, y + 0.1f, 0.0f};
                for(int k = 0; k < 12; k++)
                {
                    vert[ind][k] = vertix[k];
                }
                ind++;
                x += 0.08f;
            }
            x = 0.48f;
            y -= 0.1f;
        }

        x = 0.0f;
        y = 0.0f;

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++){
                float vertix[] = {x, y, 0.0f,
                                  x + 0.08f, y, 0.0f,
                                  x + 0.08f, y + 0.1f, 0.0f,
                                  x, y + 0.1f, 0.0f};
                for(int k = 0; k < 12; k++)
                {
                    vert[ind][k] = vertix[k];
                }
                ind++;
                x += 0.08f;
            }
            y -= 0.1f;
            x = 0.0f;
        }


        unsigned int indices[] = {  // помните, что мы начинаем с 0!
                0, 1, 3,  // первый треугольник
                1, 2, 3   // второй треугольник
        };
        unsigned int VBOs[n], VAOs[n], EBOs[n];
        for(int i = 0; i < n; i++){
            glGenVertexArrays(1, &VAOs[i]);
            glGenBuffers(1, &VBOs[i]);
            glGenBuffers(1, &EBOs[i]);
            glBindVertexArray(VAOs[i]);

            glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vert[i], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }*/


        std::vector<int> colorSide(54);
        int ind = 0;
        int cnt = 1;
        for(int i = 0; i < 3; i++)
        {
            std::cout << "            ";
            for(int j = 0; j < 3; j++)
            {
                std::cout << "   ";
                cubik[0][i][j].printSide("top", cnt++, colorSide[ind++]);
            }
            std::cout << std::endl;
        }

        for(int i = 0; i < 3; i++)
        {

            cnt = i * 3 + 1;
            for(int k = 0; k < 3; k++)
            {
                std::cout << "   " ;
                cubik[i][k][0].printSide("left", cnt++, colorSide[ind++]);

            }
            cnt = i * 3 + 1;
            for(int k = 0; k < 3; k++)
            {
                std::cout << "   ";
                cubik[i][2][k].printSide("front", cnt++, colorSide[ind++]);
            }
            cnt = i * 3 + 1;
            for(int k = 2; k >= 0; k--)
            {
                std::cout << "   ";
                cubik[i][k][2].printSide("right", cnt++, colorSide[ind++]);
            }
            cnt = i * 3 + 1;
            for(int k = 2; k >= 0; k--)
            {
                std::cout << "   ";
                cubik[i][0][k].printSide("back", cnt++, colorSide[ind++]);
            }
            std::cout << std::endl;
        }

        cnt = 1;
        for(int i = 2; i >= 0; i--)
        {
            std::cout << "            ";
            for(int j = 0; j < 3; j++)
            {
                std::cout << "   ";
                cubik[2][i][j].printSide("button", cnt++, colorSide[ind++]);
            }
            std::cout << std::endl;
        }

        /*for(int i = 0; i < n; i++){
            glUseProgram(shaderProgram[colorSide[i]]);
            glBindVertexArray(VAOs[i]); // поскольку у нас есть только один VАО, то нет необходимости связывать его каждый раз, но мы сделаем это, чтобы всё было немного более организованно
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }*/

    }

    void R_()
    {
        struct coords{
            int z, y, x;
        };

        std::vector<std::pair<coords, int>> cur(3), save(3);// coords, colour
        //cur - то, чем красим
        //save - то, что красим
        for(int i = 0; i < 3; i++)
        {
            cur[i] = {coords{0, i, 2}, cubik[0][i][2].top};
            save[i] = {coords{i, 2, 2}, cubik[i][2][2].front};
        }

        int ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].front = cur[ind++].second;
        }

        cur = save;
        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{2, i, 2}, cubik[2][i][2].button};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].button = cur[ind++].second;
        }

        cur = save;

        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{i, 0, 2}, cubik[i][0][2].back};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].back = cur[ind++].second;
        }

        cur = save;

        for(int i = 0; i < 3; i++)
        {
            save[i] = {coords{0, i, 2}, cubik[0][i][2].top};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].top = cur[ind++].second;
        }

        std::vector<std::vector<int>> savePlane(3, std::vector<int>(3));

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                savePlane[i][j] = cubik[i][j][2].right;
            }
        }

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                cubik[j][2 - i][2].right = savePlane[i][j];
            }
        }

    }

    void R2()
    {
        R_();
        R_();
    }

    void R()
    {
        R2();
        R_();
    }

    void L()
    {
        struct coords{
            int z, y, x;
        };

        std::vector<std::pair<coords, int>> cur(3), save(3);// coords, colour
        //cur - то, чем красим
        //save - то, что красим
        for(int i = 0; i < 3; i++)
        {
            cur[i] = {coords{0, i, 0}, cubik[0][i][0].top};
            save[i] = {coords{i, 2, 0}, cubik[i][2][0].front};
        }

        int ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].front = cur[ind++].second;
        }

        cur = save;
        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{2, i, 0}, cubik[2][i][0].button};
        }

        ind = 0;
        for(auto i : save)
        {
            //std::cout << i.first.z << ' ' << i.first.y << ' ' << i.first.x << std::endl;
            //std::cout << cur[ind].first.z << ' ' << cur[ind].first.y << ' ' << cur[ind].first.x << std::endl;
            cubik[i.first.z][i.first.y][i.first.x].button = cur[ind++].second;
        }

        cur = save;

        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{i, 0, 0}, cubik[i][0][0].back};
        }

        ind = 0;
        for(auto i : save)
        {
            //std::cout << i.first.z << ' ' << i.first.y << ' ' << i.first.x << ' '<< cur[ind].second << std::endl;
            cubik[i.first.z][i.first.y][i.first.x].back = cur[ind++].second;
        }

        cur = save;

        for(int i = 0; i < 3; i++)
        {
            save[i] = {coords{0, i, 0}, cubik[0][i][0].top};
        }

        ind = 0;
        for(auto i : save)
        {
            //std::cout << i.first.z << ' ' << i.first.y << ' ' << i.first.x << ' '<< cur[ind].second << std::endl;
            cubik[i.first.z][i.first.y][i.first.x].top = cur[ind++].second;
        }

        std::vector<std::vector<int>> savePlane(3, std::vector<int>(3));

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                savePlane[i][j] = cubik[i][j][0].left;
            }
        }

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                cubik[j][2 - i][0].left = savePlane[i][j];
            }
        }

    }

    void L2()
    {
        L();
        L();
    }

    void L_()
    {
        L2();
        L();
    }

    void U()
    {
        struct coords{
            int z, y, x;
        };

        std::vector<std::pair<coords, int>> cur(3), save(3);// coords, colour
        //cur - то, чем красим
        //save - то, что красим
        for(int i = 0; i < 3; i++)
        {
            cur[i] = {coords{0,0, i}, cubik[0][0][i].back};
            save[i] = {coords{0, i, 2}, cubik[0][i][2].right};
        }

        int ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].right = cur[ind++].second;
        }

        cur = save;
        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{0, 2, i}, cubik[0][2][i].front};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].front = cur[ind++].second;
        }

        cur = save;

        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{0, i, 0}, cubik[0][i][0].left};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].left = cur[ind++].second;
        }

        cur = save;

        for(int i = 0; i < 3; i++)
        {
            save[i] = {coords{0, 0, i}, cubik[0][0][i].back};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].back = cur[ind++].second;
        }

        std::vector<std::vector<int>> savePlane(3, std::vector<int>(3));

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                savePlane[i][j] = cubik[0][i][j].top;
            }
        }

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                cubik[0][j][2 - i].top = savePlane[i][j];
            }
        }
    }

    void U2()
    {
        U();
        U();
    }

    void U_()
    {
        U2();
        U();
    }

    void D_()
    {
        struct coords{
            int z, y, x;
        };

        std::vector<std::pair<coords, int>> cur(3), save(3);// coords, colour
        //cur - то, чем красим
        //save - то, что красим
        for(int i = 0; i < 3; i++)
        {
            cur[i] = {coords{2,0, i}, cubik[2][0][i].back};
            save[i] = {coords{2, i, 2}, cubik[2][i][2].right};
        }

        int ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].right = cur[ind++].second;
        }

        cur = save;
        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{2, 2, i}, cubik[2][2][i].front};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].front = cur[ind++].second;
        }

        cur = save;

        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{2, i, 0}, cubik[2][i][0].left};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].left = cur[ind++].second;
        }

        cur = save;

        for(int i = 0; i < 3; i++)
        {
            save[i] = {coords{2, 0, i}, cubik[2][0][i].back};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].back = cur[ind++].second;
        }

        std::vector<std::vector<int>> savePlane(3, std::vector<int>(3));

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                savePlane[i][j] = cubik[2][i][j].button;
            }
        }

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                cubik[2][j][2 - i].button = savePlane[i][j];
            }
        }
    }

    void D2()
    {
        D_();
        D_();
    }

    void D()
    {
        D2();
        D_();
    }

    void B_()
    {
        struct coords{
            int z, y, x;
        };

        std::vector<std::pair<coords, int>> cur(3), save(3);// coords, colour
        //cur - то, чем красим
        //save - то, что красим
        for(int i = 0; i < 3; i++)
        {
            cur[i] = {coords{0, 0, i}, cubik[0][0][i].top};
            save[i] = {coords{i, 0, 2}, cubik[i][0][2].right};
        }

        int ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].right = cur[ind++].second;
        }

        cur = save;
        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{2, 0, i}, cubik[2][0][i].button};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].button = cur[ind++].second;
        }

        cur = save;

        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{i, 0, 0}, cubik[i][0][0].left};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].left = cur[ind++].second;
        }

        cur = save;

        for(int i = 0; i < 3; i++)
        {
            save[i] = {coords{0, 0, i}, cubik[0][0][i].top};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].top = cur[ind++].second;
        }

        std::vector<std::vector<int>> savePlane(3, std::vector<int>(3));

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                savePlane[i][j] = cubik[i][0][j].back;
            }
        }

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                cubik[j][0][2 - i].back = savePlane[i][j];
            }
        }

    }

    void B2()
    {
        B_();
        B_();
    }

    void B()
    {
        B2();
        B_();
    }

    void F()
    {
        struct coords{
            int z, y, x;
        };

        std::vector<std::pair<coords, int>> cur(3), save(3);// coords, colour
        //cur - то, чем красим
        //save - то, что красим
        for(int i = 0; i < 3; i++)
        {
            cur[i] = {coords{0, 2, i}, cubik[0][2][i].top};
            save[i] = {coords{i, 2, 2}, cubik[i][2][2].right};
        }

        int ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].right = cur[ind++].second;
        }

        cur = save;
        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{2, 2, i}, cubik[2][2][i].button};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].button = cur[ind++].second;
        }

        cur = save;

        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{i, 2, 0}, cubik[i][2][0].left};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].left = cur[ind++].second;
        }

        cur = save;

        for(int i = 0; i < 3; i++)
        {
            save[i] = {coords{0, 2, i}, cubik[0][2][i].top};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].top = cur[ind++].second;
        }

        std::vector<std::vector<int>> savePlane(3, std::vector<int>(3));

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                savePlane[i][j] = cubik[i][2][j].front;
            }
        }

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                cubik[j][2][2 - i].front = savePlane[i][j];
            }
        }
    }

    void F2()
    {
        F();
        F();
    }

    void F_()
    {
        F2();
        F();
    }

    void middleU()
    {
        struct coords{
            int z, y, x;
        };

        std::vector<std::pair<coords, int>> cur(3), save(3);// coords, colour
        //cur - то, чем красим
        //save - то, что красим
        for(int i = 0; i < 3; i++)
        {
            cur[i] = {coords{1,0, i}, cubik[1][0][i].back};
            save[i] = {coords{1, i, 2}, cubik[1][i][2].right};
        }

        int ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].right = cur[ind++].second;
        }

        cur = save;
        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{1, 2, i}, cubik[1][2][i].front};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].front = cur[ind++].second;
        }

        cur = save;

        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{1, i, 0}, cubik[1][i][0].left};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].left = cur[ind++].second;
        }

        cur = save;

        for(int i = 0; i < 3; i++)
        {
            save[i] = {coords{1, 0, i}, cubik[1][0][i].back};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].back = cur[ind++].second;
        }
    }

    void middleU_()
    {
        middleU();
        middleU();
        middleU();
    }

    void middleF()
    {
        struct coords{
            int z, y, x;
        };

        std::vector<std::pair<coords, int>> cur(3), save(3);// coords, colour
        //cur - то, чем красим
        //save - то, что красим
        for(int i = 0; i < 3; i++)
        {
            cur[i] = {coords{0, 1, i}, cubik[0][1][i].top};
            save[i] = {coords{i, 1, 2}, cubik[i][1][2].right};
        }

        int ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].right = cur[ind++].second;
        }

        cur = save;
        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{2, 1, i}, cubik[2][1][i].button};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].button = cur[ind++].second;
        }

        cur = save;

        for(int i = 2; i >= 0; i--)
        {
            save[2 - i] = {coords{i, 1, 0}, cubik[i][1][0].left};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].left = cur[ind++].second;
        }

        cur = save;

        for(int i = 0; i < 3; i++)
        {
            save[i] = {coords{0, 1, i}, cubik[0][1][i].top};
        }

        ind = 0;
        for(auto i : save)
        {
            cubik[i.first.z][i.first.y][i.first.x].top = cur[ind++].second;
        }
    }

    void middleF_()
    {
        middleF();
        middleF();
        middleF();
    }

};

