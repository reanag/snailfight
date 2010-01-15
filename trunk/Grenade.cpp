#include "Grenade.hpp"
#include "Snail.hpp"

	Grenade::Grenade(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, float VelocityX, float VelocityY){
	    Window=window;
	    world=World;
	    TOH=toh;

	    damage=15;
	    timer=0;
	    lim=false;
	    exploding=false;

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
        Throw.SetBuffer(TOH->GranadeThrowSoundBuffer);
        Throw.Play();
	}

	void Grenade::Show(){
            Window->Draw(GrenadeSp);
    }

    void Grenade::ApplyForces(){
        b2Body* body=world->GetBodyList();
        for(int i=0;i<world->GetBodyCount();i++){
            data* d=(data*) body->GetUserData();
            if(d->label=="GROUND"||d->label=="wall1"||d->label=="wall2"||d->label=="roof"||d->label=="stage"){
                continue;
            }else{
                float Vx=body->GetPosition().x-grenadebody->GetPosition().x;
                float Vy=body->GetPosition().y-grenadebody->GetPosition().y;
                float dist=sqrt(pow(Vx,2)+pow(Vy,2));
                if(dist<200&&Vx!=0&&Vy!=0){
                    Vx=Vx*100/dist;
                    Vy=Vy*100/dist;
                    if(d->label=="snail"){
                        Snail* snail=(Snail*) d->object;
                        snail->Damage(damage);
                    }
                    if(d->label=="Dbody"){
                        DestroyableBody* db=(DestroyableBody*) d->object;
                        if(!db->isstatic){
                            body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x+Vx,body->GetLinearVelocity().y+Vy));
                        }
                    }else{
                        body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x+Vx,body->GetLinearVelocity().y+Vy));
                    }
                }
            }
            body=body->GetNext();
        }
    }

	void Grenade::InputHandling(){
        timer+=Window->GetFrameTime();
        if(timer>5){
            exploding=true;
            if(!lim){
                Explode.Play();
                lim=true;
                ApplyForces();
            }
            if(iter>2){
                DestroyGrenade();
            }else{
                if(iter2>2){
                    Sprite sp;
                    sp.SetImage(TOH->detonation[iter]);
                    GrenadeSp=sp;
                    GrenadeSp.SetScale(1+(0.5*iter),1+(0.5*iter));
                    GrenadeSp.SetCenter(60,65);
                    iter++;
                    iter2=0;
                }else{
                    iter2++;
                }
            }
        }
        GrenadeSp.SetPosition(grenadebody->GetPosition().x,grenadebody->GetPosition().y);
        if(!exploding)GrenadeSp.SetRotation(grenadebody->GetAngle()*-57.29577951308232);
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
