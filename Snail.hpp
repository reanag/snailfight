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
#include "RocketLauncher.hpp"
#include "Grenade.hpp"
#include "TargetPointChangeEvent.hpp"
#include "MoveLeftEvent.hpp"
#include "Pool.cpp"
//#include "Menu.hpp"

using namespace std;
using namespace sf;

class TempObjectHandler;
class Pool;

class Snail : public Object{

	public:
        Pool* poo;
        Menu* menu;
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
        b2RevoluteJointDef gunjoint;

        Vector2f Mouse; // ! //

        //Image lightImg;
        //Sprite LightSp;

        Snail(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, bool Controlled, Pool* p, Menu* m);

        void FlipX(bool flip);
        void Hide(bool hide);
        void Die();
        void Show();
        void InputHandling();
        void EventHandling(Event ev);

        void SetTargetPoint(int x, int y);
        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void RollLeft();
        void RollRight();
        void Eye1Attak();
        void Eye2Attak();
        void Shot();
        void ThrowGrenade();
        void UseTurbo();
        void ChangeWeapon(int WeaponNumber);

        void Damage(int damage);
        void Heal(int heal);

};

#endif


