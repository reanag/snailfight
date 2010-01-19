#ifndef TEMPOBJECT_HPP
#define TEMPOBJECT_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Object.hpp"
#include "TempObjectHandler.hpp"

using namespace std;
using namespace sf;

class TempObjectHandler;

class TempObject : public Object{

	public:
        RenderWindow* Window;
        b2World* world;
        TempObjectHandler* TOH;

        int number;

        b2BodyDef objectbodyDef;
        b2Body* objectbody;
        b2CircleDef objectshapeDef;
        //b2PolygonDef objectshapeDef;
        data objectdata;

        Image objectImg;
        Sprite ObjectSp;

        Shape debugDrawShape;
        bool debugDraw;

        TempObject(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY);

        virtual ~TempObject(){};
        virtual void CreateBody(float PositionX, float PositionY);
        virtual void CreateBody(float PositionX, float PositionY, float HalfWidth, float HalfHeight);
        virtual void LoadImage(string file, Image& image, Sprite& sprite);
        virtual void CreateDebugShape();
        virtual void Show();
        virtual void InputHandling();
        virtual void DestroyObject();
        virtual void SetNumber(int num);
        virtual int GetNumber();

};

#endif
