#include "Weapon.hpp"

	Weapon::Weapon(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY){
	    Window=window;
	    world=World;
	    TOH=toh;

        damage=3;
	    timer=0;
	    firespeed=0.1;
	    fliped=false;
        MouseTargeting=false;
        showmuzzle=false;
        inUse=false;

	    CreateBody(PositionX, PositionY);
	}

	void Weapon::CreateBody(float PositionX, float PositionY){
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
    }

    void Weapon::LoadMuzzle(string file){
        muzzleImg.LoadFromFile(file.c_str());
        MuzzleSp.SetImage(muzzleImg);
    }

    void Weapon::LoadSound(string file){
        WeaponFireSoundBuffer.LoadFromFile(file.c_str());
        WeaponFireSound.SetBuffer(WeaponFireSoundBuffer);
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
	    if(showmuzzle){
	        Window->Draw(MuzzleSp);
	        showmuzzle=false;
        }
    }

	void Weapon::InputHandling(Event ev){
        timer+=Window->GetFrameTime();
	    if(MouseTargeting){
	        Vector2f Mouse = Window->ConvertCoords(Window->GetInput().GetMouseX(),Window->GetInput().GetMouseY());
            float tav_x=Mouse.x-weaponbody->GetPosition().x;
            float tav_y=Mouse.y-weaponbody->GetPosition().y;
            weaponbody->SetXForm(weaponbody->GetPosition(),atan(tav_y/tav_x));
	    }
        WeaponSp.SetPosition(weaponbody->GetPosition().x,weaponbody->GetPosition().y);
        WeaponSp.SetRotation(weaponbody->GetAngle()*-57.29577951308232);

	}

	void Weapon::Shot(){
	    if(timer>firespeed){
	        Vector2f Mouse = Window->ConvertCoords(Window->GetInput().GetMouseX(),Window->GetInput().GetMouseY());
            float Vx=(Mouse.x-weaponbody->GetPosition().x)*10;
            float Vy=(Mouse.y-weaponbody->GetPosition().y)*10;
            float modx=cos(weaponbody->GetAngle())*62.5;
            float mody=sin(weaponbody->GetAngle())*62.5;
            Bullet* b;
            if(fliped){
                b=new Bullet(Window, world, TOH, weaponbody->GetPosition().x-modx, weaponbody->GetPosition().y-mody, Vx, Vy, damage);
                MuzzleSp.FlipX(fliped);
                MuzzleSp.SetPosition(weaponbody->GetPosition().x-modx*2.65, weaponbody->GetPosition().y-mody*2.65);
            }else{
                b=new Bullet(Window, world, TOH, weaponbody->GetPosition().x+modx, weaponbody->GetPosition().y+mody, Vx, Vy, damage);
                MuzzleSp.FlipX(fliped);
                MuzzleSp.SetPosition(weaponbody->GetPosition().x+modx, weaponbody->GetPosition().y+mody);
            }
            TOH->Add(b);
            MuzzleSp.SetRotation(weaponbody->GetAngle()*-57.29577951308232);
            showmuzzle=true;
            WeaponFireSound.Play();
            timer=0;
	    }
    }

    void Weapon::Use(float PositionX, float PositionY){
        inUse=true;
        CreateBody(PositionX, PositionY);
        MouseTargeting=true;
    }

    void Weapon::UnUse(){
        inUse=false;
        world->DestroyBody(weaponbody);
        MouseTargeting=false;
    }
