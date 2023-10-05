#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "Files.hpp"
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

float x = 0.25f, y = 1.25f, z = 0.0f;
float viewX = 0, viewY = 0;
GLFWwindow* GameWindow;
const float P2 = 6.28318530718;
double lstx = 0, lsty = 0, cx = 1050.0 / 2, cy = 1100.0 / 2;
bool started = false;

void CursorMove (GLFWwindow* window, double xpos, double ypos) {
    double xd = xpos - lstx;
    double yd = ypos - lsty;
    if (!started) {
        xd = 0;
        yd = 0;
    }
    lstx = xpos;
    lsty = ypos;
    started = true;
    cx += xd;
    cy += yd;
    cy = std::max(cy, 1100.0 / 4 + 0.5);
    cy = std::min(cy, (1100.0 / 4) * 3 - 0.5);
    viewX = -cx / 1050.0f;
    viewY = cy / 1100.0f;
}

void CharInput (GLFWwindow* GameWindow, unsigned int key) {

}

void KeyInput(GLFWwindow* GameWindow, int key, int scancode, int action, int mods) {
    
}

class Key {
public:
    Key(void (*Function)(), int FirstKey, int SecondKey = -1) 
        :m_Time(60), m_FirstKey(FirstKey), m_SecondKey(SecondKey), m_Function(Function) {};
    void Update();
private:
    int m_Time = 60;
    int m_FirstKey = -1;
    int m_SecondKey = -1;
    void (*m_Function)();
};

void Up () {
    float X = sin(viewX * P2) * 0.04f;
    float Z = cos(viewX * P2) * 0.04f;
    x -= X;
    z -= Z;
}

void Down() {
    float X = sin(viewX * P2) * 0.04f;
    float Z = cos(viewX * P2) * 0.04f;
    x += X;
    z += Z;
}

void Right() {
    float X = sin((viewX + 0.25) * P2) * 0.04f;
    float Z = cos((viewX + 0.25) * P2) * 0.04f;
    x += X;
    z += Z;
}

void Left () {
    float X = sin((viewX + 0.25) * P2) * 0.04f;
    float Z = cos((viewX + 0.25) * P2) * 0.04f;
    x -= X;
    z -= Z;
}

void Shift () {
    y -= 0.04f;
}

void Space() {
    y += 0.04f;
}

void Key::Update () {
    int state = glfwGetKey(GameWindow, m_FirstKey);
    int state2 = (m_SecondKey == -1 ? GLFW_PRESS : glfwGetKey(GameWindow, m_SecondKey));
    if (state == GLFW_PRESS && state2 == GLFW_PRESS) {
        if (m_Time == 0) {
            m_Function();
            m_Time = 2;
        } else {
            m_Time--;
            if (m_Time % 12 == 11) {
                m_Function();
            }
        }
    } else {
        m_Time = 60;
    }
}

Key GoFront(Up, GLFW_KEY_W, -1);
Key GoLeft(Left, GLFW_KEY_A, -1);
Key GoBack(Down, GLFW_KEY_S, -1);
Key GoRight(Right, GLFW_KEY_D, -1);
Key Jump (Space, GLFW_KEY_SPACE, -1);
Key GoDown (Shift, GLFW_KEY_LEFT_SHIFT, -1);

void HandleKeys() {
    GoBack.Update();
    GoRight.Update();
    GoFront.Update();
    GoLeft.Update();
    Jump.Update();
    GoDown.Update();
}