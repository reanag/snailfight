#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Object.hpp"
#include "TempObjectHandler.hpp"

using namespace std;
using namespace sf;

class TempObjectHandler;

class Package : public Object{

	public:
        RenderWindow* Window;
        b2World* world;
        TempObjectHandler* TOH;

        string subcaste;
        int number;

        b2BodyDef packagebodyDef;
        b2Body* packagebody;
        b2PolygonDef packageshapeDef;
        data packagedata;

        Image packageImg;
        Sprite PackageSp;

        Package(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY);

        virtual void CreateBody(float PositionX, float PositionY);
        virtual void CreateBody(float PositionX, float PositionY, float HalfWidth, float HalfHeight);
        virtual void LoadImage(string file, Image& image, Sprite& sprite);
        virtual void Show();
        virtual void InputHandling();
        virtual void DestroyPackage();
        virtual void SetNumber(int num);
        virtual int GetNumber();

};

#endif
