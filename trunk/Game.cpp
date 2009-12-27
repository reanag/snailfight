#include "Game.hpp"

	Game::Game(RenderWindow* window){
	    Window=window;
	    InGame=false;

	    b2AABB worldAABB; // Define the size of the world. Simulation will still work if bodies reach the end of the world, but it will be slower.
        worldAABB.lowerBound.Set(-100.0f, -100.0f);
        worldAABB.upperBound.Set(2500.0f, 1900.0f);

        b2Vec2 gravity(0.0f, 10.0f); // Define the gravity vector.

        bool doSleep = false; // Do we want to let bodies sleep?
        world=new b2World(worldAABB, gravity, doSleep);

        timeStep = 1.0f / 10.0f;
        iterations = 10;

        Logic=new GameLogic(Window,world);
        TOH=new TempObjectHandler();

        GameStage=new Stage(Window, world, TOH);

        MySnail=new Snail(Window, world, TOH, 600, 150);
        OtherSnail=new Snail(Window, world, TOH, 200, 150);
        OtherSnail->controlled=false;
        OtherSnail->Weapons[OtherSnail->aktWeapon]->MouseTargeting=false;

        GameView.SetCenter(MySnail->snailbody->GetPosition().x,MySnail->snailbody->GetPosition().y);
        GameView.SetHalfSize(400, 300);
	}

	void Game::Show(){
	    GameStage->Show();

        TOH->ShowBullets();
        OtherSnail->Show();
        MySnail->Show();
        TOH->ShowGrenades();

        GameStage->ShowAfter();
    }

	void Game::GameLoop(){
	    while(InGame){
            Logic->CL.m_pointCount = 0;
            MySnail->jump=false;
            world->Step(timeStep, iterations);
            Logic->LogicListener();

            Event ev;
            while (Window->GetEvent(ev)){
                MySnail->EventHandling(ev);
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

            float viewx=MySnail->snailbody->GetPosition().x-(400-Window->GetInput().GetMouseX());
            float viewy=MySnail->snailbody->GetPosition().y-(300-Window->GetInput().GetMouseY());
            if(viewx<400) viewx=400;
            if(viewx>2000) viewx=2000;
            if(viewy>1495) viewy=1495;
            GameView.SetCenter(viewx,viewy);

            Window->SetView(GameView);
            Window->Clear();
            Show();
            Window->Display();
        }
        Window->SetView(Window->GetDefaultView());
	}
