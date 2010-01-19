#include "Game.hpp"

  Game::Game(RenderWindow* window, int i, string iP) {
    ip = iP;
    p = &ip;

    Window=window;
    InGame=false;
    pPoo = new Pool();

    TOH=new TempObjectHandler();    // Módosítva CseAn által 2010 01 15
    GameStage=new Stage2();          // Módosítva CseAn által 2010 01 15

    Width=GameStage->Width();   // Módosítva CseAn által 2010 01 15
    Height=GameStage->Height(); // Módosítva CseAn által 2010 01 15


    b2AABB worldAABB; // Define the size of the world. Simulation will still work if bodies reach the end of the world, but it will be slower.
    worldAABB.lowerBound.Set(-100.0f, -100.0f);
    worldAABB.upperBound.Set(Width+100, Height+100);  // Módosítva CseAn által 2010 01 15

    b2Vec2 gravity(0.0f, 10.0f); // Define the gravity vector.

    bool doSleep = false; // Do we want to let bodies sleep?
    world=new b2World(worldAABB, gravity, doSleep);

    timeStep = 1.0f / 10.0f;
    iterations = 10;
	Logic=new GameLogic(Window,world);
	 GameStage->MakeStage(Window, world, TOH);   // Módosítva CseAn által 2010 01 15
    //TOH=new TempObjectHandler();

    //GameStage=new Stage(Window, world, TOH);
    Surface=new GameSurface(window);

    if (i==0) {
        MySnail=new Snail(Window, world, TOH, Surface, 2000, 150, true, pPoo, false);

    }
    if (i ==1) {
        Thread* ThreadCreateServer = new Thread(&ThreadCreateServerFunc);
        ThreadCreateServer->Launch();
        MySnail=new Snail(Window, world, TOH, Surface, 3400, 1200, true, pPoo, false);
        OtherSnail=new Snail(Window, world, TOH, Surface, 900, 1650, false, pPoo, true);

    }
    if (i==2) {
       Thread* ThreadCreateClient = new Thread(&ThreadCreateClientFunc, p);
       ThreadCreateClient->Launch();

       MySnail=new Snail(Window, world, TOH, Surface, 900, 1650, true, pPoo, false);
       OtherSnail=new Snail(Window, world, TOH, Surface, 3400, 1200, false, pPoo, true);

    }


    GameView.SetCenter(MySnail->snailbody->GetPosition().x,MySnail->snailbody->GetPosition().y);
    GameView.SetHalfSize(400, 300);
}

void Game::ThreadCreateServerFunc(void* UserData) {
    cout<<"\nIN MENU: Create Server\n";
    NetworkInterface p;
    mSocket = p.RunAsServer();
    pPoo->start();
    GameEvent* ev = new GameEvent("Beta");
    pPoo->AddMess(ev);
}


void Game::ThreadCreateClientFunc(void* UserData) {
    string* Object = static_cast<string*>(UserData);
    string s = *Object;
    NetworkInterface p;
    mSocket = p.RunAsClient(s);
    pPoo->start();
    GameEvent* ev = new GameEvent("Beta");
    pPoo->AddMess2(ev);
}


void Game::Show() {
        GameStage->Show();
        TOH->ShowDBodyes();
        TOH->ShowBullets();
        TOH->ShowRockets();
        TOH->ShowPackages();
        OtherSnail->Show();
        MySnail->Show();
        TOH->ShowGrenades();
        TOH->ShowRocketsDetonation();

        GameStage->ShowAfter();
        Surface->Show();
}

void Game::GameLoop() {
    while (InGame) {

        Logic->CL.m_pointCount = 0;
        MySnail->jump=false;
        world->Step(timeStep, iterations);
        Logic->LogicListener();
        GameStage->InputHandling();

        GameEvent* ge;

        ge = pPoo->GetMess();
        if(ge->EventToString().at(0)=='1'){
           TargetPointChangeEvent* tpche = (TargetPointChangeEvent*) ge;
           OtherSnail->SetTargetPoint(tpche->getXPos(),tpche->getYPos());
        }
        if(ge->EventToString().at(0)=='2'){
            cout<<"CSIGA MOZOG Balra";
            OtherSnail->MoveLeft();
        }
        if(ge->EventToString().at(0)=='3'){
            cout<<"CSIGA MOZOG Jobbra";
            OtherSnail->MoveRight();
        }
        if(ge->EventToString().at(0)=='4'){
            cout<<"CSIGA UGRIK";
            OtherSnail->MoveUp();
        }
        if(ge->EventToString().at(0)=='5'){
            cout<<"CSIGA TAPAD";
            OtherSnail->MoveDown();
        }
        if(ge->EventToString().at(0)=='7'){
            OtherSnail->RollLeft();
        }
        if(ge->EventToString().at(0)=='8'){
            OtherSnail->RollRight();
        }
        if(ge->EventToString().at(0)=='9'){
            OtherSnail->ThrowGrenade();
        }
        if(ge->EventToString()=="#ShotEvent"){
            OtherSnail->Shot();
        }

        Event ev;
        while (Window->GetEvent(ev)) {
            MySnail->EventHandling(ev);
            if (ev.Type == Event::Closed) {
                InGame=false;
                Window->Close();
            }

            if (ev.Type == Event::KeyPressed) {
                if (ev.Key.Code == Key::Escape) {
                    InGame=false;
                }
            }
        }
        MySnail->InputHandling();
        OtherSnail->InputHandling();
        TOH->InputHandling();

        float viewx=MySnail->snailbody->GetPosition().x-(400-Window->GetInput().GetMouseX());
        float viewy=MySnail->snailbody->GetPosition().y-(300-Window->GetInput().GetMouseY());
        if (viewx<400) viewx=400;
        if(viewy<300) viewy=300;                    // Módosítva CseAn által 2010 01 15
        if(viewx>Width-400) viewx=Width-400;        // Módosítva CseAn által 2010 01 15
        if(viewy>Height-300) viewy=Height-300;      // Módosítva CseAn által 2010 01 15
        GameView.SetCenter(viewx,viewy);

        Window->SetView(GameView);
        Window->Clear();
        Show();
        Window->Display();
    }
    Window->SetView(Window->GetDefaultView());
}
