#ifndef WEAPON_HPP
#define WEAPON_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include "TempObjectHandler.hpp"

using namespace std;
using namespace sf;

class Weapon : public Object {

	public:
        int damage;
        float timer;
        float firespeed;
        float clip;
        bool fliped;
        bool MouseTargeting;
        bool showmuzzle;
        bool inUse;

        RenderWindow* Window;
        b2World* world;
        TempObjectHandler* TOH;

        b2BodyDef weaponbodyDef;
        b2Body* weaponbody;
        b2PolygonDef weaponshapeDef;
        data weapondata;

        Image weaponImg;
        Sprite WeaponSp;
        Image muzzleImg;
        Sprite MuzzleSp;

        SoundBuffer WeaponFireSoundBuffer;
        Sound WeaponFireSound;
        SoundBuffer WeaponReloadSoundBuffer;
        Sound WeaponReloadSound;

        Weapon(){};
        Weapon(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY);

        virtual ~Weapon(){};
        virtual void CreateBody(float PositionX, float PositionY);
        virtual void LoadImage(string file);
        virtual void LoadMuzzle(string file);
        virtual void LoadSound(string file);
        virtual void FlipX(bool flip);
        virtual void Show();
        virtual void InputHandling(Event ev);
        virtual void Shot();
        virtual void Use(float PositionX, float PositionY);
        virtual void UnUse();

};

#endif

