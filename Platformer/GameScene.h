#ifndef  GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"

class GameScene : public Scene
{
public:
    GameScene();
    virtual ~GameScene();

public:
    void    Init();
    void    Update(float dt);
    void    Render(HDC hdc, float dt);
    void    Release();

private:
    Player* player;
};

#endif // ! GAMESCENE_H
