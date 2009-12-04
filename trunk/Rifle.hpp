#ifndef RIFLE_HPP
#define RIFLE_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Object.hpp"
#include "TempObjectHandler.hpp"
#include "Bullet.hpp"

using namespace std;
using namespace sf;

class Weapon;
#include "Weapon.hpp"
class TempObjectHandler;

class Rifle : public Weapon{

	public:
        float firespeed;
        float timer;
        bool MouseTargeting;

        bool showmuzzle;
        Image muzzleImg;
        Sprite MuzzleSp;

        SoundBuffer Buffer;
        Sound WeaponFireSound;

        Rifle(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY);

        //void FlipX(bool flip);
        void Show();
        void InputHandling(Event ev);
        void Shot();

};

#endif
