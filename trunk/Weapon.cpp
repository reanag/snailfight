#include "Weapon.hpp"

	Weapon::Weapon(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, int Ammunition){
	    Window=window;
	    world=World;
	    TOH=toh;

        damage=3;
        clipsize=10;
        clip=clipsize;
        ammunition=Ammunition-clip;
        maxammunition=200;
	    timer=0;
	    firespeed=0.1;
	    fliped=false;
        MouseTargeting=false;
        showmuzzle=false;
        inUse=false;
        debugDraw=false;

        jointX=30;
        jointY=0;
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

    void Weapon::CreateBody(float PositionX, float PositionY, float HalfWidth, float HalfHeight){
	    weaponbodyDef.position.Set(PositionX, PositionY);
        weaponbody = world->CreateBody(&weaponbodyDef);
        weaponshapeDef.SetAsBox(HalfWidth, HalfHeight);
        weaponshapeDef.density = 0.01f;
        weaponshapeDef.friction = 1.0f;
        weaponbody->CreateShape(&weaponshapeDef);
        weaponbody->SetMassFromShapes();
        weapondata.label="weapon";
        weapondata.object=this;
        weaponbody->SetUserData(&weapondata);
    }

	void Weapon::LoadImage(string file, Image& image, Sprite& sprite){
	    image.LoadFromFile(file.c_str());
        sprite.SetImage(image);
        sprite.SetPosition(weaponbodyDef.position.x,weaponbodyDef.position.y);
    }

    void Weapon::LoadSound(string file, SoundBuffer& buffer, Sound& sound){
        buffer.LoadFromFile(file.c_str());
        sound.SetBuffer(buffer);
    }

    void Weapon::CreateDebugShape(){
        debugDrawShape=Shape::Rectangle(0, 0, weaponshapeDef.vertices[2].x*2, weaponshapeDef.vertices[2].y*2, Color(200,0,0));
        debugDrawShape.SetCenter(weaponshapeDef.vertices[2].x, weaponshapeDef.vertices[2].y);
        debugDrawShape.SetPosition(weaponbody->GetPosition().x,weaponbody->GetPosition().y);
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
	    if(showmuzzle){
	        Window->Draw(MuzzleSp);
	        showmuzzle=false;
        }
	    Window->Draw(WeaponSp);
        if(debugDraw)Window->Draw(debugDrawShape);
    }

    void Weapon::SetTargetPoint(int x, int y){
        Target.x = x;
        Target.y = y;
        // Target = Window->ConvertCoords(x,y);
    }

	void Weapon::InputHandling(){
        timer+=Window->GetFrameTime();
	    if(MouseTargeting){
	        //Vector2f Mouse = Window->ConvertCoords(Window->GetInput().GetMouseX(),Window->GetInput().GetMouseY());
            float tav_x=Target.x-weaponbody->GetPosition().x;
            float tav_y=Target.y-weaponbody->GetPosition().y;
            weaponbody->SetXForm(weaponbody->GetPosition(),atan(tav_y/tav_x));
	    }
        WeaponSp.SetPosition(weaponbody->GetPosition().x,weaponbody->GetPosition().y);
        WeaponSp.SetRotation(weaponbody->GetAngle()*-57.29577951308232);
        if(debugDraw){
            debugDrawShape.SetPosition(weaponbody->GetPosition().x,weaponbody->GetPosition().y);
            debugDrawShape.SetRotation(weaponbody->GetAngle()*-57.29577951308232);
        }
	}

	void Weapon::Shot(){
        if(ammunition==0 && clip==0 && WeaponOutOfAmmoSound.GetPlayingOffset()==0)WeaponOutOfAmmoSound.Play();
	    if(timer>firespeed && (ammunition>0 || clip>0) && WeaponReloadSound.GetPlayingOffset()==0 ){
	        //Vector2f Mouse = Window->ConvertCoords(Window->GetInput().GetMouseX(),Window->GetInput().GetMouseY());
            float Vx=(Target.x-weaponbody->GetPosition().x)*10;
            float Vy=(Target.y-weaponbody->GetPosition().y)*10;
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

            clip--;
            if(clip==0 && ammunition>0){
                WeaponReloadSound.Play();
                if(ammunition>=clipsize){
                    clip=clipsize;
                    ammunition-=clipsize;
                }else{
                    clip=ammunition;
                    ammunition=0;
                }
            }
            //cout<<clip<<" "<<ammunition<<endl;
	    }
    }

    void Weapon::Use(float PositionX, float PositionY){
        inUse=true;
        CreateBody(PositionX, PositionY, weaponshapeDef.vertices[2].x, weaponshapeDef.vertices[2].y);
        MouseTargeting=true;
    }

    void Weapon::UnUse(){
        inUse=false;
        world->DestroyBody(weaponbody);
        MouseTargeting=false;
    }

    void Weapon::AddAmmo(int ammo){
        ammunition+=ammo;
        if(ammunition>maxammunition){
            ammunition>maxammunition;
        }
    }
