#define STB_IMAGE_IMPLEMENTATION
#include <string>
#include <stb/stb_image.h>
#include <iostream>
#include <GL/glew.h>

unsigned int CreateTexture (const std::string& TextureFilePath) {
    stbi_set_flip_vertically_on_load(1);
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
    unsigned int TextureId;
    m_LocalBuffer = stbi_load(TextureFilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    glGenTextures(1, &TextureId);
    glBindTexture(GL_TEXTURE_2D, TextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
    return TextureId;
}

void BindTexture(unsigned int TextureID, unsigned int TextureSlot = 0) {
    glActiveTexture(GL_TEXTURE0 + TextureSlot);
    glBindTexture(GL_TEXTURE_2D, TextureID);   
}
