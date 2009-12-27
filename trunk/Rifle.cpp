#include "Rifle.hpp"

	Rifle::Rifle(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY)/*:Weapon(RenderWindow* window, b2World* World, float PositionX, float PositionY)*/{
	    Window=window;
	    world=World;
	    TOH=toh;

	    damage=3;
	    timer=0;
	    firespeed=0.1;
	    fliped=false;
        MouseTargeting=false;
        showmuzzle=false;

        CreateBody(PositionX,PositionY);
        LoadImage("contents/Rifle1.2.png");
        WeaponSp.SetCenter(weaponshapeDef.vertices[2].x+1,weaponshapeDef.vertices[2].y);
        LoadMuzzle("contents/tt2.png");
        MuzzleSp.SetCenter(3,87);
        MuzzleSp.SetScale(0.5,0.5);
        LoadSound("contents/Gun_Silencer.wav");
/*
	    weaponbodyDef.position.Set(PositionX, PositionY);
        weaponbody = world->CreateBody(&weaponbodyDef);
        weaponshapeDef.SetAsBox(62.5f, 5.0f);
        weaponshapeDef.density = 0.01f;
        weaponshapeDef.friction = 1.0f;
        weaponbody->CreateShape(&weaponshapeDef);
        weaponbody->SetMassFromShapes();
        weapondata.label="rifle";
        weapondata.object=this;
        weaponbody->SetUserData(&weapondata);

	    weaponImg.LoadFromFile("contents/Rifle1.2.png");
        WeaponSp.SetImage(weaponImg);
        WeaponSp.SetPosition(PositionX,PositionY);
        WeaponSp.SetCenter(weaponshapeDef.vertices[2].x+1,weaponshapeDef.vertices[2].y);

        muzzleImg.LoadFromFile("contents/tt2.png");
        MuzzleSp.SetImage(muzzleImg);
        //MuzzleSp.SetPosition(PositionX,PositionY);
        MuzzleSp.SetCenter(3,87);
        MuzzleSp.SetScale(0.5,0.5);
        showmuzzle=false;

        Buffer.LoadFromFile("contents/Gun_Silencer.wav");
        WeaponFireSound.SetBuffer(Buffer);
        WeaponFireSound.SetVolume(100);

        MouseTargeting=false;*/


	}

	/*void Rifle::FlipX(bool flip){
        if(flip){
            fliped=true;
            WeaponSp.FlipX(true);
        }else{
            fliped=false;
            WeaponSp.FlipX(false);
        }
    }*/

	/*void Rifle::Show(){
	    Window->Draw(WeaponSp);
	    if(showmuzzle){
	        Window->Draw(MuzzleSp);
	        showmuzzle=false;
        }
    }

    void Rifle::InputHandling(Event ev){
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

	void Rifle::Shot(){
	    if(timer>firespeed){
	        Vector2f Mouse = Window->ConvertCoords(Window->GetInput().GetMouseX(),Window->GetInput().GetMouseY());
            float Vx=(Mouse.x-weaponbody->GetPosition().x)*10;
            float Vy=(Mouse.y-weaponbody->GetPosition().y)*10;
            float modx=cos(weaponbody->GetAngle())*62.5;
            float mody=sin(weaponbody->GetAngle())*62.5;
            Bullet* b;
            if(fliped){
                b=new Bullet(Window, world, TOH, weaponbody->GetPosition().x-modx, weaponbody->GetPosition().y-mody, Vx, Vy);
                MuzzleSp.FlipX(fliped);
                MuzzleSp.SetPosition(weaponbody->GetPosition().x-modx*2.65, weaponbody->GetPosition().y-mody*2.65);
            }else{
                b=new Bullet(Window, world, TOH, weaponbody->GetPosition().x+modx, weaponbody->GetPosition().y+mody, Vx, Vy);
                MuzzleSp.FlipX(fliped);
                MuzzleSp.SetPosition(weaponbody->GetPosition().x+modx, weaponbody->GetPosition().y+mody);
            }
            TOH->Add(b);
            MuzzleSp.SetRotation(weaponbody->GetAngle()*-57.29577951308232);
            showmuzzle=true;
            WeaponFireSound.Play();
            timer=0;
	    }
    }*/

