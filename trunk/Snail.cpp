#include "Snail.hpp"

	Snail::Snail(RenderWindow* window, b2World* World, float PositionX, float PositionY){
	    Window=window;
	    world=World;

	    fliped=false;
        mx=41.5095;
        my=20.7499;

        snailbodyDef.position.Set(PositionX, PositionY);
        snailbody = world->CreateBody(&snailbodyDef);

        bodyshapeDef.vertexCount = 3;
        bodyshapeDef.vertices[0].Set(71-mx,0-my);
        bodyshapeDef.vertices[1].Set(71-mx,45-my);
        bodyshapeDef.vertices[2].Set(0-mx,45-my);
        bodyshapeDef.density = 30.0f;
        bodyshapeDef.friction = 1.0f;
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

        b2Vec2 p1, p2;
        jd.frequencyHz = 1.0f;
        jd.dampingRatio = 0.5f;

        eye1Def.position.Set(PositionX+95-mx, PositionY-73-my);
        eye1 = world->CreateBody(&eye1Def);
        e1.radius = 7.5f;
        e1.density = 1.0f;
        eye1->CreateShape(&e1);
        eye1->SetMassFromShapes();

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
        eye2->CreateShape(&e2);
        eye2->SetMassFromShapes();

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

        snailImg.LoadFromFile("csig1.6.png");
        SnailSp.SetImage(snailImg);
        SnailSp.Scale(0.5,0.5);
        SnailSp.SetCenter(654+mx*2,444+my*2);

        eye1Img.LoadFromFile("szem1.png");
        Eye1Sp.SetImage(eye1Img);
        Eye1Sp.Scale(0.5,0.5);
        Eye1Sp.SetCenter(20,18);
        eye2Img.LoadFromFile("szem2.png");
        Eye2Sp.SetImage(eye2Img);
        Eye2Sp.Scale(0.5,0.5);
        Eye2Sp.SetCenter(14,12);

        RifleGun=new Rifle(Window, world, snailbody->GetWorldCenter().x, snailbody->GetWorldCenter().y);
        gunjoint.Initialize(snailbody, RifleGun->riflebody, RifleGun->riflebody->GetWorldCenter());
        gunjoint.localAnchor1=b2Vec2(30.0f, 0.0f);
        gunjoint.localAnchor2=b2Vec2(0.0f, 0.0f);
        world->CreateJoint(&gunjoint);

        Granadebomb=new Granade(Window, world, snailbody->GetPosition().x+10, snailbody->GetPosition().y-70, 50,-50);
        Granadebomb->Deactivate();
	}

	void Snail::FlipX(bool flip){
	    if(flip){
            fliped=true;
            SnailSp.SetCenter(786-mx*2,444+my*2); //for fliped snail
            SnailSp.FlipX(fliped);
            Eye1Sp.FlipX(fliped);
            Eye2Sp.FlipX(fliped);
            cout<<"flip"<<endl;

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

            snailbody->SetLinearVelocity(linVel);
            snailbody->SetAngularVelocity(angVel);

            gunjoint.Initialize(snailbody, RifleGun->riflebody, RifleGun->riflebody->GetWorldCenter());
            gunjoint.localAnchor1=b2Vec2(-30.0f, 0.0f);
            gunjoint.localAnchor2=b2Vec2(0.0f, 0.0f);
            world->CreateJoint(&gunjoint);
            RifleGun->FlipX(true);
	    }else{
	        fliped=false;
            SnailSp.SetCenter(654+mx*2,444+my*2);
            SnailSp.FlipX(fliped);
            Eye1Sp.FlipX(fliped);
            Eye2Sp.FlipX(fliped);
            cout<<"unflip"<<endl;

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

            snailbody->SetLinearVelocity(linVel);
            snailbody->SetAngularVelocity(angVel);

            gunjoint.Initialize(snailbody, RifleGun->riflebody, RifleGun->riflebody->GetWorldCenter());
            gunjoint.localAnchor1=b2Vec2(30.0f, 0.0f);
            gunjoint.localAnchor2=b2Vec2(0.0f, 0.0f);
            world->CreateJoint(&gunjoint);
            RifleGun->FlipX(false);
        }
    }

	void Snail::Show(){
        Window->Draw(SnailSp);
        Window->Draw(Eye1Sp);
        Window->Draw(Eye2Sp);
        RifleGun->Show();
        Granadebomb->Show();
    }

	void Snail::InputHandling(Event ev){
	    RifleGun->InputHandling(ev);
        Granadebomb->InputHandling(ev);

	    if(Window->GetInput().IsKeyDown(Key::Left)){
            b2Vec2 force(-30,snailbody->GetLinearVelocity().y);
            snailbody->SetLinearVelocity(force);
        }
        if(Window->GetInput().IsKeyDown(Key::Right)){
            b2Vec2 force(30,snailbody->GetLinearVelocity().y);
            snailbody->SetLinearVelocity(force);
        }
        if(Window->GetInput().IsKeyDown(Key::Up)){
            b2Vec2 force(snailbody->GetLinearVelocity().x,-30);
            snailbody->SetLinearVelocity(force);
        }
        if(Window->GetInput().IsKeyDown(Key::Down)){
            snailbody->SetLinearVelocity(b2Vec2(snailbody->GetLinearVelocity().x,snailbody->GetLinearVelocity().y+0.5));
        }
        if(Window->GetInput().IsKeyDown(Key::E)){
            snailbody->SetAngularVelocity(0.5);
        }
        if(Window->GetInput().IsKeyDown(Key::Q)){
            snailbody->SetAngularVelocity(-0.5);
        }
        if(Window->GetInput().IsKeyDown(Key::R)){
            if(fliped){
                eye1->SetLinearVelocity(b2Vec2(-200,-100));
            }else{
                eye1->SetLinearVelocity(b2Vec2(200,-100));
            }
        }
        if(Window->GetInput().IsKeyDown(Key::F)){
            if(fliped){
                eye2->SetLinearVelocity(b2Vec2(-200,-100));
            }else{
                eye2->SetLinearVelocity(b2Vec2(200,-100));
            }
        }
        if(Window->GetInput().IsKeyDown(Key::G)){
            if(Granadebomb->active){
                Granadebomb->Deactivate();
            }
            Granadebomb=new Granade(Window, world, snailbody->GetPosition().x+10, snailbody->GetPosition().y-70, (Window->GetInput().GetMouseX()-(snailbody->GetPosition().x+10))/2,(Window->GetInput().GetMouseY()-(snailbody->GetPosition().y-70))/2);
        }
        if((Window->GetInput().GetMouseX()>snailbody->GetPosition().x) && (fliped)){
            FlipX(false);
        }
        if((Window->GetInput().GetMouseX()<snailbody->GetPosition().x) && (!fliped)){
            FlipX(true);
        }

        SnailSp.SetPosition(snailbody->GetPosition().x,snailbody->GetPosition().y);
        SnailSp.SetRotation(snailbody->GetAngle()*-57.29577951308232);
        Eye1Sp.SetPosition(eye1->GetPosition().x,eye1->GetPosition().y);
        Eye2Sp.SetPosition(eye2->GetPosition().x,eye2->GetPosition().y);
	}

