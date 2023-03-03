#include "renderers/renderer.h"

Renderer::Renderer()
{

}

void Renderer::render(const Camera& p_camera)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    // TODO: call each of the renderers
}
