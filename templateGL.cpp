#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <windows.h>
#include <random>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Константы
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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


int main()
{
    // glfw: инициализация и конфигурирование
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// Раскомментируйте данную часть кода, если используете macOS
/*
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
*/

    // glfw: создание окна
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

    // Построение и компилирование нашей шейдерной программы

    // На этот раз мы пропустили проверку ошибок компилирования для удобства чтения (если у вас возникнут какие-либо проблемы, то добавьте код проверки ошибок компилирования (смотрите предыдущие примеры))

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
    }
;

    // Сначала связываем объект вершинного массива, затем связываем и устанавливаем вершинный буфер(ы), и затем конфигурируем вершинный атрибут(ы)


    /*
    // Указывание вершин (и буферов) и настройка вершинных атрибутов
    float firstTriangle[] = {
            -0.9f, -0.5f, 0.0f,  // слева
            -0.0f, -0.5f, 0.0f,  // справа
            -0.45f, 0.5f, 0.0f,  // вверху
    };
    float secondTriangle[] = {
            0.0f, -0.5f, 0.0f,  // слева
            0.9f, -0.5f, 0.0f,  // справа
            0.45f, 0.5f, 0.0f   // вверху
    };
    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs); // мы также можем генерировать несколько VAO или буферов одновременно
    glGenBuffers(2, VBOs);

    // Настройка первого треугольника
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // вершинные атрибуты остаются прежними
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // нет необходимости выполнять отвязку, так как мы напрямую связываем другой VAO в следующих нескольких строках кода

    // Настройка второго треугольника
    glBindVertexArray(VAOs[1]);	// обратите внимание, что мы выполняем привязку другого VAO сейчас
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); // и другого VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // поскольку данные вершин плотно упакованы, то мы также можем указать 0 в качестве шага вершинного атрибута
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // это, на самом деле, не обязательно, но остерегайтесь вызовов, которые могут повлиять на VAO, пока он связан (как связывание объектов элементного буфера или подключение/отключение вершинных атрибутов)

    // Раскомментируйте следующую строку для отрисовки полигонов в режиме каркаса
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
     */

    // Цикл рендеринга
    int cnt = 0;
    while (!glfwWindowShouldClose(window))
    {
        // Обработка ввода
        processInput(window);


        // Рендеринг
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for(int i = 0; i < n; i++){
            glUseProgram(shaderProgram[rand() % 6]);
            glBindVertexArray(VAOs[i]); // поскольку у нас есть только один VАО, то нет необходимости связывать его каждый раз, но мы сделаем это, чтобы всё было немного более организованно
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }


        if(cnt > 6)
        {
            cnt = 0;
        }


        Sleep(500);

        // glfw: обмен содержимым front- и back-буферов. Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // Опционально: освобождаем все ресурсы, как только они выполнили свое предназначение
    /*glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);*/

    // glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
    glfwTerminate();
    return 0;
}

// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании кнопки мыши в данном кадре и соответствующая обработка данных событий
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