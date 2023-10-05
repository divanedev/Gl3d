#pragma once
#include <vector>

struct Vec3f {
    float x, y, z;
};

struct Vec4f {
    float r, g, b, a;
};

struct Vertex {
    Vec3f Positions;
    Vec4f Color;
};

std::vector <unsigned int> indicies;
std::vector <Vertex> vertexes;
