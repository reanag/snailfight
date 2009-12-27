#ifndef SNAIL_HPP
#define SNAIL_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <math.h>
#include "Object.hpp"
#include "TempObjectHandler.hpp"
#include "Weapon.hpp"
#include "Rifle.hpp"
#include "Rifle2.hpp"
#include "Rifle3.hpp"
#include "Grenade.hpp"

using namespace std;
using namespace sf;

class TempObjectHandler;

class Snail : public Object{

	public:
        RenderWindow* Window;
        b2World* world;
        TempObjectHandler* TOH;

        int Health;
        float Stamina;
        int Speed;
        bool alive;
        bool turbo;

        float grenadethrowspeed;
        float timer;

        bool fliped;
        bool hid;
        bool jump;
        bool controlled;
        bool up;
        bool once;
        float mx;
        float my;

        b2BodyDef snailbodyDef;
        b2Body* snailbody;
        b2PolygonDef bodyshapeDef;
        b2CircleDef houseshapeDef;
        b2CircleDef head1Def;
        b2CircleDef head2Def;
        data snaildata;

        b2DistanceJointDef jd;
        b2Vec2 d[6];

        b2BodyDef eye1Def;
        b2Body* eye1;
        b2CircleDef e1;
        data eye1data;

        b2BodyDef eye2Def;
        b2Body* eye2;
        b2CircleDef e2;
        data eye2data;

        Image snailImg[11];
        int aktImg;
        Image houseImg;
        Sprite SnailSp;
        Image eye1Img;
        Sprite Eye1Sp;
        Image eye2Img;
        Sprite Eye2Sp;

        vector<Weapon* > Weapons;
        int aktWeapon;
        Rifle2* RifleGun;
        b2RevoluteJointDef gunjoint;

        //Image lightImg;
        //Sprite LightSp;

        Snail(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY);

        void FlipX(bool flip);
        void Hide(bool hide);
        void Die();
        void Show();
        void InputHandling(Event ev);
        void EventHandling(Event ev);
        void Damage(int damage);
        void Heal(int heal);

};

#endif


