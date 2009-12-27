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

using namespace std;
using namespace sf;

class GameLogic;

class Game{

	public:
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

        Game(RenderWindow* window);

        void Show();
        void GameLoop();

};

#endif


