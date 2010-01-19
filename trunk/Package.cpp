#include "Package.hpp"

	Package::Package(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY){
	    Window=window;
	    world=World;
	    TOH=toh;
	}

	void Package::CreateBody(float PositionX, float PositionY){
	    packagebodyDef.position.Set(PositionX, PositionY);
        packagebody = world->CreateBody(&packagebodyDef);
        packageshapeDef.SetAsBox(20.5f, 20.0f);
        packageshapeDef.density = 10.0f;
        packageshapeDef.restitution = 0.05f;
        packagebody->CreateShape(&packageshapeDef);
        packagebody->SetMassFromShapes();
        packagedata.label="package";
        packagedata.object=this;
        packagebody->SetUserData(&packagedata);
    }

    void Package::CreateBody(float PositionX, float PositionY, float HalfWidth, float HalfHeight){
        packagebodyDef.position.Set(PositionX, PositionY);
        packagebody = world->CreateBody(&packagebodyDef);
        packageshapeDef.SetAsBox(HalfWidth, HalfHeight);
        packageshapeDef.density = 10.0f;
        packageshapeDef.restitution = 0.05f;
        packagebody->CreateShape(&packageshapeDef);
        packagebody->SetMassFromShapes();
        packagedata.label="package";
        packagedata.object=this;
        packagebody->SetUserData(&packagedata);
    }

	void Package::LoadImage(string file, Image& image, Sprite& sprite){
	    image.LoadFromFile(file.c_str());
        sprite.SetImage(image);
        sprite.SetPosition(packagebody->GetPosition().x,packagebody->GetPosition().y);
    }

	void Package::Show(){
            Window->Draw(PackageSp);
    }

	void Package::InputHandling(){
        PackageSp.SetPosition(packagebody->GetPosition().x,packagebody->GetPosition().y);
        PackageSp.SetRotation(packagebody->GetAngle()*-57.29577951308232);
	}

    void Package::DestroyPackage(){
        world->DestroyBody(packagebody);
        TOH->Remove(this);
    }

    void Package::SetNumber(int num){
        number=num;
    }

    int Package::GetNumber(){
        return number;
    }
