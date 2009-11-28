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
    //ground
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(400.0f, 595.0f);
        groundBody = world->CreateBody(&groundBodyDef);
        b2PolygonDef groundShapeDef;
        groundShapeDef.SetAsBox(400.0f, 5.0f);
        groundBody->CreateShape(&groundShapeDef); // Add the ground shape to the ground body.
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
        Roof=Shape::Rectangle(0, 0, 800, 10, Color(0,0,210));
        Roof.SetCenter(400,5);
        Roof.SetPosition(400,5);

        MySnail=new Snail(Window, world, 400, 100);
	}

	void Game::Show(){
        Window->Draw(Ground);
        Window->Draw(Wall1);
        Window->Draw(Wall2);
        Window->Draw(Roof);
    }

	void Game::GameLoop(){
	    while(InGame){
            world->Step(timeStep, iterations);

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

            Window->Clear();
            Show();
            MySnail->Show();
            Window->Display();
        }

	}
