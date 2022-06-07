#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//// как Гагарин сказал - Поехали!!
#include <stdio.h>
#include <stdlib.h>
#include "lilCube.h"
#include "Cube.h"
#include "windows.h"
#include "interface.h"
#include "Friedrich.h"
#include <fstream>
#include <queue>


//add_executable(kubikBubik main.cpp lilCube.h Cube.h Friedrich.h interface.h programInterface.h glad/src/glad.c)

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Константы
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

int main() {

    std::ofstream out("L");
    out << "hello work pls\n";
    out.close();

    Friedrich algo;
    Interface user;
    Cube cube = user.createCubik();


    std::string command = "";

    std::map<std::string, int> commandToInt = {{"stop", 0}, {"move", 1}, {"assembly", 2},
                                               {"save", 3}, {"input", 4}, {"shaffle", 5},
                                               {"show", 6}};


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw создание окна
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cubik Rubik", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: загрузка всех указателей на OpenGL-функции
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    const char *vertexShaderSource = "#version 330 core\n"
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

    colors[0] = fragmentShader5SourceGreen;
    colors[1] = fragmentShader6SourceBlue;
    colors[2] = fragmentShader2SourceYellow;
    colors[3] = fragmentShader4SourceWhite;
    colors[4] = fragmentShader3SourceRed;
    colors[5] = fragmentShader1SourceOrange;

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
    for(int i = 0; i < n; i++) {
        glGenVertexArrays(1, &VAOs[i]);
        glGenBuffers(1, &VBOs[i]);
        glGenBuffers(1, &EBOs[i]);
        glBindVertexArray(VAOs[i]);

        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vert[i], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    std::vector<int> assembl;

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        if(assembl.empty()) {

            bool fromFile = 0;

            // Рендеринг
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            std::vector<int> colorSide(54);
            int ind = 0;
            int cnt = 1;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    colorSide[ind++] = cube.cubik[0][i][j].top;
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int k = 0; k < 3; k++) {
                    colorSide[ind++] = cube.cubik[i][k][0].left;
                }
            }
            for (int i = 0; i < 3; i++) {
                for (int k = 0; k < 3; k++) {
                    colorSide[ind++] = cube.cubik[i][2][k].front;
                }
            }
            for (int i = 0; i < 3; i++) {
                for (int k = 2; k >= 0; k--) {
                    colorSide[ind++] = cube.cubik[i][k][2].right;
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int k = 2; k >= 0; k--) {
                    colorSide[ind++] = cube.cubik[i][0][k].back;
                }
            }

            for (int i = 2; i >= 0; i--) {
                for (int j = 0; j < 3; j++) {
                    colorSide[ind++] = cube.cubik[2][i][j].button;
                }
            }

            for (int i = 0; i < n; i++) {
                glUseProgram(shaderProgram[colorSide[i]]);
                glBindVertexArray(
                        VAOs[i]); // поскольку у нас есть только один VАО, то нет необходимости связывать его каждый раз, но мы сделаем это, чтобы всё было немного более организованно
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }

            glfwSwapBuffers(window);
            glfwPollEvents();


            std::cout << "Input command\n";
            std::cout << "command stop - switch off game\n";
            std::cout << "command move - manual control\n";
            std::cout << "command assembly - assembly cubik by program\n";
            std::cout << "command shaffle - generate random condition\n";
            std::cout << "command show - show cubik\n";
            std::cout << "command save - save current condition\n";
            std::cout << "command input - input cibik condition\n";

            std::cin >> command;

            std::map<std::string, int> turnTypeToInt = {{"leftDown",         0},
                                                        {"leftUp",           1},
                                                        {"left180",          2},
                                                        {"rightDown",        3},
                                                        {"rightUp",          4},
                                                        {"right180",         5},
                                                        {"frontDown",        6},
                                                        {"frontUp",          7},
                                                        {"front180",         8},
                                                        {"backDown",         9},
                                                        {"backUp",           10},
                                                        {"back180",          11},
                                                        {"topLeft",          12},
                                                        {"topRight",         13},
                                                        {"top180",           14},
                                                        {"buttonLeft",       15},
                                                        {"buttonRight",      16},
                                                        {"button180",        17},
                                                        {"pifPaf",           18},
                                                        {"leftPifPaf",       19},
                                                        {"perehvatLeft",     20},
                                                        {"perehvatRight",    21},
                                                        {"putOnTheLeftSide", 22},
                                                        {"putOnRightSide",   23}};


            if (command == "move") {
                std::cin >> command;
                switch (turnTypeToInt[command]) {
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
                std::cout << "MOVE: " << command << std::endl;
                user.showCubik(cube);
            } else {
                std::ofstream output("L", std::ostream::app);
                switch (commandToInt[command]) {
                    case 0:
                        exit(0);
                        break;
                    case 1:
                        user.showCubik(cube);
                        break;
                    case 2:
                        output << "start" << std::endl;
                        buildCubik(cube, user, algo);
                        output << "finish" << std::endl;
                        output.close();
                        fromFile = 1;
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

            if (fromFile) {
                int curInd = 0;
                std::cout << "HERE" << std::endl;
                std::ifstream in("L");
                while (command != "start") {
                    in >> command;
                }
                std::cout << command << std::endl;
                in >> command;
                while (command != "finish") {
                    for (int i = 0; i < n; i++) {
                        if (command == "finish") {
                            break;
                        }
                        assembl.push_back(int(command[0] - '0'));

                        in >> command;
                    }
                }
                in.close();
            }

            fromFile = 0;
        }
        else{
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (int i = 0; i < n; i++) {
                glUseProgram(shaderProgram[assembl[i]]);
                glBindVertexArray(
                        VAOs[i]); // поскольку у нас есть только один VАО, то нет необходимости связывать его каждый раз, но мы сделаем это, чтобы всё было немного более организованно
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }

            for (int i = 0; i < n; i++) {
                assembl.erase(assembl.begin(), assembl.begin() + 1);
            }

            Sleep(500);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

    }

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна.
    // Обратите внимание, высота окна на Retina-дисплеях будет значительно больше, чем указано в программе
    glViewport(0, 0, width, height);
}