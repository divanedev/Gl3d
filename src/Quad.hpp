#pragma once
#include <vector>
#include <iostream>
#include "Entity.hpp"

void addQuad (float x1, float x2, float y1, float y2, float z1, float z2, float r, float g, float b, float a) {
    float positions[] = {
        x1, y1, z1, 1 - r, g, 1 - b, a,
        x2, y1, z1, 1 - r, g, 1 - b, a,
        x2, y1, z2, 1 - r, g, 1 - b, a,
        x1, y1, z2, 1 - r, g, 1 - b, a,
        x1, y2, z1, r, g, b, a,
        x2, y2, z1, r, g, b, a,
        x2, y2, z2, r, g, b, a,
        x1, y2, z2, r, g, b, a
    };

    unsigned int indexes[] = {
        0, 1, 2, 
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        0, 3, 7,
        7, 4, 0,
        6, 2, 1, 
        1, 5, 6, 
        0, 4, 5,
        5, 1, 0,
        3, 7, 6,
        6, 2, 3
    };
    for (int i = 0; i < 36; i++) {
        indicies.push_back(indexes[i] + ((int)vertexes.size()));
    }
    for (int i = 0; i < 8 * 7; i += 7) {
        vertexes.push_back({positions[i], positions[i + 1], positions[i + 2], positions[i + 3], positions[i + 4], positions[i + 5], positions[i + 6]});
    }
}
