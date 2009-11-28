#ifndef GRANADE_HPP
#define GRANADE_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

class Granade{

	public:
        RenderWindow* Window;
        b2World* world;

        float timer;
        bool active;

        b2BodyDef granadebodyDef;
        b2Body* granadebody;
        b2CircleDef granadeshapeDef;

        Shape Body;

        Image granadeImg;
        Sprite GranadeSp;

        Granade(RenderWindow* window, b2World* World, float PositionX, float PositionY, float VelocityX, float VelocityY);
        ~Granade();

        void Show();
        void InputHandling(Event ev);
        void Deactivate();

};

#endif
