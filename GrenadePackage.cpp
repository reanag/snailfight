#include "GrenadePackage.hpp"

	GrenadePackage::GrenadePackage(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY):Package(window, World, toh, PositionX, PositionY){
        subcaste="grenade";
        addGrenade=5;
        CreateBody(PositionX, PositionY);
        LoadImage("contents/grenade_pack.png",packageImg,PackageSp);
        PackageSp.SetCenter(packageshapeDef.vertices[2].x,packageshapeDef.vertices[2].y);
	}
