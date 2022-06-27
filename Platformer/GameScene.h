#ifndef  GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"
#include "Background.h"
#include "PixelCollision.h"

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
    STAGE stage;
    Player* player;
    Background* background;
    PixelCollision* pixelCollision;
};

#endif // GAMESCENE_H
