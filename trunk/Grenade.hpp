#ifndef GRENADE_HPP
#define GRENADE_HPP
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

class Grenade : public Object{

	public:
        RenderWindow* Window;
        b2World* world;
        TempObjectHandler* TOH;

        int damage;
        float timer;
        bool exploding;
        bool lim;

        int number;

        b2BodyDef grenadebodyDef;
        b2Body* grenadebody;
        b2CircleDef grenadeshapeDef;
        data grenadedata;

        Image grenadeImg;
        Sprite GrenadeSp;
        Image detonation[3];
        int iter;
        int iter2;
        SoundBuffer Buffer;
        Sound Explode;

        Grenade(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, float VelocityX, float VelocityY);

        void Show();
        void ApplyForces();
        void InputHandling(Event ev);
        void DestroyGrenade();
        void SetNumber(int num);
        int GetNumber();

};

#endif
