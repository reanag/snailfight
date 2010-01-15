#ifndef GAME_HPP
#define GAME_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include "GameLogic.hpp"
#include "TempObjectHandler.hpp"
#include "Stage.hpp"
#include "Snail.hpp"
#include "Pool.cpp"
#include "Menu.hpp"

using namespace std;
using namespace sf;

class GameLogic;
class Snail;
class Pool;
class Game{

	public:
        Pool* pPoo;
        Menu* menu;
        RenderWindow* Window;
        bool InGame;
        b2World* world;

        float32 timeStep;
        int32 iterations;

        GameLogic* Logic;
        TempObjectHandler* TOH;

        Stage* GameStage;

        Snail* MySnail;
        Snail* OtherSnail;

        View GameView;

        Game( RenderWindow* window, int i, Pool* p, Menu* m);

        void Show();
        void GameLoop();

};

#endif


