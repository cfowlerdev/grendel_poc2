#include <iostream>
#include "opengl/texture2d.h"
#include <STB_IMAGE/stb_image.h>

Texture2D::Texture2D(const std::string& p_filename, int slotId)
    : _slotId(slotId)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imageData = stbi_load(p_filename.c_str(), &_width, &_height, &_bpp, 0);
    if(!imageData)
    {
        std::cout << "ERROR : Failed to load texture : " << p_filename << std::endl;
        return;
    }

    GLint imageFormat;
    switch(_bpp)
    {
        case 1:
            imageFormat = GL_RED;
            break;
        case 3:
            imageFormat = GL_RGB;
            break;
        case 4:
            imageFormat = GL_RGBA;
            break;
    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, _width, _height, 0, imageFormat, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(imageData);
}

Texture2D::~Texture2D() 
{}

void Texture2D::bind()
{
    glActiveTexture(GL_TEXTURE0 + _slotId);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture2D::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
