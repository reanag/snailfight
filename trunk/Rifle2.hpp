#ifndef RIFLE2_HPP
#define RIFLE2_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Object.hpp"
#include "TempObjectHandler.hpp"
#include "Bullet.hpp"

using namespace std;
using namespace sf;

class TempObjectHandler;
#include "Weapon.hpp"
class Weapon;

class Rifle2 : public Weapon{

	public:
        Rifle2(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY);

};

#endif
