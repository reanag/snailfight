#ifndef STAGE2_HPP
#define STAGE2_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Object.hpp"
#include "TempObjectHandler.hpp"

using namespace std;
using namespace sf;

class Stage2 : public Object {

	public:
        /*class Line
        {
            b2Body* path02Body;
            data path02data;
            Shape Path02;
        public:
        Line(b2World* world2,int x, int y, int w, int h, string name)
        {

            b2BodyDef path02BodyDef;
            path02BodyDef.position.Set(x, y);
            path02Body = world2->CreateBody(&path02BodyDef);
            b2PolygonDef path02ShapeDef;
            path02ShapeDef.SetAsBox(w,h);
            path02Body->CreateShape(&path02ShapeDef);
            path02data.label=name;
            path02data.object=this;
            path02Body->SetUserData(&path02data);
            Path02=Shape::Rectangle(0, 0, path02ShapeDef.vertices[2].x*2, path02ShapeDef.vertices[2].y*2, Color(0,200,200));
            Path02.SetCenter(path02ShapeDef.vertices[2].x, path02ShapeDef.vertices[2].y);
            Path02.SetPosition(path02BodyDef.position.x,path02BodyDef.position.y);
        }
        };*/


        int BGWidth;
        int BGHeight;
        float BGScale;
        bool Visiblepath;

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
        b2Body* path01Body;
        data path01data;
        Shape Path01;
        b2Body* path02Body;
        data path02data;
        Shape Path02;
        b2Body* path03Body;
        data path03data;
        Shape Path03;
        b2Body* path04Body;
        data path04data;
        Shape Path04;
        b2Body* path05Body;
        data path05data;
        Shape Path05;
        b2Body* path06Body;
        data path06data;
        Shape Path06;
        b2Body* path07Body;
        data path07data;
        Shape Path07;
        b2Body* path08Body;
        data path08data;
        Shape Path08;
        b2Body* path09Body;
        data path09data;
        Shape Path09;
        b2Body* path10Body;
        data path10data;
        Shape Path10;
        b2Body* path11Body;
        data path11data;
        Shape Path11;
        b2Body* path12Body;
        data path12data;
        Shape Path12;
        b2Body* path13Body;
        data path13data;
        Shape Path13;
        b2Body* path14Body;
        data path14data;
        Shape Path14;
        b2Body* path15Body;
        data path15data;
        Shape Path15;
        b2Body* path16Body;
        data path16data;
        Shape Path16;
        b2Body* path17Body;
        data path17data;
        Shape Path17;
        b2Body* path18Body;
        data path18data;
        Shape Path18;
        b2Body* path19Body;
        data path19data;
        Shape Path19;
        b2Body* path20Body;
        data path20data;
        Shape Path20;
        b2Body* path21Body;
        data path21data;
        Shape Path21;
        b2Body* path22Body;
        data path22data;
        Shape Path22;
        b2Body* path23Body;
        data path23data;
        Shape Path23;
        b2Body* path24Body;
        data path24data;
        Shape Path24;

        b2Body* balcony01Body;
        data balcony01data;
        Shape Balcony01;
        b2Body* balcony02Body;
        data balcony02data;
        Shape Balcony02;
        b2Body* balcony03Body;
        data balcony03data;
        Shape Balcony03;
        b2Body* balcony04Body;
        data balcony04data;
        Shape Balcony04;
        b2Body* balcony05Body;
        data balcony05data;
        Shape Balcony05;

        b2Body* tree201Body;
        data tree201data;
        Shape Tree201;
        b2Body* tree202Body;
        data tree202data;
        Shape Tree202;
        b2Body* tree203Body;
        data tree203data;
        Shape Tree203;
        b2Body* tree204Body;
        data tree204data;
        Shape Tree204;
        b2Body* tree205Body;
        data tree205data;
        Shape Tree205;
        b2Body* tree206Body;
        data tree206data;
        Shape Tree206;

        Image grassImg;
        Sprite GrassSp;
        Image bacgroundImg;
        Sprite BacgroundSp;
        Image topImg;
        Sprite topSp;
        //Image treeImg;
        //Sprite TreeSp;

        //Stage(RenderWindow* window, b2World* World, TempObjectHandler* toh);
        Stage2();
        void MakeStage(RenderWindow* window, b2World* World, TempObjectHandler* toh);
        int Width(){return BGWidth;};
        int Height(){return BGHeight;};
        int RelativeWidth(float percent){return (int)(((float)BGWidth)*percent*0.01);};
        int RelativeHeight(float percent){return (int)(((float)BGHeight)*percent*0.01);};

        void Show();
        void ShowAfter();
        void InputHandling(/*Event ev*/);

};

#endif
