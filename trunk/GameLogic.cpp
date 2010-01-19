#include "GameLogic.hpp"

	GameLogic::GameLogic(RenderWindow* window, b2World* World){
	    Window=window;
	    world=World;

	    world->SetContactListener(&CL);
	}

	void GameLogic::LogicListener(){
	    vector<b2Body* > nuke;
	    vector<b2Shape* > nuke2;
        //cout<<CL.m_pointCount<<endl;
        bool once=false;
        bool once2=false;
        bool once3=false;
        bool once4=false;
        bool once5=false;
        for (int32 i = 0; i < CL.m_pointCount; ++i){

			ContactPoint* point = CL.m_points + i;

			b2Body* body1 = point->shape1->GetBody();
			b2Body* body2 = point->shape2->GetBody();

            data1=(data*) body1->GetUserData();
            data2=(data*) body2->GetUserData();

            if((data1->label=="snail"||data2->label=="snail")&&(data1->label!="bullet"&&data2->label!="bullet")&&(data1->label!="eye1"&&data2->label!="eye1")&&(data1->label!="eye2"&&data2->label!="eye2")){
            //if((data1->label=="snail"/* && data2->label=="GROUND"*/)||(/*data1->label=="GROUND" &&*/ data2->label=="snail")){
                if(data1->label=="snail"/* && data2->label=="GROUND"*/){
                    Snail* snail=(Snail*) data1->object;
                    if(!snail->hid&&snail->alive){
                        b2Shape* sh=body1->GetShapeList();
                        sh=sh->GetNext()->GetNext()->GetNext();
                        if(point->shape1->GetType()==snail->bodyshapeDef.type){
                            snail->jump=true;
                        }
                    }
                }
                if(/*data1->label=="GROUND" &&*/ data2->label=="snail"){
                    Snail* snail=(Snail*) data2->object;
                    if(!snail->hid&&snail->alive){
                        b2Shape* sh=body2->GetShapeList();
                        sh=sh->GetNext()->GetNext()->GetNext();
                        if(point->shape2->GetType()==snail->bodyshapeDef.type){
                            snail->jump=true;
                        }
                    }
                }
            }

            if(data1->label=="snail" && data2->label=="bullet" && !once){
                if(body2->GetLinearVelocity().x>100 || body2->GetLinearVelocity().x<-100 || body2->GetLinearVelocity().y>100 || body2->GetLinearVelocity().y<-100){
                    //cout<<"hurt"<<endl;
                    nuke.push_back(body2);
                    Snail* snail=(Snail*) data1->object;
                    Bullet* bullet=(Bullet*) data2->object;
                    snail->Damage(bullet->GetDamage());
                    float vx=body2->GetLinearVelocity().x;
                    float vy=body2->GetLinearVelocity().y;
                    body1->SetLinearVelocity(b2Vec2(body1->GetLinearVelocity().x+vx/10,body1->GetLinearVelocity().y+vy/10));
                    //snail->snailbody->SetLinearVelocity(b2Vec2(snail->snailbody->GetLinearVelocity().x+vx/10,snail->snailbody->GetLinearVelocity().y+vy/10));
                }
                once=true;
            }
            if(data1->label=="bullet" && data2->label=="snail" && !once){
                if(body1->GetLinearVelocity().x>100 || body1->GetLinearVelocity().x<-100 || body1->GetLinearVelocity().y>100 || body1->GetLinearVelocity().y<-100){
                    //cout<<"hurt"<<endl;
                    nuke.push_back(body1);
                    Snail* snail=(Snail*) data2->object;
                    Bullet* bullet=(Bullet*) data1->object;
                    snail->Damage(bullet->GetDamage());
                    float vx=body1->GetLinearVelocity().x;
                    float vy=body1->GetLinearVelocity().y;
                    body2->SetLinearVelocity(b2Vec2(body2->GetLinearVelocity().x+vx/10,body2->GetLinearVelocity().y+vy/10));
                }
                once=true;
            }

            if(data1->label=="grenade" && data2->label=="bullet" && !once2){
                nuke.push_back(body2);
                Grenade* grenade=(Grenade*) data1->object;
                grenade->timer=6;
                once2=true;
            }
            if(data1->label=="bullet" && data2->label=="grenade" && !once2){
                nuke.push_back(body1);
                Grenade* grenade=(Grenade*) data2->object;
                grenade->timer=6;
                once2=true;
            }

            if((data1->label=="rocket" || data2->label=="rocket") && !once3 && (data1->label!="weapon"&&data2->label!="weapon")){
                if(data1->label=="rocket" && !once3){
                    nuke.push_back(body1);
                    //Rocket* rocket=(Rocket*) data1->object;
                    once3=true;
                }
                if(data2->label=="rocket" && !once3){
                    nuke.push_back(body2);
                    //Rocket* rocket=(Rocket*) data2->object;
                    once3=true;
                }
            }

            int bullpow=100;
            if(data1->label=="Dbody" && data2->label=="bullet" && !once4){
                DestroyableBody* db=(DestroyableBody*) data1->object;
                if(db->isstatic)bullpow=5;
                if(body2->GetLinearVelocity().x>bullpow || body2->GetLinearVelocity().x<-bullpow || body2->GetLinearVelocity().y>bullpow || body2->GetLinearVelocity().y<-bullpow){
                    nuke.push_back(body2);
                    nuke2.push_back(point->shape1);
                    once4=true;
                }
            }
            bullpow=100;
            if(data1->label=="bullet" && data2->label=="Dbody" && !once4){
                DestroyableBody* db=(DestroyableBody*) data1->object;
                if(db->isstatic)bullpow=5;
                if(body1->GetLinearVelocity().x>bullpow || body1->GetLinearVelocity().x<-bullpow || body1->GetLinearVelocity().y>bullpow || body1->GetLinearVelocity().y<-bullpow){
                    nuke.push_back(body1);
                    nuke2.push_back(point->shape2);
                    once4=true;
                }
            }

            if(data1->label=="package" && data2->label=="snail" && !once5){
                Snail* snail=(Snail*) data2->object;
                Package* pack=(Package*) data1->object;
                if(pack->subcaste=="health"){
                    if(snail->Health<100){
                        nuke.push_back(body1);
                        HealthPackage* Hpack=(HealthPackage*) data1->object;
                        snail->Heal(Hpack->addHeal);
                    }
                }
                if(pack->subcaste=="grenade"){
                        nuke.push_back(body1);
                        GrenadePackage* Gpack=(GrenadePackage*) data1->object;
                        snail->grenades+=Gpack->addGrenade;
                }
                if(pack->subcaste=="rocket"){
                        nuke.push_back(body1);
                        RocketPackage* Rpack=(RocketPackage*) data1->object;
                        snail->Weapons[3]->AddAmmo(Rpack->addRocket);
                        snail->Surface->SetAmmo(snail->Weapons[snail->aktWeapon]->ammunition);
                }
                once5=true;
            }
            if(data1->label=="snail" && data2->label=="package" && !once5){
                Snail* snail=(Snail*) data1->object;
                Package* pack=(Package*) data2->object;
                if(pack->subcaste=="health"){
                    if(snail->Health<100){
                        nuke.push_back(body2);
                        HealthPackage* Hpack=(HealthPackage*) data2->object;
                        snail->Heal(Hpack->addHeal);
                    }
                }
                if(pack->subcaste=="grenade"){
                        nuke.push_back(body2);
                        GrenadePackage* Gpack=(GrenadePackage*) data2->object;
                        snail->grenades+=Gpack->addGrenade;
                }
                if(pack->subcaste=="rocket"){
                        nuke.push_back(body2);
                        RocketPackage* Rpack=(RocketPackage*) data1->object;
                        snail->Weapons[3]->AddAmmo(Rpack->addRocket);
                        snail->Surface->SetAmmo(snail->Weapons[snail->aktWeapon]->ammunition);
                }
                once5=true;
            }

/*
            if((data1->label=="snail" && data2->label=="wall1")||(data1->label=="wall1" && data2->label=="snail")){
                if(data1->label=="snail" && data2->label=="wall1"){
                    Snail* snail=(Snail*) data1->object;
                    snail->left=false;
                    cout<<data1->label<<" "<<data2->label<<endl;
                }
                if(data1->label=="wall1" && data2->label=="snail"){
                    Snail* snail=(Snail*) data2->object;
                    snail->left=false;
                    cout<<data1->label<<" "<<data2->label<<endl;
                }
            }
            if((data1->label=="snail" && data2->label=="wall2")||(data1->label=="wall2" && data2->label=="snail")){
                if(data1->label=="snail" && data2->label=="wall2"){
                    Snail* snail=(Snail*) data1->object;
                    snail->right=false;
                    cout<<data1->label<<" "<<data2->label<<endl;
                }
                if(data1->label=="wall2" && data2->label=="snai"){
                    Snail* snail=(Snail*) data2->object;
                    snail->right=false;
                    cout<<data1->label<<" "<<data2->label<<endl;
                }
            }
*/
            //cout<<data1->label<<" "<<data2->label<<endl;
		}

		for(unsigned int i=0;i<nuke.size();i++){
		    data* d=(data*) nuke[i]->GetUserData();
		    if(d->label=="rocket"){
		        Rocket* r=(Rocket*) d->object;
		        r->DestroyRocket();
            }
            if(d->label=="package"){
                Package* p=(Package*) d->object;
                p->DestroyPackage();
            }
            if(d->label=="bullet"){
                Bullet* b=(Bullet*) d->object;
                b->DestroyBullet();
            }
        }

        for(unsigned int i=0;i<nuke2.size();i++){
		    b2Body* b=nuke2[i]->GetBody();
		    data* dat=(data*) b->GetUserData();
		    DestroyableBody* db=(DestroyableBody*) dat->object;
		    db->EliminateShape(nuke2[i]);
        }
    }
