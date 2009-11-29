#ifndef WEAPON_HPP
#define WEAPON_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include "TempObjectHandler.hpp"

using namespace std;
using namespace sf;

class Weapon {

	public:
        struct data{
            string label;
            void* object;
        };

        bool fliped;

        RenderWindow* Window;
        b2World* world;
        TempObjectHandler* TOH;

        b2BodyDef weaponbodyDef;
        b2Body* weaponbody;
        b2PolygonDef weaponshapeDef;
        data weapondata;

        Image weaponImg;
        Sprite WeaponSp;

        Weapon(){};
        Weapon(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY);

        virtual void LoadImage(string file);
        virtual void FlipX(bool flip);
        virtual void Show();
        virtual void InputHandling(Event ev);

};

#endif

