#include "Stage2.hpp"


	Stage2::Stage2()
    {

        BGScale=2;
        Visiblepath=true;
        if (bacgroundImg.LoadFromFile("contents/Fantasy.jpg"))
	    {
	        BGWidth = bacgroundImg.GetWidth();      // megvizsgálom a háttér méretét
            BGHeight = bacgroundImg.GetHeight();
            BacgroundSp.SetImage(bacgroundImg);
            BacgroundSp.SetScale(BGScale,BGScale);
            cout << "Map original background size : " << BGWidth << " X " << BGHeight;  // kikerül konzolra a háttér eredeti mérete
            if (BGScale != 1)
            {
                BGWidth*=BGScale;
                BGHeight*=BGScale;
                cout << "\nMap is scaled (" << BGScale << "X), new size : " << BGWidth << " X " << BGHeight << "\n";// valamint ha átméretezem, akkor a megváltoztatott méret is
            }
            if (BGWidth<800) BGWidth=800;   //apró óvintézkedés, hogy ha túl kicsi lenne a méret, véletlenül se omoljunk össze
            if (BGHeight<600)
            {
                BacgroundSp.SetPosition(0,600-BGHeight);//ha a kép mérete nem éri el a 600at, akkor lejjebtolja, hogy a hézag ne alul hanem felül legyen, így még használható
                BGHeight=600;
            }
	    }
	    else
        {
	        BGWidth = 800;      // megvizsgálom a háttér méretét
            BGHeight = 600;
	    }
	    topImg.LoadFromFile("contents/Fantasy3.png");
	    topSp.SetImage(topImg);
	    topSp.SetScale(BGScale,BGScale);
    }

    void Stage2::MakeStage(RenderWindow* window, b2World* World, TempObjectHandler* toh)
    {
        Window=window;
	    world=World;
	    TOH=toh;

	    //bacgroundImg.LoadFromFile("contents/Fantasy_Soldiers_of_the_Future_014066_.jpg");
	    /*bacgroundImg.LoadFromFile("contents/Fantasy.jpg");
	    int BGWidth = bacgroundImg.GetWidth();      // megvizsgálom a háttér méretét
	    int BGHeight = bacgroundImg.GetHeight();
	    float BGScale = 1.6;
	    BacgroundSp.SetImage(bacgroundImg);
        BacgroundSp.SetScale(BGScale,BGScale);
	    cout << "Map original background size : " << BGWidth << " X " << BGHeight;
	    if (BGScale != 1)
	    {
	        BGWidth*=BGScale;
	        BGHeight*=BGScale;
	        cout << "\nMap is scaled (" << BGScale << "X), new size : " << BGWidth << " X " << BGHeight << "\n";
	    }*/

    //ground

        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(BGWidth/2, BGHeight);
        b2Body* groundBody = world->CreateBody(&groundBodyDef);
        b2PolygonDef groundShapeDef;
        groundShapeDef.SetAsBox(BGWidth/2, 5.0f);
        groundShapeDef.friction=1.1f;
        groundBody->CreateShape(&groundShapeDef);
        grounddata.label="GROUND";
        grounddata.object=this;
        groundBody->SetUserData(&grounddata);
        //grassImg.LoadFromFile("contents/d.bg_grass.png");
        //grassImg.LoadFromFile("contents/xmas_ground.png");
        GrassSp.SetImage(grassImg);
        GrassSp.SetPosition(-50,1760);
        //Ground=Shape::Rectangle(0, 0, 800, 10, Color(0,0,200));
        //Ground.SetCenter(400,5);
        //Ground.SetPosition(400,595);




    //wall 1
        b2BodyDef wall1BodyDef;
        wall1BodyDef.position.Set(5.0f, BGHeight/2);
        wall1Body = world->CreateBody(&wall1BodyDef);
        b2PolygonDef wall1ShapeDef;
        wall1ShapeDef.SetAsBox(5.0f, BGHeight/2);
        wall1Body->CreateShape(&wall1ShapeDef);
        wall1data.label="wall1";
        wall1data.object=this;
        wall1Body->SetUserData(&wall1data);
        Wall1=Shape::Rectangle(0, 0, wall1ShapeDef.vertices[2].x*2, wall1ShapeDef.vertices[2].y*2, Color(0,0,200));
        Wall1.SetCenter(wall1ShapeDef.vertices[2].x, wall1ShapeDef.vertices[2].y);
        Wall1.SetPosition(wall1BodyDef.position.x,wall1BodyDef.position.y);
    //wall 2
        b2BodyDef wall2BodyDef;
        wall2BodyDef.position.Set(BGWidth, BGHeight/2);
        wall2Body = world->CreateBody(&wall2BodyDef);
        b2PolygonDef wall2ShapeDef;
        wall2ShapeDef.SetAsBox(5.0f, BGHeight/2);
        wall2Body->CreateShape(&wall2ShapeDef);
        wall2data.label="wall2";
        wall2data.object=this;
        wall2Body->SetUserData(&wall2data);
        Wall2=Shape::Rectangle(0, 0, wall2ShapeDef.vertices[2].x*2, wall2ShapeDef.vertices[2].y*2, Color(0,0,200));
        Wall2.SetCenter(wall2ShapeDef.vertices[2].x, wall2ShapeDef.vertices[2].y);
        Wall2.SetPosition(wall2BodyDef.position.x,wall2BodyDef.position.y);
    //roof
        b2BodyDef roofBodyDef;
        roofBodyDef.position.Set(BGWidth/2, 5.0f);
        roofBody = world->CreateBody(&roofBodyDef);
        b2PolygonDef roofShapeDef;
        roofShapeDef.SetAsBox(BGWidth/2, 5.0f);
        roofBody->CreateShape(&roofShapeDef);
        roofdata.label="roof";
        roofdata.object=this;
        roofBody->SetUserData(&roofdata);
        Roof=Shape::Rectangle(0, 0, roofShapeDef.vertices[2].x*2, roofShapeDef.vertices[2].y*2, Color(0,0,200));
        Roof.SetCenter(roofShapeDef.vertices[2].x, roofShapeDef.vertices[2].y);
        Roof.SetPosition(roofBodyDef.position.x,roofBodyDef.position.y);


    //path 01
        b2BodyDef path01BodyDef;
        path01BodyDef.position.Set(RelativeWidth(20), RelativeHeight(83));
        path01BodyDef.angle=(20*0.017453);
        path01Body = world->CreateBody(&path01BodyDef);
        b2PolygonDef path01ShapeDef;
        path01ShapeDef.SetAsBox(RelativeWidth(5), 5.0f);
        path01Body->CreateShape(&path01ShapeDef);
        path01data.label="path01";
        path01data.object=this;
        path01Body->SetUserData(&path01data);
        Path01=Shape::Rectangle(0, 0, path01ShapeDef.vertices[2].x*2, path01ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path01.SetCenter(path01ShapeDef.vertices[2].x, path01ShapeDef.vertices[2].y);
        Path01.SetPosition(path01BodyDef.position.x,path01BodyDef.position.y);
        Path01.SetRotation(-path01BodyDef.angle*57.29577);
    //path02
        b2BodyDef path02BodyDef;
        path02BodyDef.position.Set(RelativeWidth(13), RelativeHeight(77));
        path02BodyDef.angle=(30*0.017453);
        path02Body = world->CreateBody(&path02BodyDef);
        b2PolygonDef path02ShapeDef;
        path02ShapeDef.SetAsBox(RelativeWidth(5), 5.0f);
        path02Body->CreateShape(&path02ShapeDef);
        path02data.label="path02";
        path02data.object=this;
        path02Body->SetUserData(&path02data);
        Path02=Shape::Rectangle(0, 0, path02ShapeDef.vertices[2].x*2, path02ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path02.SetCenter(path02ShapeDef.vertices[2].x, path02ShapeDef.vertices[2].y);
        Path02.SetPosition(path02BodyDef.position.x,path02BodyDef.position.y);
        Path02.SetRotation(-path02BodyDef.angle*57.29577);
    //path03
        b2BodyDef path03BodyDef;
        path03BodyDef.position.Set(RelativeWidth(25), RelativeHeight(84));
        path03BodyDef.angle=(-10*0.017453);
        path03Body = world->CreateBody(&path03BodyDef);
        b2PolygonDef path03ShapeDef;
        path03ShapeDef.SetAsBox(RelativeWidth(2.5), 5.0f);
        path03Body->CreateShape(&path03ShapeDef);
        path03data.label="path03";
        path03data.object=this;
        path03Body->SetUserData(&path03data);
        Path03=Shape::Rectangle(0, 0, path03ShapeDef.vertices[2].x*2, path03ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path03.SetCenter(path03ShapeDef.vertices[2].x, path03ShapeDef.vertices[2].y);
        Path03.SetPosition(path03BodyDef.position.x,path03BodyDef.position.y);
        Path03.SetRotation(-path03BodyDef.angle*57.29577);
    //path04
        b2BodyDef path04BodyDef;
        path04BodyDef.position.Set(RelativeWidth(27.5), RelativeHeight(81));
        path04BodyDef.angle=(-50*0.017453);
        path04Body = world->CreateBody(&path04BodyDef);
        b2PolygonDef path04ShapeDef;
        path04ShapeDef.SetAsBox(RelativeWidth(1.7), 5.0f);
        path04Body->CreateShape(&path04ShapeDef);
        path04data.label="path04";
        path04data.object=this;
        path04Body->SetUserData(&path04data);
        Path04=Shape::Rectangle(0, 0, path04ShapeDef.vertices[2].x*2, path04ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path04.SetCenter(path04ShapeDef.vertices[2].x, path04ShapeDef.vertices[2].y);
        Path04.SetPosition(path04BodyDef.position.x,path04BodyDef.position.y);
        Path04.SetRotation(-path04BodyDef.angle*57.29577);
    //path5
        b2BodyDef path05BodyDef;
        path05BodyDef.position.Set(RelativeWidth(29.4), RelativeHeight(77.9));
        path05BodyDef.angle=(-32*0.017453);
        path05Body = world->CreateBody(&path05BodyDef);
        b2PolygonDef path05ShapeDef;
        path05ShapeDef.SetAsBox(RelativeWidth(1), 5.0f);
        path05Body->CreateShape(&path05ShapeDef);
        path05data.label="path05";
        path05data.object=this;
        path05Body->SetUserData(&path05data);
        Path05=Shape::Rectangle(0, 0, path05ShapeDef.vertices[2].x*2, path05ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path05.SetCenter(path05ShapeDef.vertices[2].x, path05ShapeDef.vertices[2].y);
        Path05.SetPosition(path05BodyDef.position.x,path05BodyDef.position.y);
        Path05.SetRotation(-path05BodyDef.angle*57.29577);
    //path6
        b2BodyDef path06BodyDef;
        path06BodyDef.position.Set(RelativeWidth(31.6), RelativeHeight(76.6));
        path06BodyDef.angle=(-7*0.017453);
        path06Body = world->CreateBody(&path06BodyDef);
        b2PolygonDef path06ShapeDef;
        path06ShapeDef.SetAsBox(RelativeWidth(1.4), 5.0f);
        path06Body->CreateShape(&path06ShapeDef);
        path06data.label="path06";
        path06data.object=this;
        path06Body->SetUserData(&path06data);
        Path06=Shape::Rectangle(0, 0, path06ShapeDef.vertices[2].x*2, path06ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path06.SetCenter(path06ShapeDef.vertices[2].x, path06ShapeDef.vertices[2].y);
        Path06.SetPosition(path06BodyDef.position.x,path06BodyDef.position.y);
        Path06.SetRotation(-path06BodyDef.angle*57.29577);
    //path7
        b2BodyDef path07BodyDef;
        path07BodyDef.position.Set(RelativeWidth(34.3), RelativeHeight(76.74));
        path07BodyDef.angle=(10*0.017453);
        path07Body = world->CreateBody(&path07BodyDef);
        b2PolygonDef path07ShapeDef;
        path07ShapeDef.SetAsBox(RelativeWidth(1.4), 5.0f);
        path07Body->CreateShape(&path07ShapeDef);
        path07data.label="path07";
        path07data.object=this;
        path07Body->SetUserData(&path07data);
        Path07=Shape::Rectangle(0, 0, path07ShapeDef.vertices[2].x*2, path07ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path07.SetCenter(path07ShapeDef.vertices[2].x, path07ShapeDef.vertices[2].y);
        Path07.SetPosition(path07BodyDef.position.x,path07BodyDef.position.y);
        Path07.SetRotation(-path07BodyDef.angle*57.29577);
    //path8
        b2BodyDef path08BodyDef;
        path08BodyDef.position.Set(RelativeWidth(39), RelativeHeight(76));
        path08BodyDef.angle=(-10*0.017453);
        path08Body = world->CreateBody(&path08BodyDef);
        b2PolygonDef path08ShapeDef;
        path08ShapeDef.SetAsBox(RelativeWidth(4), 5.0f);
        path08Body->CreateShape(&path08ShapeDef);
        path08data.label="path08";
        path08data.object=this;
        path08Body->SetUserData(&path08data);
        Path08=Shape::Rectangle(0, 0, path08ShapeDef.vertices[2].x*2, path08ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path08.SetCenter(path08ShapeDef.vertices[2].x, path08ShapeDef.vertices[2].y);
        Path08.SetPosition(path08BodyDef.position.x,path08BodyDef.position.y);
        Path08.SetRotation(-path08BodyDef.angle*57.29577);
    //path9
        b2BodyDef path09BodyDef;
        path09BodyDef.position.Set(RelativeWidth(54), RelativeHeight(74.74));
        //path09BodyDef.angle=(0*0.017453);
        path09Body = world->CreateBody(&path09BodyDef);
        b2PolygonDef path09ShapeDef;
        path09ShapeDef.SetAsBox(RelativeWidth(11), 5.0f);
        path09Body->CreateShape(&path09ShapeDef);
        path09data.label="path09";
        path09data.object=this;
        path09Body->SetUserData(&path09data);
        Path09=Shape::Rectangle(0, 0, path09ShapeDef.vertices[2].x*2, path09ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path09.SetCenter(path09ShapeDef.vertices[2].x, path09ShapeDef.vertices[2].y);
        Path09.SetPosition(path09BodyDef.position.x,path09BodyDef.position.y);
       // path09.SetRotation(-path09BodyDef.angle*57.29577);
    //path10  stair
        b2BodyDef path10BodyDef;
        path10BodyDef.position.Set(RelativeWidth(69.5), RelativeHeight(68.9));
        path10BodyDef.angle=(5*0.017453);
        path10Body = world->CreateBody(&path10BodyDef);
        b2PolygonDef path10ShapeDef;
        path10ShapeDef.SetAsBox(RelativeWidth(1.5), 5.0f);
        path10Body->CreateShape(&path10ShapeDef);
        path10data.label="path10";
        path10data.object=this;
        path10Body->SetUserData(&path10data);
        Path10=Shape::Rectangle(0, 0, path10ShapeDef.vertices[2].x*2, path10ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path10.SetCenter(path10ShapeDef.vertices[2].x, path10ShapeDef.vertices[2].y);
        Path10.SetPosition(path10BodyDef.position.x,path10BodyDef.position.y);
        Path10.SetRotation(-path10BodyDef.angle*57.29577);
    //path11
        b2BodyDef path11BodyDef;
        path11BodyDef.position.Set(RelativeWidth(82), RelativeHeight(63));
        //path11BodyDef.angle=(0*0.017453);
        path11Body = world->CreateBody(&path11BodyDef);
        b2PolygonDef path11ShapeDef;
        path11ShapeDef.SetAsBox(RelativeWidth(7.8), 5.0f);
        path11Body->CreateShape(&path11ShapeDef);
        path11data.label="path11";
        path11data.object=this;
        path11Body->SetUserData(&path11data);
        Path11=Shape::Rectangle(0, 0, path11ShapeDef.vertices[2].x*2, path11ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path11.SetCenter(path11ShapeDef.vertices[2].x, path11ShapeDef.vertices[2].y);
        Path11.SetPosition(path11BodyDef.position.x,path11BodyDef.position.y);
       // path11.SetRotation(-path11BodyDef.angle*57.29577);
    //path12   dock
        b2BodyDef path12BodyDef;
        path12BodyDef.position.Set(RelativeWidth(72), RelativeHeight(76.7));
        path12BodyDef.angle=(9*0.017453);
        path12Body = world->CreateBody(&path12BodyDef);
        b2PolygonDef path12ShapeDef;
        path12ShapeDef.SetAsBox(RelativeWidth(7), 5.0f);
        path12Body->CreateShape(&path12ShapeDef);
        path12data.label="path12";
        path12data.object=this;
        path12Body->SetUserData(&path12data);
        Path12=Shape::Rectangle(0, 0, path12ShapeDef.vertices[2].x*2, path12ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path12.SetCenter(path12ShapeDef.vertices[2].x, path12ShapeDef.vertices[2].y);
        Path12.SetPosition(path12BodyDef.position.x,path12BodyDef.position.y);
        Path12.SetRotation(-path12BodyDef.angle*57.29577);
    //path13 barrel
        b2BodyDef path13BodyDef;
        path13BodyDef.position.Set(RelativeWidth(8.2), RelativeHeight(70));
        path13BodyDef.angle=(85*0.017453);
        path13Body = world->CreateBody(&path13BodyDef);
        b2PolygonDef path13ShapeDef;
        path13ShapeDef.SetAsBox(RelativeWidth(2.3), 5.0f);
        path13Body->CreateShape(&path13ShapeDef);
        path13data.label="path13";
        path13data.object=this;
        path13Body->SetUserData(&path13data);
        Path13=Shape::Rectangle(0, 0, path13ShapeDef.vertices[2].x*2, path13ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path13.SetCenter(path13ShapeDef.vertices[2].x, path13ShapeDef.vertices[2].y);
        Path13.SetPosition(path13BodyDef.position.x,path13BodyDef.position.y);
        Path13.SetRotation(-path13BodyDef.angle*57.29577);
    //path14barrel
        b2BodyDef path14BodyDef;
        path14BodyDef.position.Set(RelativeWidth(8.5), RelativeHeight(71.8));
        path14BodyDef.angle=(50*0.017453);
        path14Body = world->CreateBody(&path14BodyDef);
        b2PolygonDef path14ShapeDef;
        path14ShapeDef.SetAsBox(RelativeWidth(1), 5.0f);
        path14Body->CreateShape(&path14ShapeDef);
        path14data.label="path14";
        path14data.object=this;
        path14Body->SetUserData(&path14data);
        Path14=Shape::Rectangle(0, 0, path14ShapeDef.vertices[2].x*2, path14ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path14.SetCenter(path14ShapeDef.vertices[2].x, path14ShapeDef.vertices[2].y);
        Path14.SetPosition(path14BodyDef.position.x,path14BodyDef.position.y);
        Path14.SetRotation(-path14BodyDef.angle*57.29577);
    //path15 barrel
        b2BodyDef path15BodyDef;
        path15BodyDef.position.Set(RelativeWidth(7), RelativeHeight(65.5));
        path15BodyDef.angle=(5*0.017453);
        path15Body = world->CreateBody(&path15BodyDef);
        b2PolygonDef path15ShapeDef;
        path15ShapeDef.SetAsBox(RelativeWidth(1), 5.0f);
        path15Body->CreateShape(&path15ShapeDef);
        path15data.label="path15";
        path15data.object=this;
        path15Body->SetUserData(&path15data);
        Path15=Shape::Rectangle(0, 0, path15ShapeDef.vertices[2].x*2, path15ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path15.SetCenter(path15ShapeDef.vertices[2].x, path15ShapeDef.vertices[2].y);
        Path15.SetPosition(path15BodyDef.position.x,path15BodyDef.position.y);
        Path15.SetRotation(-path15BodyDef.angle*57.29577);
    //path16barrel
        b2BodyDef path16BodyDef;
        path16BodyDef.position.Set(RelativeWidth(6), RelativeHeight(62.5));
        path16BodyDef.angle=(85*0.017453);
        path16Body = world->CreateBody(&path16BodyDef);
        b2PolygonDef path16ShapeDef;
        path16ShapeDef.SetAsBox(RelativeWidth(2), 5.0f);
        path16Body->CreateShape(&path16ShapeDef);
        path16data.label="path16";
        path16data.object=this;
        path16Body->SetUserData(&path16data);
        Path16=Shape::Rectangle(0, 0, path16ShapeDef.vertices[2].x*2, path16ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path16.SetCenter(path16ShapeDef.vertices[2].x, path16ShapeDef.vertices[2].y);
        Path16.SetPosition(path16BodyDef.position.x,path16BodyDef.position.y);
        Path16.SetRotation(-path16BodyDef.angle*57.29577);
    //path17barrel
        b2BodyDef path17BodyDef;
        path17BodyDef.position.Set(RelativeWidth(5.9), RelativeHeight(58));
        path17BodyDef.angle=(-85*0.017453);
        path17Body = world->CreateBody(&path17BodyDef);
        b2PolygonDef path17ShapeDef;
        path17ShapeDef.SetAsBox(RelativeWidth(1), 5.0f);
        path17Body->CreateShape(&path17ShapeDef);
        path17data.label="path17";
        path17data.object=this;
        path17Body->SetUserData(&path17data);
        Path17=Shape::Rectangle(0, 0, path17ShapeDef.vertices[2].x*2, path17ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path17.SetCenter(path17ShapeDef.vertices[2].x, path17ShapeDef.vertices[2].y);
        Path17.SetPosition(path17BodyDef.position.x,path17BodyDef.position.y);
        Path17.SetRotation(-path17BodyDef.angle*57.29577);
    //path18barrel
        b2BodyDef path18BodyDef;
        path18BodyDef.position.Set(RelativeWidth(3), RelativeHeight(54.5));
        path18BodyDef.angle=(15*0.017453);
        path18Body = world->CreateBody(&path18BodyDef);
        b2PolygonDef path18ShapeDef;
        path18ShapeDef.SetAsBox(RelativeWidth(3), 5.0f);
        path18Body->CreateShape(&path18ShapeDef);
        path18data.label="path18";
        path18data.object=this;
        path18Body->SetUserData(&path18data);
        Path18=Shape::Rectangle(0, 0, path18ShapeDef.vertices[2].x*2, path18ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path18.SetCenter(path18ShapeDef.vertices[2].x, path18ShapeDef.vertices[2].y);
        Path18.SetPosition(path18BodyDef.position.x,path18BodyDef.position.y);
        Path18.SetRotation(-path18BodyDef.angle*57.29577);
    //path19barrel indoor
        b2BodyDef path19BodyDef;
        path19BodyDef.position.Set(RelativeWidth(16), RelativeHeight(55.5));
        path19BodyDef.angle=(-35*0.017453);
        path19Body = world->CreateBody(&path19BodyDef);
        b2PolygonDef path19ShapeDef;
        path19ShapeDef.SetAsBox(RelativeWidth(4.5), 5.0f);
        path19Body->CreateShape(&path19ShapeDef);
        path19data.label="path19";
        path19data.object=this;
        path19Body->SetUserData(&path19data);
        Path19=Shape::Rectangle(0, 0, path19ShapeDef.vertices[2].x*2, path19ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path19.SetCenter(path19ShapeDef.vertices[2].x, path19ShapeDef.vertices[2].y);
        Path19.SetPosition(path19BodyDef.position.x,path19BodyDef.position.y);
        Path19.SetRotation(-path19BodyDef.angle*57.29577);
    //path20barrel indoor
        b2BodyDef path20BodyDef;
        path20BodyDef.position.Set(RelativeWidth(34.9), RelativeHeight(49.9));
        path20BodyDef.angle=(-2*0.017453);
        path20Body = world->CreateBody(&path20BodyDef);
        b2PolygonDef path20ShapeDef;
        path20ShapeDef.SetAsBox(RelativeWidth(15.25), 5.0f);
        path20Body->CreateShape(&path20ShapeDef);
        path20data.label="path20";
        path20data.object=this;
        path20Body->SetUserData(&path20data);
        Path20=Shape::Rectangle(0, 0, path20ShapeDef.vertices[2].x*2, path20ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path20.SetCenter(path20ShapeDef.vertices[2].x, path20ShapeDef.vertices[2].y);
        Path20.SetPosition(path20BodyDef.position.x,path20BodyDef.position.y);
        Path20.SetRotation(-path20BodyDef.angle*57.29577);
    //path21 upper tunnel
        b2BodyDef path21BodyDef;
        path21BodyDef.position.Set(RelativeWidth(7.2), RelativeHeight(44));
        //path21BodyDef.angle=(15*0.017453);
        path21Body = world->CreateBody(&path21BodyDef);
        b2PolygonDef path21ShapeDef;
        path21ShapeDef.SetAsBox(RelativeWidth(1.5), 5.0f);
        path21Body->CreateShape(&path21ShapeDef);
        path21data.label="path21";
        path21data.object=this;
        path21Body->SetUserData(&path21data);
        Path21=Shape::Rectangle(0, 0, path21ShapeDef.vertices[2].x*2, path21ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path21.SetCenter(path21ShapeDef.vertices[2].x, path21ShapeDef.vertices[2].y);
        Path21.SetPosition(path21BodyDef.position.x,path21BodyDef.position.y);
        //Path21.SetRotation(-path21BodyDef.angle*57.29577);
    //path22barrel upper tunnel
        b2BodyDef path22BodyDef;
        path22BodyDef.position.Set(RelativeWidth(23.5), RelativeHeight(39));
        path22BodyDef.angle=(-10.5*0.017453);
        path22Body = world->CreateBody(&path22BodyDef);
        b2PolygonDef path22ShapeDef;
        path22ShapeDef.SetAsBox(RelativeWidth(15.25), 5.0f);
        path22Body->CreateShape(&path22ShapeDef);
        path22data.label="path22";
        path22data.object=this;
        path22Body->SetUserData(&path22data);
        Path22=Shape::Rectangle(0, 0, path22ShapeDef.vertices[2].x*2, path22ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path22.SetCenter(path22ShapeDef.vertices[2].x, path22ShapeDef.vertices[2].y);
        Path22.SetPosition(path22BodyDef.position.x,path22BodyDef.position.y);
        Path22.SetRotation(-path22BodyDef.angle*57.29577);
    //path23  kerítés
        b2BodyDef path23BodyDef;
        path23BodyDef.position.Set(RelativeWidth(69.5), RelativeHeight(55.5));
        path23BodyDef.angle=(-5*0.017453);
        path23Body = world->CreateBody(&path23BodyDef);
        b2PolygonDef path23ShapeDef;
        path23ShapeDef.SetAsBox(RelativeWidth(2), 5.0f);
        path23Body->CreateShape(&path23ShapeDef);
        path23data.label="path23";
        path23data.object=this;
        path23Body->SetUserData(&path23data);
        Path23=Shape::Rectangle(0, 0, path23ShapeDef.vertices[2].x*2, path23ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path23.SetCenter(path23ShapeDef.vertices[2].x, path23ShapeDef.vertices[2].y);
        Path23.SetPosition(path23BodyDef.position.x,path23BodyDef.position.y);
        Path23.SetRotation(-path23BodyDef.angle*57.29577);
    //path24  kerítés
        b2BodyDef path24BodyDef;
        path24BodyDef.position.Set(RelativeWidth(62.2), RelativeHeight(47));
        path24BodyDef.angle=(25*0.017453);
        path24Body = world->CreateBody(&path24BodyDef);
        b2PolygonDef path24ShapeDef;
        path24ShapeDef.SetAsBox(RelativeWidth(2), 5.0f);
        path24Body->CreateShape(&path24ShapeDef);
        path24data.label="path24";
        path24data.object=this;
        path24Body->SetUserData(&path24data);
        Path24=Shape::Rectangle(0, 0, path24ShapeDef.vertices[2].x*2, path24ShapeDef.vertices[2].y*2, Color(0,200,200));
        Path24.SetCenter(path24ShapeDef.vertices[2].x, path24ShapeDef.vertices[2].y);
        Path24.SetPosition(path24BodyDef.position.x,path24BodyDef.position.y);
        Path24.SetRotation(-path24BodyDef.angle*57.29577);



    //balcony01
        b2BodyDef balcony01BodyDef;
        balcony01BodyDef.position.Set(RelativeWidth(46.1), RelativeHeight(33.737));
        balcony01BodyDef.angle=(-1*0.017453);
        balcony01Body = world->CreateBody(&balcony01BodyDef);
        b2PolygonDef balcony01ShapeDef;
        balcony01ShapeDef.SetAsBox(RelativeWidth(7.5), 5.0f);
        balcony01Body->CreateShape(&balcony01ShapeDef);
        balcony01data.label="balcony01";
        balcony01data.object=this;
        balcony01Body->SetUserData(&balcony01data);
        Balcony01=Shape::Rectangle(0, 0, balcony01ShapeDef.vertices[2].x*2, balcony01ShapeDef.vertices[2].y*2, Color(0,200,200));
        Balcony01.SetCenter(balcony01ShapeDef.vertices[2].x, balcony01ShapeDef.vertices[2].y);
        Balcony01.SetPosition(balcony01BodyDef.position.x,balcony01BodyDef.position.y);
        Balcony01.SetRotation(-balcony01BodyDef.angle*57.29577);
    //balcony02
        b2BodyDef balcony02BodyDef;
        balcony02BodyDef.position.Set(RelativeWidth(53.61), RelativeHeight(32.2));
        balcony02BodyDef.angle=(-85*0.017453);
        balcony02Body = world->CreateBody(&balcony02BodyDef);
        b2PolygonDef balcony02ShapeDef;
        balcony02ShapeDef.SetAsBox(RelativeWidth(0.25), 5.0f);
        balcony02Body->CreateShape(&balcony02ShapeDef);
        balcony02data.label="balcony02";
        balcony02data.object=this;
        balcony02Body->SetUserData(&balcony02data);
        Balcony02=Shape::Rectangle(0, 0, balcony02ShapeDef.vertices[2].x*2, balcony02ShapeDef.vertices[2].y*2, Color(0,200,200));
        Balcony02.SetCenter(balcony02ShapeDef.vertices[2].x, balcony02ShapeDef.vertices[2].y);
        Balcony02.SetPosition(balcony02BodyDef.position.x,balcony02BodyDef.position.y);
        Balcony02.SetRotation(-balcony02BodyDef.angle*57.29577);
    //balcony03 roof
        b2BodyDef balcony03BodyDef;
        balcony03BodyDef.position.Set(RelativeWidth(49), RelativeHeight(19.5));
        balcony03BodyDef.angle=(-47.5*0.017453);
        balcony03Body = world->CreateBody(&balcony03BodyDef);
        b2PolygonDef balcony03ShapeDef;
        balcony03ShapeDef.SetAsBox(RelativeWidth(3), 5.0f);
        balcony03Body->CreateShape(&balcony03ShapeDef);
        balcony03data.label="balcony03";
        balcony03data.object=this;
        balcony03Body->SetUserData(&balcony03data);
        Balcony03=Shape::Rectangle(0, 0, balcony03ShapeDef.vertices[2].x*2, balcony03ShapeDef.vertices[2].y*2, Color(0,200,200));
        Balcony03.SetCenter(balcony03ShapeDef.vertices[2].x, balcony03ShapeDef.vertices[2].y);
        Balcony03.SetPosition(balcony03BodyDef.position.x,balcony03BodyDef.position.y);
        Balcony03.SetRotation(-balcony03BodyDef.angle*57.29577);
    //balcony04 roof
        b2BodyDef balcony04BodyDef;
        balcony04BodyDef.position.Set(RelativeWidth(52.9), RelativeHeight(20));
        balcony04BodyDef.angle=(57.5*0.017453);
        balcony04Body = world->CreateBody(&balcony04BodyDef);
        b2PolygonDef balcony04ShapeDef;
        balcony04ShapeDef.SetAsBox(RelativeWidth(3), 5.0f);
        balcony04Body->CreateShape(&balcony04ShapeDef);
        balcony04data.label="balcony04";
        balcony04data.object=this;
        balcony04Body->SetUserData(&balcony04data);
        Balcony04=Shape::Rectangle(0, 0, balcony04ShapeDef.vertices[2].x*2, balcony04ShapeDef.vertices[2].y*2, Color(0,200,200));
        Balcony04.SetCenter(balcony04ShapeDef.vertices[2].x, balcony04ShapeDef.vertices[2].y);
        Balcony04.SetPosition(balcony04BodyDef.position.x,balcony04BodyDef.position.y);
        Balcony04.SetRotation(-balcony04BodyDef.angle*57.29577);
    //balcony05 windmill
        b2BodyDef balcony05BodyDef;
        balcony05BodyDef.position.Set(RelativeWidth(40.9), RelativeHeight(26));
        balcony05BodyDef.angle=(-10*0.017453);
        balcony05Body = world->CreateBody(&balcony05BodyDef);
        b2PolygonDef balcony05ShapeDef;
        balcony05ShapeDef.SetAsBox(RelativeWidth(2.4), 3.0f);
        balcony05Body->CreateShape(&balcony05ShapeDef);
        balcony05data.label="balcony05";
        balcony05data.object=this;
        balcony05Body->SetUserData(&balcony05data);
        Balcony05=Shape::Rectangle(0, 0, balcony05ShapeDef.vertices[2].x*2, balcony05ShapeDef.vertices[2].y*2, Color(0,200,200));
        Balcony05.SetCenter(balcony05ShapeDef.vertices[2].x, balcony05ShapeDef.vertices[2].y);
        Balcony05.SetPosition(balcony05BodyDef.position.x,balcony05BodyDef.position.y);
        Balcony05.SetRotation(-balcony05BodyDef.angle*57.29577);




    //tree201
        b2BodyDef tree201BodyDef;
        tree201BodyDef.position.Set(RelativeWidth(92), RelativeHeight(60.5));
        tree201BodyDef.angle=(-30*0.017453);
        tree201Body = world->CreateBody(&tree201BodyDef);
        b2PolygonDef tree201ShapeDef;
        tree201ShapeDef.SetAsBox(RelativeWidth(3), 5.0f);
        tree201Body->CreateShape(&tree201ShapeDef);
        tree201data.label="tree201";
        tree201data.object=this;
        tree201Body->SetUserData(&tree201data);
        Tree201=Shape::Rectangle(0, 0, tree201ShapeDef.vertices[2].x*2, tree201ShapeDef.vertices[2].y*2, Color(0,200,200));
        Tree201.SetCenter(tree201ShapeDef.vertices[2].x, tree201ShapeDef.vertices[2].y);
        Tree201.SetPosition(tree201BodyDef.position.x,tree201BodyDef.position.y);
        Tree201.SetRotation(-tree201BodyDef.angle*57.29577);
    //tree202
        b2BodyDef tree202BodyDef;
        tree202BodyDef.position.Set(RelativeWidth(89.5), RelativeHeight(62.1));
        tree202BodyDef.angle=(-15*0.017453);
        tree202Body = world->CreateBody(&tree202BodyDef);
        b2PolygonDef tree202ShapeDef;
        tree202ShapeDef.SetAsBox(RelativeWidth(2), 5.0f);
        tree202Body->CreateShape(&tree202ShapeDef);
        tree202data.label="tree202";
        tree202data.object=this;
        tree202Body->SetUserData(&tree202data);
        Tree202=Shape::Rectangle(0, 0, tree202ShapeDef.vertices[2].x*2, tree202ShapeDef.vertices[2].y*2, Color(0,200,200));
        Tree202.SetCenter(tree202ShapeDef.vertices[2].x, tree202ShapeDef.vertices[2].y);
        Tree202.SetPosition(tree202BodyDef.position.x,tree202BodyDef.position.y);
        Tree202.SetRotation(-tree202BodyDef.angle*57.29577);
    //tree203
        b2BodyDef tree203BodyDef;
        tree203BodyDef.position.Set(RelativeWidth(96.2), RelativeHeight(48));
        tree203BodyDef.angle=(-71.5*0.017453);
        tree203Body = world->CreateBody(&tree203BodyDef);
        b2PolygonDef tree203ShapeDef;
        tree203ShapeDef.SetAsBox(RelativeWidth(6), 5.0f);
        tree203Body->CreateShape(&tree203ShapeDef);
        tree203data.label="tree203";
        tree203data.object=this;
        tree203Body->SetUserData(&tree203data);
        Tree203=Shape::Rectangle(0, 0, tree203ShapeDef.vertices[2].x*2, tree203ShapeDef.vertices[2].y*2, Color(0,200,200));
        Tree203.SetCenter(tree203ShapeDef.vertices[2].x, tree203ShapeDef.vertices[2].y);
        Tree203.SetPosition(tree203BodyDef.position.x,tree203BodyDef.position.y);
        Tree203.SetRotation(-tree203BodyDef.angle*57.29577);
    //tree204
        b2BodyDef tree204BodyDef;
        tree204BodyDef.position.Set(RelativeWidth(99), RelativeHeight(22));
        tree204BodyDef.angle=(-84*0.017453);
        tree204Body = world->CreateBody(&tree204BodyDef);
        b2PolygonDef tree204ShapeDef;
        tree204ShapeDef.SetAsBox(RelativeWidth(10), 5.0f);
        tree204Body->CreateShape(&tree204ShapeDef);
        tree204data.label="tree204";
        tree204data.object=this;
        tree204Body->SetUserData(&tree204data);
        Tree204=Shape::Rectangle(0, 0, tree204ShapeDef.vertices[2].x*2, tree204ShapeDef.vertices[2].y*2, Color(0,200,200));
        Tree204.SetCenter(tree204ShapeDef.vertices[2].x, tree204ShapeDef.vertices[2].y);
        Tree204.SetPosition(tree204BodyDef.position.x,tree204BodyDef.position.y);
        Tree204.SetRotation(-tree204BodyDef.angle*57.29577);
    //tree205
        b2BodyDef tree205BodyDef;
        tree205BodyDef.position.Set(RelativeWidth(85.5), RelativeHeight(28.7));
        tree205BodyDef.angle=(12*0.017453);
        tree205Body = world->CreateBody(&tree205BodyDef);
        b2PolygonDef tree205ShapeDef;
        tree205ShapeDef.SetAsBox(RelativeWidth(6.7), 5.0f);
        tree205Body->CreateShape(&tree205ShapeDef);
        tree205data.label="tree205";
        tree205data.object=this;
        tree205Body->SetUserData(&tree205data);
        Tree205=Shape::Rectangle(0, 0, tree205ShapeDef.vertices[2].x*2, tree205ShapeDef.vertices[2].y*2, Color(0,200,200));
        Tree205.SetCenter(tree205ShapeDef.vertices[2].x, tree205ShapeDef.vertices[2].y);
        Tree205.SetPosition(tree205BodyDef.position.x,tree205BodyDef.position.y);
        Tree205.SetRotation(-tree205BodyDef.angle*57.29577);
    //tree206
        b2BodyDef tree206BodyDef;
        tree206BodyDef.position.Set(RelativeWidth(90.5), RelativeHeight(10));
        tree206BodyDef.angle=(10*0.017453);
        tree206Body = world->CreateBody(&tree206BodyDef);
        b2PolygonDef tree206ShapeDef;
        tree206ShapeDef.SetAsBox(RelativeWidth(3), 5.0f);
        tree206Body->CreateShape(&tree206ShapeDef);
        tree206data.label="tree206";
        tree206data.object=this;
        tree206Body->SetUserData(&tree206data);
        Tree206=Shape::Rectangle(0, 0, tree206ShapeDef.vertices[2].x*2, tree206ShapeDef.vertices[2].y*2, Color(0,200,200));
        Tree206.SetCenter(tree206ShapeDef.vertices[2].x, tree206ShapeDef.vertices[2].y);
        Tree206.SetPosition(tree206BodyDef.position.x,tree206BodyDef.position.y);
        Tree206.SetRotation(-tree206BodyDef.angle*57.29577);

        /*treeImg.LoadFromFile("contents/fákk1.png");
        TreeSp.SetImage(treeImg);
        TreeSp.SetCenter(220,850);
        TreeSp.SetScale(2,2);
        TreeSp.SetPosition(5,1800);*/

	}

	void Stage2::Show(){
	    //Window->Draw(Ground);
	    Window->Draw(BacgroundSp);
        Window->Draw(Wall1);
        Window->Draw(Wall2);
        Window->Draw(Roof);
        if (Visiblepath==true)
        {
            Window->Draw(Path01);
            Window->Draw(Path02);
            Window->Draw(Path03);
            Window->Draw(Path04);
            Window->Draw(Path05);
            Window->Draw(Path06);
            Window->Draw(Path07);
            Window->Draw(Path08);
            Window->Draw(Path09);
            Window->Draw(Path10);
            Window->Draw(Path11);
            Window->Draw(Path12);
            Window->Draw(Path13);
            Window->Draw(Path14);
            Window->Draw(Path15);
            Window->Draw(Path16);
            Window->Draw(Path17);
            Window->Draw(Path18);
            Window->Draw(Path19);
            Window->Draw(Path20);
            Window->Draw(Path21);
            Window->Draw(Path22);
            Window->Draw(Path23);
            Window->Draw(Path24);

            Window->Draw(Balcony01);
            Window->Draw(Balcony02);
            Window->Draw(Balcony03);
            Window->Draw(Balcony04);
            Window->Draw(Balcony05);

            Window->Draw(Tree201);
            Window->Draw(Tree202);
            Window->Draw(Tree203);
            Window->Draw(Tree204);
            Window->Draw(Tree205);
            Window->Draw(Tree206);
        }
        Window->Draw(GrassSp);
        GrassSp.SetPosition(-40,1765);
    }

	void Stage2::ShowAfter(){
	    //Window->Draw(TreeSp);
        Window->Draw(GrassSp);
        GrassSp.SetPosition(-50,1760);
        Window->Draw(topSp);
    }

	void Stage2::InputHandling(/*Event ev*/){

	}

