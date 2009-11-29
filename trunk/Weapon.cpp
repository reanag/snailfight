#include "Weapon.hpp"

	Weapon::Weapon(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY){
	    Window=window;
	    world=World;
	    TOH=toh;

	    fliped=false;

	    weaponbodyDef.position.Set(PositionX, PositionY);
        weaponbody = world->CreateBody(&weaponbodyDef);
        weaponshapeDef.SetAsBox(62.5f, 5.0f);
        weaponshapeDef.density = 0.01f;
        weaponshapeDef.friction = 1.0f;
        weaponbody->CreateShape(&weaponshapeDef);
        weaponbody->SetMassFromShapes();
        weapondata.label="weapon";
        weapondata.object=this;
        weaponbody->SetUserData(&weapondata);

	}

	void Weapon::LoadImage(string file){
	    weaponImg.LoadFromFile(file.c_str());
        WeaponSp.SetImage(weaponImg);
        WeaponSp.SetPosition(weaponbodyDef.position.x,weaponbodyDef.position.y);
        WeaponSp.SetCenter(weaponshapeDef.vertices[2].x+1,weaponshapeDef.vertices[2].y);
    }

	void Weapon::FlipX(bool flip){
        if(flip){
            fliped=true;
            WeaponSp.FlipX(true);
        }else{
            fliped=false;
            WeaponSp.FlipX(false);
        }
    }

	void Weapon::Show(){
	    Window->Draw(WeaponSp);
    }

	void Weapon::InputHandling(Event ev){
        float tav_x=Window->GetInput().GetMouseX()-weaponbody->GetPosition().x;
        float tav_y=Window->GetInput().GetMouseY()-weaponbody->GetPosition().y;
        weaponbody->SetXForm(weaponbody->GetPosition(),(atan(tav_y/tav_x)));
        WeaponSp.SetPosition(weaponbody->GetPosition().x,weaponbody->GetPosition().y);
        WeaponSp.SetRotation(weaponbody->GetAngle()*-57.29577951308232);
	}
