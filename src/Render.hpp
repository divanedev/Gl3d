#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Buttons.hpp"
#include "Quad.hpp"
unsigned int va, vb, ib;
unsigned int Shader;
float near = 0.01f, far = 100.0f;

void Draw () {
    HandleKeys();
    glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.0f, 0.0f));
    float X, Y, Z;
    X = sin(viewX * P2);
    Z = cos(viewX * P2);
    Y = sin(viewY * P2);
    X *= cos(viewY * P2);
    Z *= cos(viewY * P2);
    glm::mat4 View = glm::lookAt(glm::vec3(x, y, z), glm::vec3(x + X, y + Y, z + Z), glm::vec3(0, 1, 0));
    //std::cout << X << ' ' << Y << ' ' << Z << std::endl;
    int width, height;
    glfwGetWindowSize(GameWindow, &width, &height);
    glm::mat4 Proj = glm::perspective(glm::radians(70.7f), (GLfloat)width / (GLfloat)height, near, far);
    glm::mat4 MVP = Proj * View * Model;
       
    UploadUniformMat4f (Shader, "u_MVP", MVP);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(GameWindow);
    glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Init () {
    int GlfwMajorVersion, GlfwMinorVersion, GlfwRevision;
    glfwGetVersion(&GlfwMajorVersion, &GlfwMinorVersion, &GlfwRevision);
    std::cout << std::endl << "GLFW version : " << ' ' << GlfwMajorVersion << "." << GlfwMinorVersion << ' ' << GlfwRevision << std::endl << std::endl;
    
    if (!glfwInit()) {
        std::cout << "GLFW did not start properly!" << std::endl;
        exit(-1);
    }

    glfwSetErrorCallback(GlfwErrorHappened);

    GameWindow = glfwCreateWindow(1280, 720, "Gl3D", NULL, NULL);

    if (!GameWindow) {
        std::cout << "GameWindow did not start correctly!" << std::endl;
        exit(-1);
    }

    glfwMakeContextCurrent(GameWindow);
    glfwSetFramebufferSizeCallback(GameWindow, framebuffer_size_callback);
    glfwSwapInterval(1);
    
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwSetWindowSizeLimits(GameWindow, 300, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwSetCharCallback(GameWindow, CharInput);
    glfwSetKeyCallback(GameWindow, KeyInput);

    if (glewInit() != GLEW_OK) {
        std::cout << "Coud not Initilize GLEW" << std::endl;
    }

    glfwSetInputMode(GameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(GameWindow, CursorMove);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(OpenGlErrorHappend, NULL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

    glGenVertexArrays(1, &va);
    glBindVertexArray(va);

    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);

    addQuad(-1.0f, +1.0f, -1.0f, -0.3f, -1.0f, +1.0f, 0.1f, 0.2f, 0.9f, 1.0f);

    addQuad (-0.5f, +0.5f, +1.5f, +1.6f, -0.5f, +0.5f, 1.0f, 0.2f, 0.3f, 1.0f);

    for (int i = 0; i < (int)vertexes.size(); i++) {
        std::cout << vertexes[i].Positions.x << ' ' << vertexes[i].Positions.y << ' ' << vertexes[i].Positions.z << std::endl;
    }
    for (int i = 0; i < (int)indicies.size(); i += 3) {
        std::cout << indicies[i] << ' ' << indicies[i + 1] << ' ' << indicies[i + 2] << std::endl;
    }

    glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(Vertex), static_cast<void*>(vertexes.data()), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)sizeof(Vec3f));

    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);


    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof (unsigned int), static_cast<void*>(indicies.data()), GL_STATIC_DRAW);

    std::pair <std::string, std::string> p = ParseShader("../res/shaders/basic.shader");

    std::string VertexShaderCode = p.first;
    std::string FragmentShaderCode = p.second;

    Shader = CreateShaderProgram(VertexShaderCode, FragmentShaderCode);

    glUseProgram(Shader);
 
}
