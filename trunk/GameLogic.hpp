#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include "ContactListener.hpp"
#include "Game.hpp"
#include "Snail.hpp"
#include "Rifle.hpp"
#include "Grenade.hpp"
#include "Bullet.hpp"
#include "Rocket.hpp"
#include "DestroyableBody.hpp"

using namespace std;
using namespace sf;

class GameLogic{
    struct data{
        string label;
        void* object;
    };

	public:
        RenderWindow* Window;
        b2World* world;

        ContactListener CL;

        data* data1;
        data* data2;

        GameLogic(RenderWindow* window, b2World* World);

        void LogicListener();

};

#endif
