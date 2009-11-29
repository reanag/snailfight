#include "Grenade.hpp"

	Grenade::Grenade(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, float VelocityX, float VelocityY){
	    Window=window;
	    world=World;
	    TOH=toh;
	    timer=0;
	    lim=false;

        grenadebodyDef.position.Set(PositionX, PositionY);
        grenadebody = world->CreateBody(&grenadebodyDef);

        grenadeshapeDef.density = 20.0f;
        grenadeshapeDef.radius = 10.0f;
        grenadeshapeDef.restitution = 0.05f;
        grenadebody->CreateShape(&grenadeshapeDef);
        grenadebody->SetMassFromShapes();
        grenadedata.label="grenade";
        grenadedata.object=this;
        grenadebody->SetUserData(&grenadedata);
        grenadebody->SetLinearVelocity(b2Vec2(VelocityX, VelocityY));

	    //grenadeImg.LoadFromFile("contents/Granade1.png");
        GrenadeSp.SetImage(TOH->grenadeImg);
        GrenadeSp.SetScale(0.6,0.6);
        GrenadeSp.SetPosition(PositionX, PositionY);
        GrenadeSp.SetCenter(grenadebody->GetLocalCenter().x+17,grenadebody->GetLocalCenter().y+28);
        //detonation[0].LoadFromFile("contents/det1.png");
        //detonation[1].LoadFromFile("contents/det2.png");
        //detonation[2].LoadFromFile("contents/det3.png");
        iter=0;
        iter2=0;
        //Buffer.LoadFromFile("contents/Grenade3.wav");
        Explode.SetBuffer(TOH->GranadeSoundBuffer);
        Explode.SetVolume(100);
	}

	void Grenade::Show(){
            Window->Draw(GrenadeSp);
    }

	void Grenade::InputHandling(Event ev){
        timer+=Window->GetFrameTime();
        if(timer>5){
            if(!lim){
                Explode.Play();
                lim=true;
            }
            if(iter>2){
                DestroyGrenade();
            }else{
                if(iter2>2){
                    Sprite sp;
                    sp.SetImage(TOH->detonation[iter]);
                    GrenadeSp=sp;
                    GrenadeSp.SetScale(2,2);
                    GrenadeSp.SetCenter(60,65);
                    iter++;
                    iter2=0;
                }else{
                    iter2++;
                }
            }
        }

        GrenadeSp.SetPosition(grenadebody->GetPosition().x,grenadebody->GetPosition().y);
        GrenadeSp.SetRotation(grenadebody->GetAngle()*-57.29577951308232);
	}

    void Grenade::DestroyGrenade(){
        world->DestroyBody(grenadebody);
        TOH->Remove(this);
    }

    void Grenade::SetNumber(int num){
        number=num;
    }

    int Grenade::GetNumber(){
        return number;
    }
