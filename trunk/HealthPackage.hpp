#ifndef HEALTHPACKAGE_HPP
#define HEALTHPACKAGE_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Package.hpp"
#include "TempObjectHandler.hpp"

using namespace std;
using namespace sf;

class TempObjectHandler;

class HealthPackage : public Package{

	public:
        int addHeal;
        /*int number;

        b2BodyDef packagebodyDef;
        b2Body* packagebody;
        b2PolygonDef packageshapeDef;
        data packagedata;

        Image packageImg;
        Sprite PackageSp;*/

        HealthPackage(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY);
/*
        void Show();
        void InputHandling();
        void DestroyPackage();
        void SetNumber(int num);
        int GetNumber();
*/
};

#endif
