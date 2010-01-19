#include "RocketLauncher.hpp"
#include "Snail.hpp"

	RocketLauncher::RocketLauncher(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, int Ammunition, Snail* user):Weapon(window, World, toh, PositionX, PositionY, Ammunition){
        User=user;
        damage=15;
        clipsize=1;
        clip=clipsize;
        ammunition=Ammunition-clip;
	    firespeed=0.2;

        CreateBody(PositionX,PositionY, 72.5, 10);
        LoadImage("contents/rocketluncher2.png", weaponImg, WeaponSp);
        WeaponSp.SetCenter(weaponshapeDef.vertices[2].x,weaponshapeDef.vertices[2].y+6.5);
        LoadImage("contents/tt2.png", muzzleImg, MuzzleSp);
        MuzzleSp.SetCenter(3,87);
        MuzzleSp.SetScale(0.5,0.5);
        LoadSound("contents/RocketLauncher.wav", WeaponFireSoundBuffer, WeaponFireSound);
        LoadSound("contents/flak_reload.wav", WeaponReloadSoundBuffer, WeaponReloadSound);
        LoadSound("contents/Sound 837 clip out 1.wav", WeaponOutOfAmmoSoundBuffer, WeaponOutOfAmmoSound);

        jointX=30;
        jointY=-15;
	}

    void RocketLauncher::Shot(){
        if(ammunition==0 && clip==0 && WeaponOutOfAmmoSound.GetPlayingOffset()==0)WeaponOutOfAmmoSound.Play();
	    if(timer>firespeed && (ammunition>0 || clip>0) && WeaponReloadSound.GetPlayingOffset()==0 ){
	        //Vector2f Mouse = Window->ConvertCoords(Window->GetInput().GetMouseX(),Window->GetInput().GetMouseY());
            float Vx=(Target.x-weaponbody->GetPosition().x)*10;
            float Vy=(Target.y-weaponbody->GetPosition().y)*10;
            float modx=cos(weaponbody->GetAngle())*62.5;
            float mody=sin(weaponbody->GetAngle())*62.5;
            Rocket* r;
            if(fliped){
                r=new Rocket(Window, world, TOH, weaponbody->GetPosition().x-modx, weaponbody->GetPosition().y-mody, Vx, Vy, damage);
                MuzzleSp.FlipX(fliped);
                MuzzleSp.SetPosition(weaponbody->GetPosition().x-modx*2.65, weaponbody->GetPosition().y-mody*2.65);
            }else{
                r=new Rocket(Window, world, TOH, weaponbody->GetPosition().x+modx, weaponbody->GetPosition().y+mody, Vx, Vy, damage);
                MuzzleSp.FlipX(fliped);
                MuzzleSp.SetPosition(weaponbody->GetPosition().x+modx, weaponbody->GetPosition().y+mody);
            }
            TOH->Add(r);
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

            float modX=cos(weaponbody->GetAngle())*30;
            float modY=sin(weaponbody->GetAngle())*30;
            if(fliped){
                User->snailbody->SetLinearVelocity(b2Vec2(modX,modY));
            }else{
                User->snailbody->SetLinearVelocity(b2Vec2(-modX,-modY));
            }
	    }
    }
