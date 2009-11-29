#ifndef GAME_HPP
#define GAME_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include "GameLogic.hpp"
#include "TempObjectHandler.hpp"
#include "Snail.hpp"

using namespace std;
using namespace sf;

class GameLogic;

class Game{
    struct data{
        string label;
        void* object;
    };

	public:
        RenderWindow* Window;
        bool InGame;
        b2World* world;

        float32 timeStep;
        int32 iterations;

        GameLogic* Logic;
        TempObjectHandler* TOH;

        b2Body* groundBody;
        data grounddata;
        Shape Ground;
        b2Body* wall1Body;
        data wall1data;
        Shape Wall1;
        b2Body* wall2Body;
        data wall2data;
        Shape Wall2;
        b2Body* roofBody;
        data roofdata;
        Shape Roof;
        Snail* MySnail;
        Snail* OtherSnail;

        Game(RenderWindow* window);

        void Show();
        void GameLoop();

};

#endif


