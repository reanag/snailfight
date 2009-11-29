#include "GameLogic.hpp"

	GameLogic::GameLogic(RenderWindow* window, b2World* World){
	    Window=window;
	    world=World;

	    world->SetContactListener(&CL);
	}

	void GameLogic::LogicListener(){
	    vector<b2Body* > nuke;
        //cout<<CL.m_pointCount<<endl;
        bool once=false;
        for (int32 i = 0; i < CL.m_pointCount; ++i)
		{
			ContactPoint* point = CL.m_points + i;

			b2Body* body1 = point->shape1->GetBody();
			b2Body* body2 = point->shape2->GetBody();

            data1=(data*) body1->GetUserData();
            data2=(data*) body2->GetUserData();

            if((data1->label=="snail" && data2->label=="GROUND")||(data1->label=="GROUND" && data2->label=="snail")){
                if(data1->label=="snail" && data2->label=="GROUND"){
                    Snail* snail=(Snail*) data1->object;
                    //snail->out();
                    b2Shape* sh=body1->GetShapeList();
                    sh=sh->GetNext()->GetNext()->GetNext();
                    if(point->shape1==sh){
                        snail->jump=true;
                    }
                }
                if(data1->label=="GROUND" && data2->label=="snail"){
                    Snail* snail=(Snail*) data2->object;
                    //snail->out();
                    b2Shape* sh=body2->GetShapeList();
                    sh=sh->GetNext()->GetNext()->GetNext();
                    if(point->shape2==sh){
                        snail->jump=true;
                    }
                }
            }

            if(data1->label=="snail" && data2->label=="bullet" && !once){
                if(body2->GetLinearVelocity().x>100 || body2->GetLinearVelocity().x<-100 || body2->GetLinearVelocity().y>100 || body2->GetLinearVelocity().y<-100){
                    cout<<"hurt"<<endl;
                    nuke.push_back(body2);
                }
                once=true;
            }
            if(data1->label=="bullet" && data2->label=="snail" && !once){
                if(body1->GetLinearVelocity().x>100 || body1->GetLinearVelocity().x<-100 || body1->GetLinearVelocity().y>100 || body1->GetLinearVelocity().y<-100){
                    cout<<"hurt"<<endl;
                    nuke.push_back(body1);
                }
                once=true;
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

		for(int i=0;i<nuke.size();i++){
		    data* d=(data*) nuke[i]->GetUserData();
		    Bullet* b=(Bullet*) d->object;
		    b->DestroyBullet();
        }
    }
