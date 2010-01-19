#include "HealthPackage.hpp"

	HealthPackage::HealthPackage(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY):Package(window, World, toh, PositionX, PositionY){
        subcaste="health";
        addHeal=25;
        CreateBody(PositionX, PositionY);
        LoadImage("contents/health_pack.png",packageImg,PackageSp);
        PackageSp.SetCenter(packageshapeDef.vertices[2].x,packageshapeDef.vertices[2].y);
	}

	/*void HealthPackage::Show(){
            Window->Draw(PackageSp);
    }

	void HealthPackage::InputHandling(){
        PackageSp.SetPosition(packagebody->GetPosition().x,packagebody->GetPosition().y);
        PackageSp.SetRotation(packagebody->GetAngle()*-57.29577951308232);
	}

    void HealthPackage::DestroyPackage(){
        world->DestroyBody(packagebody);
        TOH->Remove(this);
    }

    void HealthPackage::SetNumber(int num){
        number=num;
    }

    int HealthPackage::GetNumber(){
        return number;
    }*/
