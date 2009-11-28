#ifndef RIFLE_HPP
#define RIFLE_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

class Rifle{

	public:
        RenderWindow* Window;
        b2World* world;

        b2BodyDef riflebodyDef;
        b2Body* riflebody;
        b2PolygonDef rifleshapeDef;

        Shape Body;

        Image rifleImg;
        Sprite RifleSp;

        b2MouseJointDef md;
        b2MouseJoint* mouseJoint;

        b2BodyDef bd;
        b2Body* bullet;
        b2CircleDef bullcd;
        Shape Bullet;


        bool fliped;

        Rifle(RenderWindow* window, b2World* World, float PositionX, float PositionY);

        void FlipX(bool flip);
        void Show();
        void InputHandling(Event ev);

};

#endif
