#include "Snail.hpp"

	Snail::Snail(RenderWindow* window, b2World* World, TempObjectHandler* toh, float PositionX, float PositionY, bool Controlled, Pool* p, Menu* m){
	    poo = p;
	    menu = m;
	    Window=window;
	    world=World;
	    TOH=toh;

	    Health=100;
	    Stamina=100;
	    Speed=30;
	    alive=true;
	    turbo=false;

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
        //snailImg.LoadFromFile("contents/xmas_csig1.6.png");
        //houseImg.LoadFromFile("contents/xmas_csig1.6.house.png");
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
        Weapons.push_back(new RocketLauncher(Window, world, TOH, snailbody->GetWorldCenter().x, snailbody->GetWorldCenter().y, 200));
        if(controlled){
            Weapons[aktWeapon]->MouseTargeting=true;
        }
        Weapons[1]->UnUse();
        Weapons[2]->UnUse();
        Weapons[3]->UnUse();
        //Weapons[0]->Use(snailbody->GetWorldCenter().x, snailbody->GetWorldCenter().y);
        /*RifleGun=new Rifle2(Window, world, TOH, snailbody->GetWorldCenter().x, snailbody->GetWorldCenter().y);
        RifleGun->MouseTargeting=true;
        gunjoint.Initialize(snailbody, RifleGun->weaponbody, RifleGun->weaponbody->GetWorldCenter());*/
        gunjoint.Initialize(snailbody, Weapons[aktWeapon]->weaponbody, Weapons[aktWeapon]->weaponbody->GetWorldCenter());
        gunjoint.localAnchor1=b2Vec2(Weapons[aktWeapon]->jointX, Weapons[aktWeapon]->jointY);
        gunjoint.localAnchor2=b2Vec2(0.0f, 0.0f);
        world->CreateJoint(&gunjoint);

        //lightImg.LoadFromFile("contents/night-light.png");
        //LightSp.SetImage(lightImg);
        //LightSp.SetCenter(1000,782);
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
                //LightSp.FlipX(true);
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
                //LightSp.FlipX(false);
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
        //if(controlled){
        //    Window->Draw(LightSp);
        //}
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
            Weapons[aktWeapon]->InputHandling();
            if(controlled){
                timer+=Window->GetFrameTime();

                if(!turbo&&Stamina<100)Stamina+=0.1;
                if(Window->GetInput().IsKeyDown(Key::LShift) && Stamina>50 && !turbo){/*turbo=true;Speed=60;*/UseTurbo();}
                if(turbo && Stamina<1 && Stamina>=0){turbo=false;Speed=30;}
                if(turbo){Stamina-=0.75;if(Stamina<0){Stamina=0;}}

                if(Window->GetInput().IsKeyDown(Key::A)){
                    //snailbody->SetLinearVelocity(b2Vec2(-Speed,snailbody->GetLinearVelocity().y));
                    MoveLeft();
                }
                if(Window->GetInput().IsKeyDown(Key::D)){
                    //snailbody->SetLinearVelocity(b2Vec2(Speed,snailbody->GetLinearVelocity().y));
                    MoveRight();
                }
                if(Window->GetInput().IsKeyDown(Key::W) && jump){
                    //snailbody->SetLinearVelocity(b2Vec2(snailbody->GetLinearVelocity().x,-Speed-30));
                    MoveUp();
                }
                if(Window->GetInput().IsKeyDown(Key::S)){
                    //snailbody->SetLinearVelocity(b2Vec2(/*snailbody->GetLinearVelocity().x*/0,snailbody->GetLinearVelocity().y+0.5));
                    MoveDown();
                }
                if(Window->GetInput().IsKeyDown(Key::E)){
                    //snailbody->SetAngularVelocity(0.5);
                    RollRight();
                }
                if(Window->GetInput().IsKeyDown(Key::Q)){
                    //snailbody->SetAngularVelocity(-0.5);
                    RollLeft();
                }
                if(Window->GetInput().IsKeyDown(Key::R)){
                    /*if(fliped){
                        eye1->SetLinearVelocity(b2Vec2(-200,-100));
                    }else{
                        eye1->SetLinearVelocity(b2Vec2(200,-100));
                    }*/
                    Eye1Attak();
                }
                if(Window->GetInput().IsKeyDown(Key::F)){
                    /*if(fliped){
                        eye2->SetLinearVelocity(b2Vec2(-200,-100));
                    }else{
                        eye2->SetLinearVelocity(b2Vec2(200,-100));
                    }*/
                    Eye2Attak();
                }
                //cout<<abs(int(snailbody->GetAngle()*-57.29577951308232)%360)<<endl;
                if(Window->GetInput().IsKeyDown(Key::C)){
                    if(!hid){
                        Hide(true);
                    }
                }else{
                    if(hid){
                        Hide(false);
                    }
                }

                //Mouse = Window->ConvertCoords(Window->GetInput().GetMouseX(),Window->GetInput().GetMouseY());
                SetTargetPoint(Window->GetInput().GetMouseX(),Window->GetInput().GetMouseY());

                if(Window->GetInput().IsKeyDown(Key::G) && timer>grenadethrowspeed){
                    /*Grenade* g=new Grenade(Window, world, TOH, snailbody->GetPosition().x+10, snailbody->GetPosition().y-70, (Mouse.x-(snailbody->GetPosition().x+10))/2,(Mouse.y-(snailbody->GetPosition().y-70))/2);
                    TOH->Add(g);
                    timer=0;*/
                    ThrowGrenade();
                }

                /*if(Window->GetInput().IsKeyDown(Key::X)){
                    Damage(1);
                }

                if(Window->GetInput().IsKeyDown(Key::H)){
                    Heal(1);
                }*/

                /*if((Mouse.x>snailbody->GetPosition().x) && (fliped)){
                    FlipX(false);
                }
                if((Mouse.x<snailbody->GetPosition().x) && (!fliped)){
                    FlipX(true);
                }*/

                if(Window->GetInput().IsMouseButtonDown(Mouse::Left)){
                    //Weapons[aktWeapon]->Shot();
                    Shot();
                }

                /*
                if(ev.Type == Event::MouseButtonPressed){
                    if(ev.Key.Code == 0){

                    }
                }*/

            }
	    }
        SnailSp.SetPosition(snailbody->GetPosition().x,snailbody->GetPosition().y);
        SnailSp.SetRotation(snailbody->GetAngle()*-57.29577951308232);
        Eye1Sp.SetPosition(eye1->GetPosition().x,eye1->GetPosition().y);
        Eye2Sp.SetPosition(eye2->GetPosition().x,eye2->GetPosition().y);
        //LightSp.SetPosition(RifleGun->weaponbody->GetPosition().x,RifleGun->weaponbody->GetPosition().y);
        //LightSp.SetRotation(RifleGun->weaponbody->GetAngle()*-57.29577951308232);
	}

	void Snail::EventHandling(Event ev){
	    if(ev.Type == sf::Event::MouseWheelMoved && alive){
            if(ev.MouseWheel.Delta == 1 ){
                Weapons[aktWeapon]->UnUse();
                aktWeapon++;
                if(aktWeapon>Weapons.size()-1){
                    aktWeapon=0;
                }
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
            }
            if(ev.MouseWheel.Delta == -1 ){
                Weapons[aktWeapon]->UnUse();
                aktWeapon--;
                if(aktWeapon<0){
                    aktWeapon=Weapons.size()-1;
                }
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
            }
        }
    }

    void Snail::SetTargetPoint(int x, int y){
     //TargetPointChangeEvent létrehozása, ha megváltozott a TargetPoint
        TargetPointChangeEvent* nev = new TargetPointChangeEvent(x,y);
     //Pool MessagesToSend vektorához hozzáadni (static vector, csak a menün keresztül lehet)
         poo->AddMess(nev);

        Mouse = Window->ConvertCoords(x,y);
        if((Mouse.x>snailbody->GetPosition().x) && (fliped)){
            FlipX(false);
        }
        if((Mouse.x<snailbody->GetPosition().x) && (!fliped)){
            FlipX(true);
        }
    }

    void Snail::MoveLeft(){
        MoveLeftEvent* mlev = new MoveLeftEvent();
        poo->AddMess(mlev);
        snailbody->SetLinearVelocity(b2Vec2(-Speed,snailbody->GetLinearVelocity().y));
    }
    void Snail::MoveRight(){
        snailbody->SetLinearVelocity(b2Vec2(Speed,snailbody->GetLinearVelocity().y));
    }
    void Snail::MoveUp(){
        snailbody->SetLinearVelocity(b2Vec2(snailbody->GetLinearVelocity().x,-Speed-30));
    }
    void Snail::MoveDown(){
        snailbody->SetLinearVelocity(b2Vec2(0,snailbody->GetLinearVelocity().y+0.5));
    }
    void Snail::RollLeft(){
        snailbody->SetAngularVelocity(-0.5);
    }
    void Snail::RollRight(){
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
        Weapons[aktWeapon]->Shot();
    }
    void Snail::ThrowGrenade(){
        Grenade* g=new Grenade(Window, world, TOH, snailbody->GetPosition().x+10, snailbody->GetPosition().y-70, (Mouse.x-(snailbody->GetPosition().x+10))/2,(Mouse.y-(snailbody->GetPosition().y-70))/2);
        TOH->Add(g);
        timer=0;
    }
    void Snail::UseTurbo(){
        turbo=true;
        Speed=60;
    }
    void Snail::ChangeWeapon(int WeaponNumber){
     //   poo->AddMess(WeaponChangeEvent e(WeaponNumber));
        if(WeaponNumber>0 && WeaponNumber<Weapons.size()){
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
        }
    }

	void Snail::Damage(int damage){
	    if(alive){
            Health-=damage;
            if(Health<=0)Die();
            else if(Health<10)aktImg=9;
            else if(Health<20)aktImg=8;
            else if(Health<30)aktImg=7;
            else if(Health<40)aktImg=6;
            else if(Health<50)aktImg=5;
            else if(Health<60)aktImg=4;
            else if(Health<70)aktImg=3;
            else if(Health<80)aktImg=2;
            else if(Health<90)aktImg=1;
            cout<<"Damaged: "<<damage<<"  Health: "<<Health<<endl;
            SnailSp.SetImage(snailImg[aktImg]);
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
        //cout<<aktImg<<" "<<Health<<" "<<alive<<endl;
        SnailSp.SetImage(snailImg[aktImg]);
    }

