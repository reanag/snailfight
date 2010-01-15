#ifndef DESTROYABLEBODY_HPP
#define DESTROYABLEBODY_HPP
#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <math.h>
#include <vector>
#include "Object.hpp"
#include "TempObjectHandler.hpp"

using namespace std;
using namespace sf;

struct position;

class DestroyableBody : public Object{
	public:
        struct position{
            b2PolygonDef* polygon;
            b2Shape* shape;
            unsigned int positionX;
            unsigned int positionY;
            int iterI;
            //int iterJ;
            position* left;
            position* right;
            position* up;
            position* down;
            bool suspended;
            bool checked;

            position(){
                polygon=0;
                shape=0;
                positionX=0;
                positionY=0;
                iterI=0;
                //iterJ=0;
                left=0;
                right=0;
                up=0;
                down=0;
                suspended=false;
                checked=false;
            }

            position(unsigned int posX, unsigned int posY, b2PolygonDef* poly){
                polygon=poly;
                shape=0;
                iterI=0;
                //iterJ=0;
                positionX=posX;
                positionY=posY;
                left=0;
                right=0;
                up=0;
                down=0;
                suspended=false;
                checked=false;
            }

            ~position(){
                polygon=0;
                shape=0;
                if(left){
                    left->right=0;
                    left=0;
                }
                if(right){
                    right->left=0;
                    right=0;
                }
                if(up){
                    up->down=0;
                    up=0;
                }
                if(down){
                    down->up=0;
                    down=0;
                }
            }

            /*position* position::GetLeft(){
                if(left!=NULL)return left;
            }
            position* position::GetRight(){
                if(right!=NULL)return right;
            }
            position* position::GetUp(){
                if(up!=NULL)return up;
            }
            position* position::GetDown(){
                if(down!=NULL)return down;
            }*/

        };

        RenderWindow* Window;
        b2World* world;
        TempObjectHandler* TOH;

        int number;

        bool deleteable;
        bool breaking;
        bool isstatic;
        int iter;
        int shapecount;
        int Ilimit;
        int Jlimit;

        b2BodyDef destroyablebodyDef;
        b2Body* destroyablebody;
        //b2PolygonDef dshapeDef;
        data destroyablebodydata;

        //Shape Body;
        //vector<Shape> Body;
        vector<position*> positions;
        vector<position> position_collector;
        position* first;
        position* bottom;

        Image DBodyImg;
        Sprite DBodySp;
        Image bulletholeImg1;
        Image bulletholeImg2;

        DestroyableBody(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, float Angle, bool IsStatic);
        DestroyableBody(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, float Angle, vector<position> NewPositions, Image image, int ilimit, int jlimit);

        void Show();
        void InputHandling();
        void GetNext(position* p);
        //void GetLeft(position* p);
        void GetRight(position* p);
        //void GetUp(position* p);
        void FindBottom(position* p);
        void UnCheck();
        bool IsUnbroken(position* p);
        void EliminateShape(b2Shape* shape);
        void CollectShapes(position* p);
        void SetNumber(int num);
        int GetNumber();

};

#endif

