#ifndef MAP_H
#define MAP_H
#include <fstream>
#include "../../Graphics/GObject.h"
#include "../../GEGraphicsCore.h"
#include "../../GEGlobal.h"
#include "vector"
#include "array"
#include "../../GERandom.h"
#include "../../GEInput.h"
#include "../../GEMouse.h"


using namespace std;

class Map
{
private:
    bool ReversingTool;
    bool MirrorTool;
    bool editingMode;
    bool gliderTool;
    int FIELD_DIMENSION;
    int size = GE_GLOBAL_TILESIZE;
    int map[GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE][GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE];
    int checkCellState(int x, int y, int state);
    int c_left(int x, int y);
    int c_right(int x, int y);
    int c_up(int x, int y);
    int c_down(int x, int y);
    void processInput();
    void resetMatrix();
    void SaveFile();
    void modifyFigure(vector<array<int,2>> figure,int value);
    void showFigure(vector<array<int,2>> figure);
    void drawCellforEditing(int x, int y);
    
    vector<array<int,2>> gliderPos; 
    
public:
    Map();
    void Draw();
    void Update();
    int getMatrix(int x, int y);
    void setMatrix(int x,int y,int value);
};

#endif // MAP_H
