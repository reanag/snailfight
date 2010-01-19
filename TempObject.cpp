#include "TempObject.hpp"

	TempObject::TempObject(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY){
	    Window=window;
	    world=World;
	    TOH=toh;

        objectbodyDef.position.Set(PositionX, PositionY);
        objectbody = world->CreateBody(&objectbodyDef);

        objectshapeDef.density = 20.0f;
        objectshapeDef.radius = 10.0f;
        objectshapeDef.restitution = 0.05f;
        objectbody->CreateShape(&objectshapeDef);
        objectbody->SetMassFromShapes();
        objectdata.label="tempObject";
        objectdata.object=this;
        objectbody->SetUserData(&objectdata);

	    objectImg.LoadFromFile("contents/");
        ObjectSp.SetImage(objectImg);
        ObjectSp.SetPosition(PositionX, PositionY);
        ObjectSp.SetCenter(objectbody->GetLocalCenter().x+17,objectbody->GetLocalCenter().y+28);
	}

	void TempObject::LoadImage(string file, Image& image, Sprite& sprite){
	    image.LoadFromFile(file.c_str());
        sprite.SetImage(image);
//        sprite.SetPosition(weaponbodyDef.position.x,weaponbodyDef.position.y);
    }

    void TempObject::CreateDebugShape(){
    //    debugDrawShape=Shape::Rectangle(0, 0, weaponshapeDef.vertices[2].x*2, weaponshapeDef.vertices[2].y*2, Color(200,0,0));
     //   debugDrawShape.SetCenter(weaponshapeDef.vertices[2].x, weaponshapeDef.vertices[2].y);
      //  debugDrawShape.SetPosition(weaponbody->GetPosition().x,weaponbody->GetPosition().y);
    }

	void TempObject::Show(){
            Window->Draw(ObjectSp);
    }

	void TempObject::InputHandling(){
        ObjectSp.SetPosition(objectbody->GetPosition().x,objectbody->GetPosition().y);
        ObjectSp.SetRotation(objectbody->GetAngle()*-57.29577951308232);
	}

    void TempObject::DestroyObject(){
        world->DestroyBody(objectbody);
        //TOH->Remove(this);
    }

    void TempObject::SetNumber(int num){
        number=num;
    }

    int TempObject::GetNumber(){
        return number;
    }
