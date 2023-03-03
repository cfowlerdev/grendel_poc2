#pragma once
#include "objects/camera.h"

class Renderer
{
public:
    Renderer();

    void render(const Camera& p_camera);
    
};
