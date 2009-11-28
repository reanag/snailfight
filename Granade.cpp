#include "Granade.hpp"

	Granade::Granade(RenderWindow* window, b2World* World, float PositionX, float PositionY, float VelocityX, float VelocityY){
	    Window=window;
	    world=World;
	    timer=Window->GetFrameTime();
	    active=true;

        granadebodyDef.position.Set(PositionX, PositionY);
        granadebody = world->CreateBody(&granadebodyDef);

        granadeshapeDef.density = 20.0f;
        granadeshapeDef.radius = 10.0f;
        granadeshapeDef.restitution = 0.05f;
        granadebody->CreateShape(&granadeshapeDef);
        granadebody->SetMassFromShapes();
        granadebody->SetLinearVelocity(b2Vec2(VelocityX, VelocityY));

        Body=Shape::Circle(0,0,granadeshapeDef.radius,Color(255,0,0));
        Body.SetPosition(granadebody->GetPosition().x,granadebody->GetPosition().y);

	    granadeImg.LoadFromFile("Granade1.png");
        GranadeSp.SetImage(granadeImg);
        GranadeSp.SetScale(0.6,0.6);
        GranadeSp.SetPosition(PositionX, PositionY);
        GranadeSp.SetCenter(granadebody->GetLocalCenter().x+17,granadebody->GetLocalCenter().y+28);
	}

	Granade::~Granade(){
        world->DestroyBody(granadebody);
    }

	void Granade::Show(){
	    if(active){
            Window->Draw(GranadeSp);
            //Window->Draw(Body);
	    }
    }

	void Granade::InputHandling(Event ev){
	    if(active){
            timer+=Window->GetFrameTime();
            GranadeSp.SetPosition(granadebody->GetPosition().x,granadebody->GetPosition().y);
            GranadeSp.SetRotation(granadebody->GetAngle()*-57.29577951308232);
            Body.SetPosition(granadebody->GetPosition().x,granadebody->GetPosition().y);
            if(timer>5){
                Deactivate();
            }
	    }
	}

	void Granade::Deactivate(){
        world->DestroyBody(granadebody);
        active=false;
    }
