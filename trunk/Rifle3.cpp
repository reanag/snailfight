#include "Rifle3.hpp"
//the red rifle
	Rifle3::Rifle3(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, int Ammunition):Weapon(window, World, toh, PositionX, PositionY, Ammunition){
        damage=5;
        clipsize=12;
        clip=clipsize;
        ammunition=Ammunition-clip;
	    firespeed=0.2;

        CreateBody(PositionX,PositionY);
        LoadImage("contents/Rifle3.png", weaponImg, WeaponSp);
        WeaponSp.SetCenter(weaponshapeDef.vertices[2].x+1,weaponshapeDef.vertices[2].y);
        LoadImage("contents/tt2.png", muzzleImg, MuzzleSp);
        MuzzleSp.SetCenter(3,87);
        MuzzleSp.SetScale(0.5,0.5);
        LoadSound("contents/Sound 629 fire 8.wav", WeaponFireSoundBuffer, WeaponFireSound);
        LoadSound("contents/Sound 649 load 8.wav", WeaponReloadSoundBuffer, WeaponReloadSound);
        LoadSound("contents/Sound 837 clip out 1.wav", WeaponOutOfAmmoSoundBuffer, WeaponOutOfAmmoSound);
	}
