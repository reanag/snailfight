#ifndef GRENADEPACKAGE_HPP
#define GRENADEPACKAGE_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Package.hpp"
#include "TempObjectHandler.hpp"

using namespace std;
using namespace sf;

class TempObjectHandler;

class GrenadePackage : public Package{

	public:
        int addGrenade;

        GrenadePackage(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY);

};

#endif
