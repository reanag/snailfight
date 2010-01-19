#include "RocketPackage.hpp"

	RocketPackage::RocketPackage(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY):Package(window, World, toh, PositionX, PositionY){
        subcaste="rocket";
        addRocket=5;
        CreateBody(PositionX, PositionY);
        LoadImage("contents/rocket_pack.png",packageImg,PackageSp);
        PackageSp.SetCenter(packageshapeDef.vertices[2].x,packageshapeDef.vertices[2].y);
	}

