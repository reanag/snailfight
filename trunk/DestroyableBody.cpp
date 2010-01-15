#include "DestroyableBody.hpp"

	DestroyableBody::DestroyableBody(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, float Angle, bool IsStatic){
	    Window=window;
	    world=World;
	    TOH=toh;

	    //ok=true;
	    deleteable=false;
	    breaking=false;
	    isstatic=IsStatic;

        destroyablebodyDef.position.Set(PositionX, PositionY);
        destroyablebodyDef.angle=Angle/-57.29577951308232;
        destroyablebody = world->CreateBody(&destroyablebodyDef);

        Ilimit=3;
        Jlimit=20;

        for(unsigned int j=0;j<Jlimit;j++){
            for(unsigned int i=0;i<Ilimit;i++){
                b2PolygonDef* dshapeDef=new b2PolygonDef();
                dshapeDef->SetAsBox(5,5,b2Vec2(5+(i*10),5+(j*10)),0);
                position* p=new position(dshapeDef->vertices[0].x, dshapeDef->vertices[0].y, dshapeDef);
                p->iterI=(j*Ilimit)+i;
                positions.push_back(p);
                if(i>0){
                    p->left=positions[p->iterI-1];
                    positions[p->iterI-1]->right=p;
                }
                if(j>0){
                    p->up=positions[p->iterI-Ilimit];
                    positions[p->iterI-Ilimit]->down=p;
                }
                dshapeDef->userData=p;
                if(!isstatic){
                    dshapeDef->density=30.0f;
                    dshapeDef->friction=0.5f;
                }
                p->shape=destroyablebody->CreateShape(dshapeDef);
            }
        }
        first=positions[0];
        positions.back()->suspended=true;

        /*for(int i=0;i<positions.size();i++){
            int jj=(int)positions[i]->iterI/Jlimit;
            int ii=positions[i]->iterI-(jj*Jlimit);
            cout<<"i,j,iter: "<<ii<<" "<<jj<<" "<<positions[i]->iterI<<endl;
        }*/

        /*iter=0;
        GetNext(positions[0][0]);
        cout<<iter<<endl;
        UnCheck();*/

        /*for(int j=0;j<20;j++){
            for(int i=0;i<3;i++){
                cout<<j<<","<<i<<": "<<positions[j][i]->positionX<<" "<<positions[j][i]->positionY<<endl;
            }
        }*/

        /*position* next=positions[0][0];
        while(next!=NULL){
            cout<<next->positionX<<" "<<next->positionY<<endl;
            if(next->GetRight()!=NULL){
                next=next->GetRight();
            }
        }*/

        destroyablebody->SetMassFromShapes();

        destroyablebodydata.label="Dbody";
        destroyablebodydata.object=this;
        destroyablebody->SetUserData(&destroyablebodydata);

        DBodyImg.LoadFromFile("contents/brick.png");
        DBodySp.SetImage(DBodyImg);
        DBodySp.SetCenter(5,5);
        DBodySp.SetPosition(PositionX, PositionY);
        DBodySp.SetRotation(destroyablebody->GetAngle()*-57.29577951308232);

        bulletholeImg1.LoadFromFile("contents/bullethole1.3.png");
	}

    DestroyableBody::DestroyableBody(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, float Angle, vector<position> NewPositions, Image image, int ilimit, int jlimit){
        Window=window;
	    world=World;
	    TOH=toh;

	    deleteable=false;
	    breaking=false;
        destroyablebodyDef.position.Set(PositionX, PositionY);
        destroyablebodyDef.angle=Angle;
        destroyablebody = world->CreateBody(&destroyablebodyDef);

        Ilimit=ilimit;
        Jlimit=jlimit;

        /*for(unsigned int i=0;i<NewPositions.size();i++){
            //if(NewPositions[i]->left)cout<<"left"<<endl;
            //if(NewPositions[i]->right)cout<<"right"<<endl;
            //if(NewPositions[i]->up)cout<<"up"<<endl;
            //if(NewPositions[i]->down)cout<<"down"<<endl;
            int jj=(int)NewPositions[i].iterI/Jlimit;
            int ii=NewPositions[i].iterI-(jj*Jlimit);
            cout<<"i,j,iter: "<<ii<<" "<<jj<<" "<<NewPositions[i].iterI<<endl;
        }*/
        //cout<<endl<<endl<<endl;

        for(int i=0;i<Ilimit*Jlimit;i++){
            positions.push_back(new position());
        }

        //for(unsigned int j=0;j<Jlimit;j++){
          //  for(unsigned int i=0;i<Ilimit;i++){
          for(unsigned int i=0;i<NewPositions.size();i++){
                b2PolygonDef* dshapeDef=new b2PolygonDef();
                dshapeDef->SetAsBox(5,5,b2Vec2(NewPositions[i].positionX+5,NewPositions[i].positionY+5),0);
                position* p=new position(dshapeDef->vertices[0].x, dshapeDef->vertices[0].y, dshapeDef);
                //positions.push_back(p);
                p->iterI=NewPositions[i].iterI;
                positions[p->iterI]=p;

                dshapeDef->userData=p;
                dshapeDef->density=30.0f;
                p->shape=destroyablebody->CreateShape(dshapeDef);
            }
        //}

            for(int i=0;i<positions.size();i++){
                int jj=(int)positions[i]->iterI/Ilimit;
                int ii=positions[i]->iterI-(jj*Ilimit);
                /*cout<<"i,j,iter: "<<ii<<" "<<jj<<" "<<positions[i]->iterI<<endl;
                cout<<"pos x,y : "<<positions[i]->positionX<<" "<<positions[i]->positionY<<endl;*/
                //cout<<"vertex x,y : "<<positions[i]->polygon->vertices[0].x<<" "<<positions[i]->polygon->vertices[0].y<<endl;

                if(positions[i]->iterI!=0 && positions[i]->polygon!=0){
                    if(ii>0){
                        if(positions[i-1]){
                            positions[i]->left=positions[i-1];
                            positions[i-1]->right=positions[i];
                        }
                    }
                    if(jj>0){
                        if(positions[i-Ilimit]){
                            positions[i]->up=positions[i-Ilimit];
                            positions[i-Ilimit]->down=positions[i];
                        }
                    }
                }
                if(positions[i]->polygon==0){
                    delete positions[i];
                    positions[i]=0;
                }
            }

            if(positions[0]==0){
                //positions.erase(positions.begin());
                int i=2;
                position* aktpos=positions[i];
                while(!aktpos){
                    aktpos=positions[i+1];
                    i++;
                }
                first=aktpos;
            }else{
                first=positions[0];
            }
            if(positions.back()==0){
                int i=positions.size()-2;
                position* aktpos=positions[i];
                while(!aktpos){
                    aktpos=positions[i-1];
                    i--;
                }
                aktpos->suspended=true;
            }else{
                positions.back()->suspended=true;
            }

            /*iter=0;
            GetNext(first);
            cout<<iter<<endl;
            UnCheck();*/


        /*for(unsigned int i=0;i<NewPositions.size();i++){
            if(NewPositions[i]->left)cout<<"left"<<endl;
            if(NewPositions[i]->right)cout<<"right"<<endl;
            if(NewPositions[i]->up)cout<<"up"<<endl;
            if(NewPositions[i]->down)cout<<"down"<<endl;
            int jj=(int)NewPositions[i]->iterI/Jlimit;
            int ii=NewPositions[i]->iterI-(jj*Jlimit);
            cout<<"i,j,iter: "<<ii<<" "<<jj<<" "<<NewPositions[i]->iterI<<endl;

            b2PolygonDef* dshapeDef=new b2PolygonDef();
            dshapeDef->SetAsBox(5,5,b2Vec2(NewPositions[i]->positionX+5,NewPositions[i]->positionY+5),0);
            position* p=new position(dshapeDef->vertices[0].x, dshapeDef->vertices[0].y, dshapeDef);
            p->iterI=NewPositions[i]->iterI;
            positions.push_back(p);

            dshapeDef->userData=p;
            dshapeDef->density=30.0f;
            positions[i]->shape=destroyablebody->CreateShape(dshapeDef);
        }*/

        /*first=positions[0];
        positions.back()->suspended=true;*/

        destroyablebody->SetMassFromShapes();

        destroyablebodydata.label="Dbody";
        destroyablebodydata.object=this;
        destroyablebody->SetUserData(&destroyablebodydata);

        DBodyImg=image;
        DBodyImg.CreateMaskFromColor(Color(0,0,0));
        DBodySp.SetImage(DBodyImg);
        DBodyImg.CreateMaskFromColor(Color(0,0,0));
        DBodySp.SetCenter(5,5);
        DBodySp.SetPosition(PositionX, PositionY);
        DBodySp.SetRotation(destroyablebody->GetAngle()*-57.29577951308232);

        bulletholeImg1.LoadFromFile("contents/bullethole1.3.png");
    }

    void DestroyableBody::Show(){
        //if(ok){
            Window->Draw(DBodySp);
        //}
    }


    void DestroyableBody::InputHandling(){
        //if(ok){
            DBodySp.SetPosition(destroyablebody->GetPosition().x,destroyablebody->GetPosition().y);
            DBodySp.SetRotation(destroyablebody->GetAngle()*-57.29577951308232);
            if(deleteable || destroyablebody->GetShapeList()==NULL){
                world->DestroyBody(destroyablebody);
                TOH->Remove(this);
               // ok=false;
            }
        //}
    }

    void DestroyableBody::GetNext(position* p){
        p->checked=true;
        if(p->left&&p->left->checked==false){GetNext(p->left);}
        if(p->right&&p->right->checked==false){GetNext(p->right);}
        if(p->up&&p->up->checked==false){GetNext(p->up);}
        if(p->down&&p->down->checked==false){GetNext(p->down);}
        iter++;
    }

    void DestroyableBody::GetRight(position* p){
        cout<<p->positionX<<" "<<p->positionY<<endl;
        if(p->right)GetRight(p->right);
        iter++;
    }

    void DestroyableBody::FindBottom(position* p){
        cout<<p->positionX<<" "<<p->positionY<<endl;
        bottom=p;
        if(p->down){
            FindBottom(p->down);
        }
    }

    void DestroyableBody::UnCheck(){
        /*for(int j=0;j<20;j++){
            for(int i=0;i<3;i++){
                if(positions[j][i]!=NULL||positions[j][i]!=0)positions[j][i]->checked=false;
            }
        }*/
        shapecount=0;
        for(int i=0;i<positions.size();i++){
            if(positions[i]!=NULL||positions[i]!=0){
                positions[i]->checked=false;
                shapecount++;
            }
        }
    }

    bool DestroyableBody::IsUnbroken(position* p){
        p->checked=true;
        bottom=p;
        if(p->suspended)return true;
        if(p->left&&p->left->checked==false){
            if(IsUnbroken(p->left))return true;
        }
        if(p->right&&p->right->checked==false){
            if(IsUnbroken(p->right))return true;
        }
        if(p->up&&p->up->checked==false){
            if(IsUnbroken(p->up))return true;
        }
        if(p->down&&p->down->checked==false){
            if(IsUnbroken(p->down))return true;
        }
        return false;
    }

    void DestroyableBody::EliminateShape(b2Shape* shape){
        position* pos=(position*) shape->GetUserData();
        DBodyImg.Copy(bulletholeImg1, pos->positionX, pos->positionY, IntRect(0, 0, 20, 20), true);
        DBodyImg.CreateMaskFromColor(Color(0,0,0));
        //delete pos;   //nem tom ez így fasza-e mert elvileg a mátrixban lévõ cucc is megszûnik létezni én UnCheck hívásánál ez gázos leheta
                      //egyenlõre úgy fest így is mûködik
        /*if(pos->left){
            pos->left->right=0;
            pos->left=0;
        }
        if(pos->right){
            pos->right->left=0;
            pos->right=0;
        }
        if(pos->up){
            pos->up->down=0;
            pos->up=0;
        }
        if(pos->down){
            pos->down->up=0;
            pos->down=0;
        }*/

        //iter=0;
        //GetNext(positions[0][0]);
        //cout<<iter<<endl;

        destroyablebody->DestroyShape(shape);
        int aktiter=pos->iterI;
        bool suspend=pos->suspended;

        if(first->suspended==false){
            if(pos==first){
                //positions.erase(positions.begin());
                int i=first->iterI+1;
                position* aktpos=positions[i];
                while(!aktpos){
                    aktpos=positions[i+1];
                    i++;
                }
                first=aktpos;
            }
            if(suspend){
                int i=pos->iterI-1;
                position* aktpos=positions[i];
                while(!aktpos){
                    aktpos=positions[i-1];
                    i--;
                }
                aktpos->suspended=true;
            }
        }
        delete pos;
        positions[aktiter]=0;

        if(!breaking){
            if(first){
                if(!IsUnbroken(first)){
                    UnCheck();
                    Image pic(DBodyImg.GetWidth(),bottom->positionY+15);
                    pic.Copy(DBodyImg, 0, 0, IntRect(0, 0, DBodyImg.GetWidth(), bottom->positionY+15), true);
                    pic.CreateMaskFromColor(Color(0,0,0));

                    breaking=true;
                    CollectShapes(first);
                    breaking=false;

                    shapecount-=position_collector.size();
                    if(position_collector.size()>5){
                        TOH->Add(new DestroyableBody(Window, world, TOH, destroyablebody->GetPosition().x, destroyablebody->GetPosition().y, destroyablebody->GetAngle(), position_collector, pic, Ilimit, Jlimit ));
                    }
                }
                UnCheck();
                position_collector.clear();
            }
            destroyablebody->SetMassFromShapes();
        }
        if(shapecount<6){
            deleteable=true;
        }
    }

    void DestroyableBody::CollectShapes(position* p){
        p->checked=true;
        position new_p;
        new_p.iterI=p->iterI;
        new_p.positionX=p->positionX;
        new_p.positionY=p->positionY;
        position_collector.push_back(new_p);
        if(p->left&&p->left->checked==false){
            CollectShapes(p->left);
        }
        if(p->right&&p->right->checked==false){
            CollectShapes(p->right);
        }
        if(p->up&&p->up->checked==false){
            CollectShapes(p->up);
        }
        if(p->down&&p->down->checked==false){
            CollectShapes(p->down);
        }
        EliminateShape(p->shape);
    }

    void DestroyableBody::SetNumber(int num){
        number=num;
    }

    int DestroyableBody::GetNumber(){
        return number;
    }

