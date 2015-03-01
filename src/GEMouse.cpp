#include "GEMouse.h"

GEMouse::GEMouse()
{


}


void GEMouse::getMousePos(int &x, int &y)
{
    SDL_GetMouseState(&x,&y);
}

bool GEMouse::isButtonPressed(int button)
{
    if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(button))
        return true;
    return false;
}


void GEMouse::update()
{
    SDL_PumpEvents();

}
