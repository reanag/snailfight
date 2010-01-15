#ifndef ROCKET_HPP
#define ROCKET_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include "Object.hpp"
#include "TempObjectHandler.hpp"

using namespace std;
using namespace sf;

class TempObjectHandler;

class Rocket : public Object{

	public:
        RenderWindow* Window;
        b2World* world;
        TempObjectHandler* TOH;

        int damage;

        bool exploding;
        bool lim;
        int number;

        float nullPositionX;
        float nullPositionY;

        b2BodyDef rocketbodyDef;
        b2Body* rocketbody;
        b2CircleDef rocketshapeDef;
        data rocketdata;

        //Shape BulletSp;
        Image rocketImg;
        Sprite RocketSp;
        int iter;
        int iter2;
        //SoundBuffer Buffer;
        Sound Explode;
        Sound Flight;

        Shape debugDrawShape;

        Rocket(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, float VelocityX, float VelocityY, int Damage);

        void Show();
        void ApplyForces();
        void InputHandling();
        void DestroyRocket();
        void SetNumber(int num);
        int GetNumber();
        int GetDamage();

};

#endif

