#pragma once
#include <string>
#include "opengl/window.h"
#include "opengl/program.h"


class Engine {
public:
    void init(const std::string &p_title, const int &p_width, const int &p_height);

    void onUpdate();

    void loadEntities();

private:
    Window *_window;
    Program *_program;

    int _width;
    int _height;


};
