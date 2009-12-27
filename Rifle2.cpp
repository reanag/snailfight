#include "Rifle2.hpp"

	Rifle2::Rifle2(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY)/*:Weapon(RenderWindow* window, b2World* World, float PositionX, float PositionY)*/{
	    Window=window;
	    world=World;
	    TOH=toh;

        damage=10;
	    timer=0;
	    firespeed=1;
	    fliped=false;
        MouseTargeting=false;
        showmuzzle=false;

        CreateBody(PositionX,PositionY);
        LoadImage("contents/Rifle2.png");
        WeaponSp.SetCenter(weaponshapeDef.vertices[2].x+1,weaponshapeDef.vertices[2].y+7);
        LoadMuzzle("contents/tt2.png");
        MuzzleSp.SetCenter(3,87);
        MuzzleSp.SetScale(0.5,0.5);
        LoadSound("contents/Gun_Silencer.wav");
	}
