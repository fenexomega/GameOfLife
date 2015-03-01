#ifndef FINALGAME_H
#define FINALGAME_H

#include "../GEGame.h"
#include <vector>
#include <fstream>
#include "../Graphics/GObject.h"
#include "../Graphics/GELoadingAnimation.h"
#include "../Graphics/GETileMap.h"
#include "Game_Classes/Map.h"
#include "../GEInput.h"

extern float deltaTime;

class FinalGame : public GEGame
{
private:
    Map *map;
    int fps = 15;
public:
    float timeMedia = 0;
    FinalGame();
    ~FinalGame();
    void gameUpdate(long currentTime);
    void gameDraw();
    void gameDispose();

};

#endif // FINALGAME_H
