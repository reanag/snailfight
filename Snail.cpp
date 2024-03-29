#include "Snail.hpp"

	Snail::Snail(RenderWindow* window, b2World* World, TempObjectHandler* toh, GameSurface* surface, float PositionX, float PositionY, bool Controlled, Pool* p,  bool b){
	    poo = p;
	    NET = b;
	    Window=window;
	    world=World;
	    TOH=toh;
		Surface=surface;

	    Health=100;
	    Stamina=100;
	    Speed=30;
	    alive=true;
	    turbo=false;

		grenades=5;
	    grenadethrowspeed=0.5;
        timer=0;

	    fliped=false;
	    hid=false;
	    jump=false;
	    controlled=Controlled;
	    up=false;
	    once=false;
        mx=41.5095;
        my=20.7499;

        snailbodyDef.position.Set(PositionX, PositionY);
        snailbody = world->CreateBody(&snailbodyDef);

        bodyshapeDef.vertexCount = 3;
        bodyshapeDef.vertices[0].Set(71-mx,0-my);
        bodyshapeDef.vertices[1].Set(71-mx,45-my);
        bodyshapeDef.vertices[2].Set(0-mx,45-my);
        bodyshapeDef.density = 30.0f;
        bodyshapeDef.friction = 0.5f;
        snailbody->CreateShape(&bodyshapeDef);

        houseshapeDef.radius = 35.0f;
        houseshapeDef.density = 5.0f;
        houseshapeDef.localPosition.Set(25-mx, 0-my);
        snailbody->CreateShape(&houseshapeDef);

        head1Def.radius = 10.0f;
        head1Def.density = 1.0f;
        head1Def.localPosition.Set(82-mx, -2-my);
        snailbody->CreateShape(&head1Def);

        head2Def.radius = 10.0f;
        head2Def.density = 1.0f;
        head2Def.localPosition.Set(73-mx, -18-my);
        snailbody->CreateShape(&head2Def);

        snailbody->SetMassFromShapes();
        snaildata.label="snail";
        snaildata.object=this;
        snailbody->SetUserData(&snaildata);

        b2Vec2 p1, p2;
        jd.frequencyHz = 1.0f;
        jd.dampingRatio = 0.5f;

        eye1Def.position.Set(PositionX+95-mx, PositionY-73-my);
        eye1 = world->CreateBody(&eye1Def);
        e1.radius = 7.5f;
        e1.density = 1.0f;
        e1.friction = 0.5f;
        eye1->CreateShape(&e1);
        eye1->SetMassFromShapes();
        eye1data.label="eye1";
        eye1data.object=this;
        eye1->SetUserData(&eye1data);

        jd.body1 = snailbody;
        jd.body2 = eye1;
        jd.localAnchor1.Set(0.0f, 30.0f);
        jd.localAnchor2.Set(0.0f, 0.0f);
        p1 = jd.body1->GetWorldPoint(jd.localAnchor1);
        p2 = jd.body2->GetWorldPoint(jd.localAnchor2);
        d[0] = p2 - p1;
        jd.length = d[0].Length();
        world->CreateJoint(&jd);

        jd.body1 = snailbody;
        jd.body2 = eye1;
        jd.localAnchor1.Set(30.0f, 0.0f);
        jd.localAnchor2.Set(0.0f, 0.0f);
        p1 = jd.body1->GetWorldPoint(jd.localAnchor1);
        p2 = jd.body2->GetWorldPoint(jd.localAnchor2);
        d[1] = p2 - p1;
        jd.length = d[1].Length();
        world->CreateJoint(&jd);

        jd.body1 = snailbody;
        jd.body2 = eye1;
        jd.localAnchor1.Set(30.0f, 30.0f);
        jd.localAnchor2.Set(0.0f, 0.0f);
        p1 = jd.body1->GetWorldPoint(jd.localAnchor1);
        p2 = jd.body2->GetWorldPoint(jd.localAnchor2);
        d[2] = p2 - p1;
        jd.length = d[2].Length();
        world->CreateJoint(&jd);

        eye2Def.position.Set(PositionX+110-mx, PositionY-65-my);
        eye2 = world->CreateBody(&eye2Def);
        e2.radius = 5.5f;
        e2.density = 1.0f;
        e2.friction = 0.5f;
        eye2->CreateShape(&e2);
        eye2->SetMassFromShapes();
        eye2data.label="eye2";
        eye2data.object=this;
        eye2->SetUserData(&eye2data);

        jd.body1 = snailbody;
        jd.body2 = eye2;
        jd.localAnchor1.Set(0.0f, 30.0f);
        jd.localAnchor2.Set(0.0f, 0.0f);
        p1 = jd.body1->GetWorldPoint(jd.localAnchor1);
        p2 = jd.body2->GetWorldPoint(jd.localAnchor2);
        d[3] = p2 - p1;
        jd.length = d[3].Length();
        world->CreateJoint(&jd);

        jd.body1 = snailbody;
        jd.body2 = eye2;
        jd.localAnchor1.Set(30.0f, 0.0f);
        jd.localAnchor2.Set(0.0f, 0.0f);
        p1 = jd.body1->GetWorldPoint(jd.localAnchor1);
        p2 = jd.body2->GetWorldPoint(jd.localAnchor2);
        d[4] = p2 - p1;
        jd.length = d[4].Length();
        world->CreateJoint(&jd);

        jd.body1 = snailbody;
        jd.body2 = eye2;
        jd.localAnchor1.Set(30.0f, 30.0f);
        jd.localAnchor2.Set(0.0f, 0.0f);
        p1 = jd.body1->GetWorldPoint(jd.localAnchor1);
        p2 = jd.body2->GetWorldPoint(jd.localAnchor2);
        d[5] = p2 - p1;
        jd.length = d[5].Length();
        world->CreateJoint(&jd);

        for(int i=0;i<11;i++){
            stringstream out;
            out << i;
            string s = "contents/csig1.6_wounds" + out.str() + ".png";
            snailImg[i].LoadFromFile(s.c_str());
        }
        aktImg=0;

        houseImg.LoadFromFile("contents/csig1.6.house.png");
        SnailSp.Scale(0.5,0.5);
        SnailSp.SetCenter(654+mx*2,444+my*2);
        SnailSp.SetImage(snailImg[aktImg]);

        eye1Img.LoadFromFile("contents/szem1.png");
        Eye1Sp.SetImage(eye1Img);
        Eye1Sp.Scale(0.5,0.5);
        Eye1Sp.SetCenter(20,18);
        eye2Img.LoadFromFile("contents/szem2.png");
        Eye2Sp.SetImage(eye2Img);
        Eye2Sp.Scale(0.5,0.5);
        Eye2Sp.SetCenter(14,12);

        aktWeapon=0;
        Weapons.push_back(new Rifle(Window, world, TOH, snailbody->GetWorldCenter().x, snailbody->GetWorldCenter().y, 500));
        Weapons.push_back(new Rifle2(Window, world, TOH, snailbody->GetWorldCenter().x, snailbody->GetWorldCenter().y, 200));
        Weapons.push_back(new Rifle3(Window, world, TOH, snailbody->GetWorldCenter().x, snailbody->GetWorldCenter().y, 200));
        Weapons.push_back(new RocketLauncher(Window, world, TOH, snailbody->GetWorldCenter().x, snailbody->GetWorldCenter().y, 10, this));
        if(controlled){
            Weapons[aktWeapon]->MouseTargeting=true;
        }
        Weapons[1]->UnUse();
        Weapons[2]->UnUse();
        Weapons[3]->UnUse();

		Surface->SetAmmo(Weapons[aktWeapon]->ammunition);
        Surface->SetClip(Weapons[aktWeapon]->clip);
        //Weapons[0]->Use(snailbody->GetWorldCenter().x, snailbody->GetWorldCenter().y);
        gunjoint.Initialize(snailbody, Weapons[aktWeapon]->weaponbody, Weapons[aktWeapon]->weaponbody->GetWorldCenter());
        gunjoint.localAnchor1=b2Vec2(Weapons[aktWeapon]->jointX, Weapons[aktWeapon]->jointY);
        gunjoint.localAnchor2=b2Vec2(0.0f, 0.0f);
        world->CreateJoint(&gunjoint);
	}

	void Snail::FlipX(bool flip){
	    if(flip){
	        if(!hid){
                fliped=true;
                SnailSp.SetImage(snailImg[aktImg]);
                SnailSp.SetCenter(786-mx*2,444+my*2); //for fliped snail
                SnailSp.FlipX(fliped);
                Eye1Sp.FlipX(fliped);
                Eye2Sp.FlipX(fliped);

                float x=snailbody->GetPosition().x;
                float y=snailbody->GetPosition().y;
                float ang=snailbody->GetAngle();
                b2Vec2 linVel=snailbody->GetLinearVelocity();
                float angVel=snailbody->GetAngularVelocity();

                world->DestroyBody(snailbody);
                snailbodyDef.position.Set(x,y);
                snailbodyDef.angle=ang;
                snailbody = world->CreateBody(&snailbodyDef);
                bodyshapeDef.vertices[0].Set(-71+mx,0-my);
                bodyshapeDef.vertices[1].Set(0+mx,45-my);
                bodyshapeDef.vertices[2].Set(-71+mx,45-my);
                snailbody->CreateShape(&bodyshapeDef);
                houseshapeDef.localPosition.Set(-25+mx, 0-my);
                snailbody->CreateShape(&houseshapeDef);
                head1Def.localPosition.Set(-82+mx, -2-my);
                snailbody->CreateShape(&head1Def);
                head2Def.localPosition.Set(-73+mx, -18-my);
                snailbody->CreateShape(&head2Def);

                jd.body1 = snailbody;
                jd.body2 = eye1;
                jd.localAnchor1.Set(0.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[0].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye1;
                jd.localAnchor1.Set(-30.0f, 0.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[1].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye1;
                jd.localAnchor1.Set(-30.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[2].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye2;
                jd.localAnchor1.Set(0.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[3].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye2;
                jd.localAnchor1.Set(-30.0f, 0.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[4].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye2;
                jd.localAnchor1.Set(-30.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[5].Length();
                world->CreateJoint(&jd);

                snailbody->SetMassFromShapes();
                snailbody->SetUserData(&snaildata);

                snailbody->SetLinearVelocity(linVel);
                snailbody->SetAngularVelocity(angVel);

                gunjoint.Initialize(snailbody, Weapons[aktWeapon]->weaponbody, Weapons[aktWeapon]->weaponbody->GetWorldCenter());
                gunjoint.localAnchor1=b2Vec2(-Weapons[aktWeapon]->jointX, Weapons[aktWeapon]->jointY);
                gunjoint.localAnchor2=b2Vec2(0.0f, 0.0f);
                world->CreateJoint(&gunjoint);
                Weapons[aktWeapon]->FlipX(true);
            }else{
                fliped=true;
                SnailSp.SetImage(houseImg);
                SnailSp.SetCenter(786-mx*2,444+my*2); //for fliped snail
                SnailSp.FlipX(fliped);
                Eye1Sp.FlipX(fliped);
                Eye2Sp.FlipX(fliped);

                float x=snailbody->GetPosition().x;
                float y=snailbody->GetPosition().y;
                float ang=snailbody->GetAngle();
                b2Vec2 linVel=snailbody->GetLinearVelocity();
                float angVel=snailbody->GetAngularVelocity();

                world->DestroyBody(snailbody);
                snailbodyDef.position.Set(x,y);
                snailbodyDef.angle=ang;
                snailbody = world->CreateBody(&snailbodyDef);
                houseshapeDef.localPosition.Set(-25+mx, 0-my);
                snailbody->CreateShape(&houseshapeDef);

                jd.body1 = snailbody;
                jd.body2 = eye1;
                jd.localAnchor1.Set(0.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[0].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye1;
                jd.localAnchor1.Set(-30.0f, 0.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[1].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye1;
                jd.localAnchor1.Set(-30.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[2].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye2;
                jd.localAnchor1.Set(0.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[3].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye2;
                jd.localAnchor1.Set(-30.0f, 0.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[4].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye2;
                jd.localAnchor1.Set(-30.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[5].Length();
                world->CreateJoint(&jd);

                snailbody->SetMassFromShapes();
                snailbody->SetUserData(&snaildata);

                snailbody->SetLinearVelocity(linVel);
                snailbody->SetAngularVelocity(angVel);

                gunjoint.Initialize(snailbody, Weapons[aktWeapon]->weaponbody, Weapons[aktWeapon]->weaponbody->GetWorldCenter());
                gunjoint.localAnchor1=b2Vec2(-Weapons[aktWeapon]->jointX, Weapons[aktWeapon]->jointY);
                gunjoint.localAnchor2=b2Vec2(0.0f, 0.0f);
                world->CreateJoint(&gunjoint);
                Weapons[aktWeapon]->FlipX(true);
            }
	    }else{
	        if(!hid){
                fliped=false;
                SnailSp.SetImage(snailImg[aktImg]);
                SnailSp.SetCenter(654+mx*2,444+my*2);
                SnailSp.FlipX(fliped);
                Eye1Sp.FlipX(fliped);
                Eye2Sp.FlipX(fliped);

                float x=snailbody->GetPosition().x;
                float y=snailbody->GetPosition().y;
                float ang=snailbody->GetAngle();
                b2Vec2 linVel=snailbody->GetLinearVelocity();
                float angVel=snailbody->GetAngularVelocity();

                world->DestroyBody(snailbody);
                snailbodyDef.position.Set(x,y);
                snailbodyDef.angle=ang;
                snailbody = world->CreateBody(&snailbodyDef);
                bodyshapeDef.vertices[0].Set(71-mx,0-my);
                bodyshapeDef.vertices[1].Set(71-mx,45-my);
                bodyshapeDef.vertices[2].Set(0-mx,45-my);
                snailbody->CreateShape(&bodyshapeDef);
                houseshapeDef.localPosition.Set(25-mx, 0-my);
                snailbody->CreateShape(&houseshapeDef);
                head1Def.localPosition.Set(82-mx, -2-my);
                snailbody->CreateShape(&head1Def);
                head2Def.localPosition.Set(73-mx, -18-my);
                snailbody->CreateShape(&head2Def);

                jd.body1 = snailbody;
                jd.body2 = eye1;
                jd.localAnchor1.Set(0.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[0].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye1;
                jd.localAnchor1.Set(30.0f, 0.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[1].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye1;
                jd.localAnchor1.Set(30.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[2].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye2;
                jd.localAnchor1.Set(0.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[3].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye2;
                jd.localAnchor1.Set(30.0f, 0.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[4].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye2;
                jd.localAnchor1.Set(30.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[5].Length();
                world->CreateJoint(&jd);

                snailbody->SetMassFromShapes();
                snailbody->SetUserData(&snaildata);

                snailbody->SetLinearVelocity(linVel);
                snailbody->SetAngularVelocity(angVel);

                gunjoint.Initialize(snailbody, Weapons[aktWeapon]->weaponbody, Weapons[aktWeapon]->weaponbody->GetWorldCenter());
                gunjoint.localAnchor1=b2Vec2(Weapons[aktWeapon]->jointX, Weapons[aktWeapon]->jointY);
                gunjoint.localAnchor2=b2Vec2(0.0f, 0.0f);
                world->CreateJoint(&gunjoint);
                Weapons[aktWeapon]->FlipX(false);
	        }else{
	            fliped=false;
                SnailSp.SetImage(houseImg);
                SnailSp.SetCenter(654+mx*2,444+my*2);
                SnailSp.FlipX(fliped);
                Eye1Sp.FlipX(fliped);
                Eye2Sp.FlipX(fliped);

                float x=snailbody->GetPosition().x;
                float y=snailbody->GetPosition().y;
                float ang=snailbody->GetAngle();
                b2Vec2 linVel=snailbody->GetLinearVelocity();
                float angVel=snailbody->GetAngularVelocity();

                world->DestroyBody(snailbody);
                snailbodyDef.position.Set(x,y);
                snailbodyDef.angle=ang;
                snailbody = world->CreateBody(&snailbodyDef);
                houseshapeDef.localPosition.Set(25-mx, 0-my);
                snailbody->CreateShape(&houseshapeDef);

                jd.body1 = snailbody;
                jd.body2 = eye1;
                jd.localAnchor1.Set(0.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[0].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye1;
                jd.localAnchor1.Set(30.0f, 0.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[1].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye1;
                jd.localAnchor1.Set(30.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[2].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye2;
                jd.localAnchor1.Set(0.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[3].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye2;
                jd.localAnchor1.Set(30.0f, 0.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[4].Length();
                world->CreateJoint(&jd);

                jd.body1 = snailbody;
                jd.body2 = eye2;
                jd.localAnchor1.Set(30.0f, 30.0f);
                jd.localAnchor2.Set(0.0f, 0.0f);
                jd.length = d[5].Length();
                world->CreateJoint(&jd);

                snailbody->SetMassFromShapes();
                snailbody->SetUserData(&snaildata);

                snailbody->SetLinearVelocity(linVel);
                snailbody->SetAngularVelocity(angVel);

                gunjoint.Initialize(snailbody, Weapons[aktWeapon]->weaponbody, Weapons[aktWeapon]->weaponbody->GetWorldCenter());
                gunjoint.localAnchor1=b2Vec2(Weapons[aktWeapon]->jointX, Weapons[aktWeapon]->jointY);
                gunjoint.localAnchor2=b2Vec2(0.0f, 0.0f);
                world->CreateJoint(&gunjoint);
                Weapons[aktWeapon]->FlipX(false);
            }
        }
    }

    void Snail::Hide(bool hide){
	    if(hide){
            hid=true;
            FlipX(fliped);
        }else{
            hid=false;
            FlipX(fliped);
        }
    }

	void Snail::Show(){
        Window->Draw(SnailSp);
        Window->Draw(Eye1Sp);
        Window->Draw(Eye2Sp);
        if(alive)Weapons[aktWeapon]->Show();
    }

    void Snail::Die(){
        alive=false;
        aktImg=10;
        hid=false;
        float x=snailbody->GetPosition().x;
        float y=snailbody->GetPosition().y;
        float ang=snailbody->GetAngle();
        b2Vec2 linVel=snailbody->GetLinearVelocity();
        float angVel=snailbody->GetAngularVelocity();
        Weapons[aktWeapon]->UnUse();

        if(fliped){
                world->DestroyBody(snailbody);
                snailbodyDef.position.Set(x,y);
                snailbodyDef.angle=ang;
                snailbody = world->CreateBody(&snailbodyDef);
                bodyshapeDef.vertices[0].Set(-71+mx,0-my);
                bodyshapeDef.vertices[1].Set(0+mx,45-my);
                bodyshapeDef.vertices[2].Set(-71+mx,45-my);
                snailbody->CreateShape(&bodyshapeDef);
                houseshapeDef.localPosition.Set(-25+mx, 0-my);
                snailbody->CreateShape(&houseshapeDef);

                snailbody->SetMassFromShapes();
                snailbody->SetUserData(&snaildata);

                snailbody->SetLinearVelocity(linVel);
                snailbody->SetAngularVelocity(angVel);
	    }else{
                world->DestroyBody(snailbody);
                snailbodyDef.position.Set(x,y);
                snailbodyDef.angle=ang;
                snailbody = world->CreateBody(&snailbodyDef);
                bodyshapeDef.vertices[0].Set(71-mx,0-my);
                bodyshapeDef.vertices[1].Set(71-mx,45-my);
                bodyshapeDef.vertices[2].Set(0-mx,45-my);
                snailbody->CreateShape(&bodyshapeDef);
                houseshapeDef.localPosition.Set(25-mx, 0-my);
                snailbody->CreateShape(&houseshapeDef);

                snailbody->SetMassFromShapes();
                snailbody->SetUserData(&snaildata);

                snailbody->SetLinearVelocity(linVel);
                snailbody->SetAngularVelocity(angVel);
        }
    }

	void Snail::InputHandling(){
	    if(alive){
            if(controlled){
                timer+=Window->GetFrameTime();

				if(Window->GetInput().IsKeyDown(Key::LShift) && Stamina>50 && !turbo){/*turbo=true;Speed=60;*/UseTurbo();}


                if(Window->GetInput().IsKeyDown(Key::A)){
                    MoveLeft();
                }
                if(Window->GetInput().IsKeyDown(Key::D)){
                    MoveRight();
                }
                if(Window->GetInput().IsKeyDown(Key::W) && jump){
                    MoveUp();
                }
                if(Window->GetInput().IsKeyDown(Key::S)){
                    MoveDown();
                }
                if(Window->GetInput().IsKeyDown(Key::E)){
                    RollRight();
                }
                if(Window->GetInput().IsKeyDown(Key::Q)){
                    RollLeft();
                }
                if(Window->GetInput().IsKeyDown(Key::R)){
                    Eye1Attak();
                }
                if(Window->GetInput().IsKeyDown(Key::F)){
                    Eye2Attak();
                }
                if(Window->GetInput().IsKeyDown(Key::C)){
                    if(!hid){
                        Hide(true);
                    }
                }else{
                    if(hid){
                        Hide(false);
                    }
                }
                SetTargetPoint(Window->GetInput().GetMouseX(),Window->GetInput().GetMouseY());

                if(Window->GetInput().IsKeyDown(Key::G) && timer>grenadethrowspeed)
                {
                    ThrowGrenade();
                }

                if(Window->GetInput().IsMouseButtonDown(Mouse::Left)){
                    //Weapons[aktWeapon]->Shot();
                    Shot();
                }
             }
	    }
        SnailSp.SetPosition(snailbody->GetPosition().x,snailbody->GetPosition().y);
        SnailSp.SetRotation(snailbody->GetAngle()*-57.29577951308232);
        Eye1Sp.SetPosition(eye1->GetPosition().x,eye1->GetPosition().y);
        Eye2Sp.SetPosition(eye2->GetPosition().x,eye2->GetPosition().y);
        if(!turbo&&Stamina<100)Stamina+=0.1;
        if(turbo && Stamina<1 && Stamina>=0){turbo=false;Speed=30;}
        if(turbo){Stamina-=0.75;if(Stamina<0){Stamina=0;}}
        if(controlled)Surface->SetStamina(Stamina);
        if(alive){
            Weapons[aktWeapon]->SetTargetPoint(Mouse.x, Mouse.y);
            Weapons[aktWeapon]->InputHandling();
        }
	}

	void Snail::EventHandling(Event ev){
	    if(ev.Type == sf::Event::MouseWheelMoved && alive){
            if(ev.MouseWheel.Delta == 1 ){
				int wep=aktWeapon+1;
                ChangeWeapon(wep);
            }
            if(ev.MouseWheel.Delta == -1 ){
				int wep=aktWeapon-1;
				ChangeWeapon(wep);
            }
        }
    }

    void Snail::SetTargetPoint( int x, int y){
//		if((int)NewMouse.x!=(int)Mouse.x || (int)NewMouse.y!=(int)Mouse.y){
			if(!NET){
				tpce = new TargetPointChangeEvent(x,y);
			}
			Mouse = Window->ConvertCoords(x,y);
			if((Mouse.x>snailbody->GetPosition().x) && (fliped)){
				FlipX(false);
			}
			if((Mouse.x<snailbody->GetPosition().x) && (!fliped)){
				FlipX(true);
			}
	///	}

	}

    void Snail::MoveLeft(){
      if(!NET){
        MoveLeftEvent* mlev = new MoveLeftEvent();
        poo->AddMess(tpce);
        poo->AddMess(mlev);
      }
        snailbody->SetLinearVelocity(b2Vec2(-Speed,snailbody->GetLinearVelocity().y));
    }
    void Snail::MoveRight(){
      if(!NET){
        MoveRightEvent* mrev = new MoveRightEvent();
        poo->AddMess(tpce);
        poo->AddMess(mrev);
      }
        snailbody->SetLinearVelocity(b2Vec2(Speed,snailbody->GetLinearVelocity().y));
    }
    void Snail::MoveUp(){
      if(!NET){
        MoveUpEvent* muev = new MoveUpEvent();
        poo->AddMess(tpce);
        poo->AddMess(muev);
      }
        snailbody->SetLinearVelocity(b2Vec2(snailbody->GetLinearVelocity().x,-Speed-30));
    }
    void Snail::MoveDown(){
        if(!NET){
            MoveDownEvent* mdev = new MoveDownEvent();
            poo->AddMess(tpce);
            poo->AddMess(mdev);
        }
        snailbody->SetLinearVelocity(b2Vec2(0,snailbody->GetLinearVelocity().y+0.5));
    }
    void Snail::RollLeft(){
        if(!NET){
            RollLeftEvent* rlev = new RollLeftEvent();
            poo->AddMess(tpce);
            poo->AddMess(rlev);
        }
        snailbody->SetAngularVelocity(-0.5);
    }
    void Snail::RollRight(){
        if(!NET){
            RollRightEvent* rrev = new RollRightEvent();
            poo->AddMess(tpce);
            poo->AddMess(rrev);
        }
        snailbody->SetAngularVelocity(0.5);
    }
    void Snail::Eye1Attak(){
        if(fliped){
            eye1->SetLinearVelocity(b2Vec2(-200,-100));
        }else{
            eye1->SetLinearVelocity(b2Vec2(200,-100));
        }
    }
    void Snail::Eye2Attak(){
        if(fliped){
            eye2->SetLinearVelocity(b2Vec2(-200,-100));
        }else{
            eye2->SetLinearVelocity(b2Vec2(200,-100));
        }
    }
    void Snail::Shot(){
        if(!NET){
            ShotEvent* sev = new ShotEvent();
            poo->AddMess(tpce);
            poo->AddMess(sev);

        }
        Weapons[aktWeapon]->Shot();
        Surface->SetAmmo(Weapons[aktWeapon]->ammunition);
        Surface->SetClip(Weapons[aktWeapon]->clip);
    }
    void Snail::ThrowGrenade(){
		if(grenades>0){
			if(!NET){
				GranadeThrowedEvent* gtev = new GranadeThrowedEvent();
				poo->AddMess(tpce);
				poo->AddMess(gtev);
			}
			Grenade* g=new Grenade(Window, world, TOH, snailbody->GetPosition().x+10, snailbody->GetPosition().y-70, (Mouse.x-(snailbody->GetPosition().x+10))/2,(Mouse.y-(snailbody->GetPosition().y-70))/2);
			TOH->Add(g);
			timer=0;
		}
    }
    void Snail::UseTurbo(){
        turbo=true;
        Speed=60;
    }
    void Snail::ChangeWeapon(int WeaponNumber){
        if(WeaponNumber<0){
            WeaponNumber=Weapons.size()-1;
        }
        if(WeaponNumber>Weapons.size()-1){
            WeaponNumber=0;
        }
        Weapons[aktWeapon]->UnUse();
        aktWeapon=WeaponNumber;
        Weapons[aktWeapon]->Use(snailbody->GetWorldCenter().x, snailbody->GetWorldCenter().y);
        if(fliped){
            gunjoint.Initialize(snailbody, Weapons[aktWeapon]->weaponbody, Weapons[aktWeapon]->weaponbody->GetWorldCenter());
            gunjoint.localAnchor1=b2Vec2(-Weapons[aktWeapon]->jointX, Weapons[aktWeapon]->jointY);
            gunjoint.localAnchor2=b2Vec2(0.0f, 0.0f);
            world->CreateJoint(&gunjoint);
            Weapons[aktWeapon]->FlipX(true);
        }else{
            gunjoint.Initialize(snailbody, Weapons[aktWeapon]->weaponbody, Weapons[aktWeapon]->weaponbody->GetWorldCenter());
            gunjoint.localAnchor1=b2Vec2(Weapons[aktWeapon]->jointX, Weapons[aktWeapon]->jointY);
            gunjoint.localAnchor2=b2Vec2(0.0f, 0.0f);
            world->CreateJoint(&gunjoint);
            Weapons[aktWeapon]->FlipX(false);
        }
        //Weapons[aktWeapon]->SetTargetPoint(Mouse.x, Mouse.y);
        Surface->SetAmmo(Weapons[aktWeapon]->ammunition);
        Surface->SetClip(Weapons[aktWeapon]->clip);
    }

	void Snail::Damage(int damage){
	    if(alive){
            Health-=damage;
            if(Health<=0){Health=0;Die();}
            else if(Health<10)aktImg=9;
            else if(Health<20)aktImg=8;
            else if(Health<30)aktImg=7;
            else if(Health<40)aktImg=6;
            else if(Health<50)aktImg=5;
            else if(Health<60)aktImg=4;
            else if(Health<70)aktImg=3;
            else if(Health<80)aktImg=2;
            else if(Health<90)aktImg=1;
            //cout<<"Damaged: "<<damage<<"  Health: "<<Health<<endl;
            SnailSp.SetImage(snailImg[aktImg]);
			if(controlled)Surface->SetHealth(Health);
	    }
    }

  void Snail::Heal(int heal){
        Health+=heal;
        if(Health>100)Health=100;
        if(Health<10)aktImg=9;
        else if(Health<20)aktImg=8;
        else if(Health<30)aktImg=7;
        else if(Health<40)aktImg=6;
        else if(Health<50)aktImg=5;
        else if(Health<60)aktImg=4;
        else if(Health<70)aktImg=3;
        else if(Health<80)aktImg=2;
        else if(Health<90)aktImg=1;
        else if(Health>90)aktImg=0;
        SnailSp.SetImage(snailImg[aktImg]);
        if(controlled)Surface->SetHealth(Health);
    }

