#ifndef GEMOUSE_H
#define GEMOUSE_H

#include <SDL/SDL.h>



class GEMouse
{
public:
    GEMouse();
    static void update();
    static void getMousePos(int &x, int &y);
    static bool isButtonPressed(int button);
};

#endif // GEMOUSE_H
