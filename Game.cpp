#include "Game.hpp"

	Game::Game(RenderWindow* window){
	    Window=window;
	    InGame=false;

	    b2AABB worldAABB; // Define the size of the world. Simulation will still work if bodies reach the end of the world, but it will be slower.
        worldAABB.lowerBound.Set(-100.0f, -100.0f);
        worldAABB.upperBound.Set(900.0f, 700.0f);

        b2Vec2 gravity(0.0f, 5.0f); // Define the gravity vector.

        bool doSleep = false; // Do we want to let bodies sleep?
        world=new b2World(worldAABB, gravity, doSleep);

        timeStep = 1.0f / 10.0f;
        iterations = 10;

        Logic=new GameLogic(Window,world);
        TOH=new TempObjectHandler();
    //ground
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(400.0f, 595.0f);
        groundBody = world->CreateBody(&groundBodyDef);
        b2PolygonDef groundShapeDef;
        groundShapeDef.SetAsBox(400.0f, 5.0f);
        groundBody->CreateShape(&groundShapeDef); // Add the ground shape to the ground body.
        grounddata.label="GROUND";
        grounddata.object=this;
        groundBody->SetUserData(&grounddata);
        Ground=Shape::Rectangle(0, 0, 800, 10, Color(0,0,200));
        Ground.SetCenter(400,5);
        Ground.SetPosition(400,595);
    //wall 1
        b2BodyDef wall1BodyDef;
        wall1BodyDef.position.Set(5.0f, 300.0f);
        wall1Body = world->CreateBody(&wall1BodyDef);
        b2PolygonDef wall1ShapeDef;
        wall1ShapeDef.SetAsBox(5.0f, 300.0f);
        wall1Body->CreateShape(&wall1ShapeDef);
        wall1data.label="wall1";
        wall1data.object=this;
        wall1Body->SetUserData(&wall1data);
        Wall1=Shape::Rectangle(0, 0, 10, 600, Color(0,0,210));
        Wall1.SetCenter(5,300);
        Wall1.SetPosition(5,300);
    //wall 2
        b2BodyDef wall2BodyDef;
        wall2BodyDef.position.Set(795.0f, 300.0f);
        wall2Body = world->CreateBody(&wall2BodyDef);
        b2PolygonDef wall2ShapeDef;
        wall2ShapeDef.SetAsBox(5.0f, 300.0f);
        wall2Body->CreateShape(&wall2ShapeDef);
        wall2data.label="wall2";
        wall2data.object=this;
        wall2Body->SetUserData(&wall2data);
        Wall2=Shape::Rectangle(0, 0, 10, 600, Color(0,0,210));
        Wall2.SetCenter(5,300);
        Wall2.SetPosition(795,300);
    //roof
        b2BodyDef roofBodyDef;
        roofBodyDef.position.Set(400.0f, 5.0f);
        roofBody = world->CreateBody(&roofBodyDef);
        b2PolygonDef roofShapeDef;
        roofShapeDef.SetAsBox(400.0f, 5.0f);
        roofBody->CreateShape(&roofShapeDef);
        roofdata.label="roof";
        roofdata.object=this;
        roofBody->SetUserData(&roofdata);
        Roof=Shape::Rectangle(0, 0, 800, 10, Color(0,0,210));
        Roof.SetCenter(400,5);
        Roof.SetPosition(400,5);

        MySnail=new Snail(Window, world, TOH, 600, 150);
        OtherSnail=new Snail(Window, world, TOH, 200, 150);
        OtherSnail->controlled=false;
        OtherSnail->RifleGun->MouseTargeting=false;
	}

	void Game::Show(){
        Window->Draw(Ground);
        Window->Draw(Wall1);
        Window->Draw(Wall2);
        Window->Draw(Roof);
        TOH->ShowBullets();
        OtherSnail->Show();
        MySnail->Show();
        TOH->ShowGrenades();
    }

	void Game::GameLoop(){
	    while(InGame){
            Logic->CL.m_pointCount = 0;
            MySnail->jump=false;
            world->Step(timeStep, iterations);
            Logic->LogicListener();

            Event ev;
            while (Window->GetEvent(ev)){
                if (ev.Type == Event::Closed){
                    InGame=false;
                    Window->Close();
                }

                if (ev.Type == Event::KeyPressed){
                    if (ev.Key.Code == Key::Escape){
                        InGame=false;
                        //Window->Close();
                    }
                }
            }
            MySnail->InputHandling(ev);
            OtherSnail->InputHandling(ev);
            TOH->InputHandling(ev);

            Window->Clear();
            Show();
            Window->Display();
        }

	}
