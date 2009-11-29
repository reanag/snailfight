#ifndef GRENADE_HPP
#define GRENADE_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include "TempObjectHandler.hpp"

using namespace std;
using namespace sf;

class TempObjectHandler;

class Grenade{
    struct data{
        string label;
        void* object;
    };

	public:
        RenderWindow* Window;
        b2World* world;
        TempObjectHandler* TOH;

        float timer;
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
        void InputHandling(Event ev);
        void DestroyGrenade();
        void SetNumber(int num);
        int GetNumber();

};

#endif
