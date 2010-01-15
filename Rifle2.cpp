#include "Rifle2.hpp"
//the yellow rifle
	Rifle2::Rifle2(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, int Ammunition):Weapon(window, World, toh, PositionX, PositionY, Ammunition){
        damage=10;
        clipsize=1;
        clip=clipsize;
        ammunition=Ammunition-clip;
	    firespeed=1;

        CreateBody(PositionX,PositionY);
        LoadImage("contents/Rifle2.png", weaponImg, WeaponSp);
        WeaponSp.SetCenter(weaponshapeDef.vertices[2].x+1,weaponshapeDef.vertices[2].y+7);
        LoadImage("contents/tt2.png", muzzleImg, MuzzleSp);
        MuzzleSp.SetCenter(3,87);
        MuzzleSp.SetScale(0.5,0.5);
        LoadSound("contents/Sound 635.wav", WeaponFireSoundBuffer, WeaponFireSound);
        LoadSound("contents/Sound 637 load 4.wav", WeaponReloadSoundBuffer, WeaponReloadSound);
        LoadSound("contents/Sound 837 clip out 1.wav", WeaponOutOfAmmoSoundBuffer, WeaponOutOfAmmoSound);
	}
