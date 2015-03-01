#include "Map.h"

Map::Map()
{
    FIELD_DIMENSION = GE_GLOBAL_SCREEN_HEIGHT/size;
    
    for (int x = 0; x < FIELD_DIMENSION; ++x)
    {
        for (int y = 0; y < FIELD_DIMENSION; ++y)
        {
            map[x][y] = GERandom::getInt(3);
        }
    }
    
    editingMode = false;
    ReversingTool = false;
    MirrorTool = false;
    gliderTool = false;
    
    
    gliderPos.push_back({-1,-1});
    gliderPos.push_back({ 0,-1});
    gliderPos.push_back({+1,-1});
    gliderPos.push_back({-1, 0});
    gliderPos.push_back({ 0,+1});
}   

void Map::resetMatrix()
{
    for (int x = 0; x < FIELD_DIMENSION; ++x)
    {
        for (int y = 0; y < FIELD_DIMENSION; ++y)
        {
            map[x][y] = 0;
        }
    }
}

void Map::Draw()
{
    int x,y;
    GEMouse::getMousePos(x,y);
    for (int x = 0; x < FIELD_DIMENSION; ++x)
    {
        for (int y = 0; y < FIELD_DIMENSION; ++y)
        {
            if(map[x][y] == 1)
                GEGraphicsCore::DrawRectangle(x*size,y*size,size,size,GEColor::Blue());
            if(map[x][y] == 2)
                GEGraphicsCore::DrawRectangle(x*size,y*size,size,size,GEColor::getColor(0,200,255));
        }
    }
    if(editingMode)
    {
        
        if(gliderTool)
            showFigure(gliderPos);
        else
            drawCellforEditing(x/size,y/size);
        GEGraphicsCore::Grid(GEColor::getColor(60,60,60),size);        
    }
    else
        GEGraphicsCore::Grid(GEColor::getColor(0,0,0),size);
}

void Map::Update()
{
    processInput();
    int x,y;
    GEMouse::getMousePos(x,y);    
    int aux[GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE][GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE];
    if(!editingMode)
    {
        for (int x = 0; x < FIELD_DIMENSION; ++x)
        {
            for (int y = 0; y < FIELD_DIMENSION; ++y)
            {
                aux[x][y] = checkCellState(x,y,map[(x)][y]);
            }
        }
        
        for (int x = 0; x < FIELD_DIMENSION; ++x)
        {
            for (int y = 0; y < FIELD_DIMENSION; ++y)
            {
                map[x][y] =  aux[x][y] ;
            }
        }
    }
    else
    {
        
        if(gliderTool)
        {
            if(GEMouse::isButtonPressed(1))
                modifyFigure(gliderPos,1);
            if(GEMouse::isButtonPressed(3))
                modifyFigure(gliderPos,0);
        }
        else
        {
            if(GEMouse::isButtonPressed(1))
                map[x/size][y/size] = 1;
            if(GEMouse::isButtonPressed(3))
                map[x/size][y/size] = 0;
        }
    }
    
    
}

void Map::modifyFigure(vector<array<int,2>> figure, int value)
{
    int x,y;
    int z = 1;
    GEMouse::getMousePos(x,y);   
    
    if(ReversingTool)
        z = -1;
    
    x /= size;
    y /= size;
    
    for (int i = 0; i < figure.size(); ++i) {
        if(MirrorTool)
            map[x + figure[i][1]*z][y + figure[i][0]*z] = value;
        else
            map[x + figure[i][0]*z][y + figure[i][1]*z] = value;
    }
}

void Map::processInput()
{
    
    if(GEInput::isKeyPressed(GEInput::DOWN))
        ReversingTool = true;
    if(GEInput::isKeyPressed(GEInput::UP))
        ReversingTool = false;
    
    if(GEInput::isKeyPressed(GEInput::LEFT))
        MirrorTool = true;
    if(GEInput::isKeyPressed(GEInput::RIGHT))
        MirrorTool = false;
    
    if(GEInput::isKeyPressed(GEInput::LCTRL))
    {
        if(GEInput::isKeyPressed(GEInput::r))
            resetMatrix();
        if(GEInput::isKeyPressed(GEInput::e))
            editingMode = !editingMode;
        if(GEInput::isKeyPressed(GEInput::s))
            SaveFile();
        
        
        
    }
    if(GEInput::isKeyPressed(GEInput::Number_1))
        gliderTool = !gliderTool;
}

int Map::checkCellState(int x, int y,int state)
{
    int counter = 0; 
    
    int l = this->c_left(x,y);
    int r = this->c_right(x,y);
    int u = this->c_up(x,y);
    int d = this->c_down(x,y);
    
    counter += map[l][y] ? 1 : 0;
    counter += map[r][y] ? 1 : 0;
    counter += map[x][u] ? 1 : 0;
    counter += map[x][d] ? 1 : 0;
    counter += map[l][u] ? 1 : 0;
    counter += map[l][d] ? 1 : 0;
    counter += map[r][u] ? 1 : 0;
    counter += map[r][d] ? 1 : 0;
    
    
    if(state == 0)
    {
        if(counter == 3)
            return 2;
        return 0;
    }
    else
    {
        if(counter == 2 || counter == 3)
            return 1;
        return 0;
        
    }
    
}

int Map::c_left(int x, int y)
{
    if( x <= 0 )
        return FIELD_DIMENSION-1;
    return x-1;
}

int Map::c_right(int x, int y)
{
    if( x >= (FIELD_DIMENSION-1) )
        return 0;
    return x+1;
}

int Map::c_up(int x, int y)
{
    if( y <= 0 )
        return FIELD_DIMENSION-1;
    return y-1;
}

int Map::c_down(int x, int y)
{
    if( y >= (FIELD_DIMENSION-1) )
        return 0;
    return y+1;
}

int Map::getMatrix(int x, int y)
{
    return map[x][y];
}

void Map::setMatrix(int x,int y,int value)
{
    map[x][y] = value;
}

void Map::SaveFile()
{
    ofstream file;
    file.open("map.txt");
    for (int x = 0; x < GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE; ++x)
    {
        for (int y = 0; y < GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE; ++y)
        {
            file << (map[x][y] > 0 ? 1 : 0);
        }
        file << endl;
    }
    file.close();
}

void Map::showFigure(vector<array<int,2>> figure)
{
    int x,y;
    int z = 1;
    GEMouse::getMousePos(x,y);
    x /= size;
    y /= size;
    
    if(ReversingTool)
        z = -1;
    
    
    for (int i = 0; i < figure.size(); ++i) 
    {
        if(MirrorTool)
            drawCellforEditing(x+figure[i][1]*z,y+figure[i][0]*z);
        else
            drawCellforEditing(x+figure[i][0]*z,y+figure[i][1]*z);
    }
}

void Map::drawCellforEditing(int x, int y)
{
    int xs = x*size;
    int ys = y*size;
    
    if(map[x][y])
        GEGraphicsCore::DrawRectangle(xs,ys,size,size,GEColor::Red());
    else
        GEGraphicsCore::DrawRectangle(xs,ys,size,size,GEColor::Green());
}
