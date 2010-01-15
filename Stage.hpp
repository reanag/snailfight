#ifndef STAGE_HPP
#define STAGE_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Object.hpp"
#include "TempObjectHandler.hpp"
#include "DestroyableBody.hpp"

using namespace std;
using namespace sf;

class Stage : public Object {

	public:
        RenderWindow* Window;
        b2World* world;
        TempObjectHandler* TOH;

        b2Body* groundBody;
        data grounddata;
        //Shape Ground;
        b2Body* wall1Body;
        data wall1data;
        Shape Wall1;
        b2Body* wall2Body;
        data wall2data;
        Shape Wall2;
        b2Body* roofBody;
        data roofdata;
        Shape Roof;

        Image grassImg;
        Sprite GrassSp;
        Image bacgroundImg;
        Sprite BacgroundSp;
        //Image treeImg;
        //Sprite TreeSp;

        b2Body* stageBody;
        data stagedata;
        Shape StageShape;
        Image stageImg;
        Sprite StageSp;

        Stage(RenderWindow* window, b2World* World, TempObjectHandler* toh);

        void Show();
        void ShowAfter();
        void InputHandling();

};

#endif
