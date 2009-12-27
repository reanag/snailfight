#ifndef BULLET_HPP
#define BULLET_HPP
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

class Bullet : public Object{

	public:
        RenderWindow* Window;
        b2World* world;
        TempObjectHandler* TOH;

        int damage;

        bool lim;
        int number;

        b2BodyDef bulletbodyDef;
        b2Body* bulletbody;
        b2CircleDef bulletshapeDef;
        data bulletdata;

        Shape BulletSp;
        SoundBuffer Buffer;
        Sound Explode;

        Bullet(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, float VelocityX, float VelocityY, int Damage);

        void Show();
        void InputHandling(Event ev);
        void DestroyBullet();
        void SetNumber(int num);
        int GetNumber();

};

#endif
