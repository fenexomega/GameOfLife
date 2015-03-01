#include "Engine.h"

Engine::Engine()
{
}

bool Engine::InitSystems()
{
    bool allGreat;
    allGreat = GEGraphicsCore::initGraphics();
    
    if(allGreat)
    {
        GE_LOG("All Systems Initialized. ");
        return true;
    }
    else
    {
        GE_LOG("Errors occurried. Closing :(");
        return false;
    }
}

bool Engine::DisposeSystems()
{
    GE_LOG("Disposing Systems");
    SDL_Quit();
}

void Engine::Run(GEGame *game)
{
    GETimer timer;
    GERandom::initRandomSeed();
    GE_LOG("Running Game");
    while(event.type != SDL_QUIT)
    {
        timer.Update();
        deltaTime = timer.getMedia();
        totalTime = timer.getTotalTime();
        
        SDL_PollEvent(&event);
        SDL_Delay(1000/GE_GLOBAL_FPS);
        GEMouse::update();
        GEInput::update();
        game->gameUpdate(timer.getSecondTime());
        
        //Clean the screen, draw, then update screen.
        GEGraphicsCore::clearScreen(0,0,0);
        game->gameDraw();
        GEGraphicsCore::UpdateScreen();
        if(GEInput::isKeyDown(GEInput::ESCAPE))
            break;
    }
    GE_LOG("Disposing Game");
    game->gameDispose();
    
    DisposeSystems();
}
