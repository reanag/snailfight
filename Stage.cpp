#include "Stage.hpp"

    Stage::Stage()
    {}

	void Stage::MakeStage(RenderWindow* window, b2World* World, TempObjectHandler* toh){
	    Window=window;
	    world=World;
	    TOH=toh;

    //ground
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(1200.0f, 1795.0f);
        b2Body* groundBody = world->CreateBody(&groundBodyDef);
        b2PolygonDef groundShapeDef;
        groundShapeDef.SetAsBox(1200.0f, 5.0f);
        groundShapeDef.friction=1.1f;
        groundBody->CreateShape(&groundShapeDef);
        grounddata.label="GROUND";
        grounddata.object=this;
        groundBody->SetUserData(&grounddata);
        //grassImg.LoadFromFile("contents/d.bg_grass.png");
        //grassImg.LoadFromFile("contents/xmas_ground.png");
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

        bacgroundImg.LoadFromFile("contents/Fantasy_War_014653_.jpg");
        BacgroundSp.SetImage(bacgroundImg);
        BacgroundSp.SetScale(1.5,1.5);

        b2BodyDef stageBodyDef;
        stageBodyDef.position.Set(520.0f, 1780.0f);
        stageBody = world->CreateBody(&stageBodyDef);
        b2PolygonDef stageShapeDef;

        stageShapeDef.SetAsBox(510.0f, 15.0f);
        stageBody->CreateShape(&stageShapeDef);

        stageShapeDef.SetAsBox(15.0f, 30.0f, b2Vec2(500,0),0);
        //stageShapeDef.localPosition.Set(500,0);
        stageBody->CreateShape(&stageShapeDef);

        stagedata.label="stage";
        stagedata.object=this;
        stageBody->SetUserData(&stagedata);
        //StageShape=Shape::Rectangle(0, 0, stageShapeDef.vertices[2].x*2, stageShapeDef.vertices[2].y*2, Color(0,0,200));
        StageShape=Shape::Rectangle(0, 0, 30, 60, Color(0,0,200));
        StageShape.SetCenter(stageShapeDef.vertices[2].x, stageShapeDef.vertices[2].y);
        //StageShape.SetPosition(stageBodyDef.position.x,stageBodyDef.position.y);
        StageShape.SetPosition(stageBodyDef.position.x+1000,stageBodyDef.position.y);

        stageImg.LoadFromFile("contents/roof.png");
        StageSp.SetImage(stageImg);
        StageSp.SetPosition(-100,1690);

        /*TOH->Add(new DestroyableBody(Window, world, TOH, 1600, 1500, 0, true));
        TOH->Add(new DestroyableBody(Window, world, TOH, 2000, 1500, 270, true));
        TOH->Add(new DestroyableBody(Window, world, TOH, 2100, 1500, 90, true));
        TOH->Add(new DestroyableBody(Window, world, TOH, 2100, 1000, 180, true));
        */
        for(int i=0;i<5;i++){
            TOH->Add(new DestroyableBody(Window, world, TOH, 300+(i*500), 1500, 270, true));
        }
	}

	void Stage::Show(){
	    //Window->Draw(Ground);
	    Window->Draw(BacgroundSp);
	    Window->Draw(StageSp);
	    //Window->Draw(StageShape);
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
        //db->Show();
        //db2->Show();
        //db3->Show();
    }

	void Stage::InputHandling(){
        //db->InputHandling();
        //db2->InputHandling();
        //db3->InputHandling();

	}

