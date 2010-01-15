#include "Rocket.hpp"
#include "Snail.hpp"
#include "DestroyableBody.hpp"

	Rocket::Rocket(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, float VelocityX, float VelocityY, int Damage){
	    Window=window;
	    world=World;
	    TOH=toh;
	    damage=Damage;
	    exploding=false;
	    lim=false;

	    nullPositionX=PositionX;
        nullPositionY=PositionY;

        rocketbodyDef.position.Set(PositionX, PositionY);
        rocketbody = world->CreateBody(&rocketbodyDef);
        rocketbodyDef.isBullet = true;
        rocketbodyDef.allowSleep = false;
        rocketshapeDef.density = 20.0f;
        rocketshapeDef.radius = 6.0f;
        rocketshapeDef.restitution = 0.05f;
        rocketbody->CreateShape(&rocketshapeDef);
        rocketbody->SetMassFromShapes();
        rocketdata.label="rocket";
        rocketdata.object=this;
        rocketbody->SetUserData(&rocketdata);
        rocketbody->SetLinearVelocity(b2Vec2(VelocityX, VelocityY));

        /*debugDrawShape=Shape::Circle(0,0,rocketshapeDef.radius,Color(200,0,0));
        debugDrawShape.SetPosition(rocketbody->GetPosition().x,rocketbody->GetPosition().y);*/

        RocketSp.SetImage(TOH->rocketImg);
        //RocketSp.SetScale(0.6,0.6);
        RocketSp.SetPosition(PositionX, PositionY);
        RocketSp.SetCenter(53,9);
        //RocketSp.SetCenter(rocketbody->GetLocalCenter().x+17,rocketbody->GetLocalCenter().y+28);

        iter=0;
        iter2=0;

        Explode.SetBuffer(TOH->GranadeSoundBuffer);
        Flight.SetBuffer(TOH->RocketFlightSoundBuffer);
        Flight.Play();
        Flight.SetLoop(true);
	}

	void Rocket::Show(){
        Window->Draw(RocketSp);
        //Window->Draw(debugDrawShape);
    }

    void Rocket::ApplyForces(){
        b2Body* body=world->GetBodyList();
        for(int i=0;i<world->GetBodyCount();i++){
            data* d=(data*) body->GetUserData();
            if(d->label=="GROUND"||d->label=="wall1"||d->label=="wall2"||d->label=="roof"||d->label=="stage"){
                continue;
            }else{
                float Vx=body->GetPosition().x-rocketbody->GetPosition().x;
                float Vy=body->GetPosition().y-rocketbody->GetPosition().y;
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

	void Rocket::InputHandling(){
        if(exploding){
            if(!lim){
                Explode.Play();
                Flight.Stop();
                lim=true;
                ApplyForces();
            }
            if(iter>2){
                world->DestroyBody(rocketbody);
                TOH->Remove(this);
            }else{
                if(iter2>2){
                    Sprite sp;
                    sp.SetImage(TOH->detonation[iter]);
                    RocketSp=sp;
                    RocketSp.SetScale(1+(0.5*iter),1+(0.5*iter));
                    RocketSp.SetCenter(60,65);
                    iter++;
                    iter2=0;
                }else{
                    iter2++;
                }
            }
        }
        RocketSp.SetPosition(rocketbody->GetPosition().x,rocketbody->GetPosition().y);
        if(!exploding){
            float rotation=0;
            rotation=atan((rocketbody->GetLinearVelocity().y)/(rocketbody->GetLinearVelocity().x))*-57.29577951308232;
            if(rocketbody->GetLinearVelocity().x<0&&rocketbody->GetLinearVelocity().y<0){
                rotation+=180;
            }
            if(rocketbody->GetLinearVelocity().x<0&&rocketbody->GetLinearVelocity().y>0){
                rotation-=180;
            }
            RocketSp.SetRotation(rotation);
        }
        //cout<<(rocketbody->GetPosition().x-nullPositionX)/200<<" "<<(rocketbody->GetPosition().y-nullPositionY)/200<<endl;
        Flight.SetPosition((rocketbody->GetPosition().x-nullPositionX)/500,(rocketbody->GetPosition().y-nullPositionY)/500,0);
        //debugDrawShape.SetPosition(rocketbody->GetPosition().x,rocketbody->GetPosition().y);

        //cout<<rocketbody->GetLinearVelocity().x<<" "<<rocketbody->GetLinearVelocity().y<<endl;
        /*if(rocketbody->GetLinearVelocity().x>-2 && rocketbody->GetLinearVelocity().x<2 && rocketbody->GetLinearVelocity().y>-2 && rocketbody->GetLinearVelocity().y<2){
            DestroyRocket();
        }*/
	}

    void Rocket::DestroyRocket(){
        exploding=true;
    }

    void Rocket::SetNumber(int num){
        number=num;
    }

    int Rocket::GetNumber(){
        return number;
    }

    int Rocket::GetDamage(){
        return damage;
    }
