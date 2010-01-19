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
#include "Stage2.hpp"
#include "Snail.hpp"
#include "NetworkInterface.cpp"
#include "Pool.cpp"
#include "Menu.hpp"
#include "GameSurface.hpp"

using namespace std;
using namespace sf;

class GameLogic;
class Snail;
class Pool;


static Pool* pPoo;


class Game{

	public:

        int Width, Height;      // Módosítva by CseAn 2010.01.18

        RenderWindow* Window;
        bool InGame;
        b2World* world;

        float32 timeStep;
        int32 iterations;

        GameLogic* Logic;
        TempObjectHandler* TOH;

        Stage2* GameStage;
		GameSurface* Surface;

        Snail* MySnail;
        Snail* OtherSnail;

        View GameView;

        Game( RenderWindow* window, int i, string iP);
        //1 Game( RenderWindow* window, int i, Pool* p);
        void static ThreadCreateServerFunc(void* UserData);
        void static ThreadCreateClientFunc(void* UserData);
        string ip;
        string* p;


        void Show();
        void GameLoop();

};

#endif


