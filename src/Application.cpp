#include <X11/Xlib.h>
#include <iomanip>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.hpp"
#include "Texture.hpp"
#include "Debug.hpp"
#include "Buttons.hpp"
#include "Files.hpp"
#include "Render.hpp"

int main () {
    Display* d = XOpenDisplay(NULL);
    Screen*  s = DefaultScreenOfDisplay(d);
    std::cout << "Screen Resoultion : " << s->height << " * " << s->width << std::endl;
    
    Init();

    unsigned int TXT = CreateTexture("../res/textures/TXT.png");

    BindTexture(TXT, 0);
    glClearColor(0.4f, 0.38f, 0.98f, 0);
    while (!glfwWindowShouldClose(GameWindow)) {
        Draw();
    }

    glfwTerminate();
}