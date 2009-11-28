#include "Rifle.hpp"

	Rifle::Rifle(RenderWindow* window, b2World* World, float PositionX, float PositionY){
	    Window=window;
	    world=World;

	    fliped=false;

	    riflebodyDef.position.Set(PositionX, PositionY);
        riflebody = world->CreateBody(&riflebodyDef);
        rifleshapeDef.SetAsBox(62.5f, 5.0f);
        rifleshapeDef.density = 0.01f;
        rifleshapeDef.friction = 1.0f;
        riflebody->CreateShape(&rifleshapeDef);

        riflebody->SetMassFromShapes();

        /*Body=Shape::Rectangle(0,0,rifleshapeDef.vertices[2].x*2,rifleshapeDef.vertices[2].y*2,Color(255,0,0));
        Body.SetPosition(riflebody->GetPosition().x,riflebody->GetPosition().y);
        Body.SetCenter(rifleshapeDef.vertices[2].x,rifleshapeDef.vertices[2].y);*/


	    rifleImg.LoadFromFile("Rifle1.2.png");
        RifleSp.SetImage(rifleImg);
        RifleSp.SetPosition(PositionX,PositionY);
        RifleSp.SetCenter(rifleshapeDef.vertices[2].x+1,rifleshapeDef.vertices[2].y);

        bullcd.density = 20.0f;
        bullcd.radius = 2.0f;
        bullcd.restitution = 0.05f;
        Bullet=Shape::Circle(0,0,2.0,Color(255,255,255));
        bullet=NULL;
	}

	void Rifle::FlipX(bool flip){
        if(flip){
            fliped=true;
            RifleSp.FlipX(true);
        }else{
            fliped=false;
            RifleSp.FlipX(false);
        }
    }

	void Rifle::Show(){
	    Window->Draw(Bullet);
	    Window->Draw(RifleSp);
	    //Window->Draw(Body);
    }

	void Rifle::InputHandling(Event ev){

            if(ev.Type == Event::MouseButtonPressed){
                if(ev.Key.Code == 0){
                    if(bullet != NULL){
                        world->DestroyBody(bullet);
                        bullet = NULL;
                    }
                    bd.isBullet = true;
                    bd.allowSleep = false;
                    bd.position.Set(riflebody->GetPosition().x,riflebody->GetPosition().y);

                    bullet = world->CreateBody(&bd);
                    bullet->CreateShape(&bullcd);
                    bullet->SetMassFromShapes();

                    bullet->SetLinearVelocity(b2Vec2((Window->GetInput().GetMouseX()-riflebody->GetPosition().x),(Window->GetInput().GetMouseY()-riflebody->GetPosition().y)));

                    Bullet.SetPosition(bullet->GetPosition().x,bullet->GetPosition().y);
                }
            }

        float tav_x=Window->GetInput().GetMouseX()-riflebody->GetPosition().x;
        float tav_y=Window->GetInput().GetMouseY()-riflebody->GetPosition().y;
        riflebody->SetXForm(riflebody->GetPosition(),(atan(tav_y/tav_x)/**57.29577951308232*/));
	    Body.SetPosition(riflebody->GetPosition().x,riflebody->GetPosition().y);
        Body.SetRotation(riflebody->GetAngle()*-57.29577951308232);
        RifleSp.SetPosition(riflebody->GetPosition().x,riflebody->GetPosition().y);
        RifleSp.SetRotation(riflebody->GetAngle()*-57.29577951308232);
        if(bullet != NULL){
            Bullet.SetPosition(bullet->GetPosition().x,bullet->GetPosition().y);
        }




	}
