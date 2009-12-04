#include "Stage.hpp"

	Stage::Stage(RenderWindow* window, b2World* World, TempObjectHandler* toh){
	    Window=window;
	    world=World;
	    TOH=toh;

    //ground
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(1200.0f, 1795.0f);
        b2Body* groundBody = world->CreateBody(&groundBodyDef);
        b2PolygonDef groundShapeDef;
        groundShapeDef.SetAsBox(1200.0f, 5.0f);
        groundBody->CreateShape(&groundShapeDef);
        grounddata.label="GROUND";
        grounddata.object=this;
        groundBody->SetUserData(&grounddata);
        grassImg.LoadFromFile("contents/d.bg_grass.png");
        GrassSp.SetImage(grassImg);
        GrassSp.SetPosition(-50,1760);
        //Ground=Shape::Rectangle(0, 0, 800, 10, Color(0,0,200));
        //Ground.SetCenter(400,5);
        //Ground.SetPosition(400,595);
    //wall 1
        b2BodyDef wall1BodyDef;
        wall1BodyDef.position.Set(5.0f, 900.0f);
        wall1Body = world->CreateBody(&wall1BodyDef);
        b2PolygonDef wall1ShapeDef;
        wall1ShapeDef.SetAsBox(5.0f, 900.0f);
        wall1Body->CreateShape(&wall1ShapeDef);
        wall1data.label="wall1";
        wall1data.object=this;
        wall1Body->SetUserData(&wall1data);
        Wall1=Shape::Rectangle(0, 0, wall1ShapeDef.vertices[2].x*2, wall1ShapeDef.vertices[2].y*2, Color(0,0,200));
        Wall1.SetCenter(wall1ShapeDef.vertices[2].x, wall1ShapeDef.vertices[2].y);
        Wall1.SetPosition(wall1BodyDef.position.x,wall1BodyDef.position.y);
    //wall 2
        b2BodyDef wall2BodyDef;
        wall2BodyDef.position.Set(2395.0f, 900.0f);
        wall2Body = world->CreateBody(&wall2BodyDef);
        b2PolygonDef wall2ShapeDef;
        wall2ShapeDef.SetAsBox(5.0f, 900.0f);
        wall2Body->CreateShape(&wall2ShapeDef);
        wall2data.label="wall2";
        wall2data.object=this;
        wall2Body->SetUserData(&wall2data);
        Wall2=Shape::Rectangle(0, 0, wall2ShapeDef.vertices[2].x*2, wall2ShapeDef.vertices[2].y*2, Color(0,0,200));
        Wall2.SetCenter(wall2ShapeDef.vertices[2].x, wall2ShapeDef.vertices[2].y);
        Wall2.SetPosition(wall2BodyDef.position.x,wall2BodyDef.position.y);
    //roof
        b2BodyDef roofBodyDef;
        roofBodyDef.position.Set(1200.0f, 5.0f);
        roofBody = world->CreateBody(&roofBodyDef);
        b2PolygonDef roofShapeDef;
        roofShapeDef.SetAsBox(1200.0f, 5.0f);
        roofBody->CreateShape(&roofShapeDef);
        roofdata.label="roof";
        roofdata.object=this;
        roofBody->SetUserData(&roofdata);
        Roof=Shape::Rectangle(0, 0, roofShapeDef.vertices[2].x*2, roofShapeDef.vertices[2].y*2, Color(0,0,200));
        Roof.SetCenter(roofShapeDef.vertices[2].x, roofShapeDef.vertices[2].y);
        Roof.SetPosition(roofBodyDef.position.x,roofBodyDef.position.y);

        /*treeImg.LoadFromFile("contents/fákk1.png");
        TreeSp.SetImage(treeImg);
        TreeSp.SetCenter(220,850);
        TreeSp.SetScale(2,2);
        TreeSp.SetPosition(5,1800);*/

	}

	void Stage::Show(){
	    //Window->Draw(Ground);
        Window->Draw(Wall1);
        Window->Draw(Wall2);
        Window->Draw(Roof);
        Window->Draw(GrassSp);
        GrassSp.SetPosition(-40,1765);
    }

	void Stage::ShowAfter(){
	    //Window->Draw(TreeSp);
        Window->Draw(GrassSp);
        GrassSp.SetPosition(-50,1760);
    }

	void Stage::InputHandling(Event ev){

	}

