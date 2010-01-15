#include "Bullet.hpp"

	Bullet::Bullet(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, float VelocityX, float VelocityY, int Damage){
	    Window=window;
	    world=World;
	    TOH=toh;
	    damage=Damage;
	    lim=false;

        bulletbodyDef.position.Set(PositionX, PositionY);
        bulletbody = world->CreateBody(&bulletbodyDef);
        bulletbodyDef.isBullet = true;
        bulletbodyDef.allowSleep = false;
        bulletshapeDef.density = 50.0f;
        bulletshapeDef.radius = 2.0f;
        bulletshapeDef.restitution = 0.05f;
        bulletbody->CreateShape(&bulletshapeDef);
        bulletbody->SetMassFromShapes();
        bulletdata.label="bullet";
        bulletdata.object=this;
        bulletbody->SetUserData(&bulletdata);
        bulletbody->SetLinearVelocity(b2Vec2(VelocityX, VelocityY));

        BulletSp=Shape::Circle(0,0,2.0,Color(200,200,200));
        BulletSp.SetPosition(bulletbody->GetPosition().x,bulletbody->GetPosition().y);
	}

	void Bullet::Show(){
            Window->Draw(BulletSp);
    }

	void Bullet::InputHandling(){
        BulletSp.SetPosition(bulletbody->GetPosition().x,bulletbody->GetPosition().y);
        //BulletSp.SetRotation(bulletbody->GetAngle()*-57.29577951308232);

        //cout<<bulletbody->GetLinearVelocity().x<<" "<<bulletbody->GetLinearVelocity().y<<endl;
        if(bulletbody->GetLinearVelocity().x>-2 && bulletbody->GetLinearVelocity().x<2 && bulletbody->GetLinearVelocity().y>-2 && bulletbody->GetLinearVelocity().y<2){
            DestroyBullet();
        }
	}

    void Bullet::DestroyBullet(){
        world->DestroyBody(bulletbody);
        TOH->Remove(this);
    }

    void Bullet::SetNumber(int num){
        number=num;
    }

    int Bullet::GetNumber(){
        return number;
    }

    int Bullet::GetDamage(){
        return damage;
    }
