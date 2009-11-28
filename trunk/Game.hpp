#ifndef GAME_HPP
#define GAME_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Snail.hpp"

using namespace std;
using namespace sf;

class Game{

	public:
        RenderWindow* Window;
        bool InGame;
        b2World* world;

        float32 timeStep;
        int32 iterations;

        b2Body* groundBody;
        Shape Ground;
        b2Body* wall1Body;
        Shape Wall1;
        b2Body* wall2Body;
        Shape Wall2;
        b2Body* roofBody;
        Shape Roof;
        Snail* MySnail;

        Game(RenderWindow* window);

        void Show();
        void GameLoop();

};

#endif


