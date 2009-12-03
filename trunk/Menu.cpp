#include "Menu.hpp"

	Menu::Menu(RenderWindow* window){
	    Window=window;
	    IpIsSet = false;
	    AmIClient = false;
	    AmIServer = false;
        csiga_b.LoadFromFile("contents/csiguszbody.png");
        Csiga_b.SetImage(csiga_b);
        Csiga_b.SetPosition(0+100,-5+30);
        csiga_l.LoadFromFile("contents/csiga_l.png");
        Csiga_l.SetImage(csiga_l);
        Csiga_l.SetCenter(8,80);
        Csiga_l.SetPosition(385+8+100,350+80+30);
        csiga_r.LoadFromFile("contents/csiga_r.png");
        Csiga_r.SetImage(csiga_r);
        Csiga_r.SetPosition(277+100,445+30);
        gun.LoadFromFile("contents/menugun.png");
        Gun.SetImage(gun);
        Gun.SetCenter(36,195);
        Gun.SetPosition(270+36+100,299+195+30);
        laser.LoadFromFile("contents/laser2.png");
        Laser.SetImage(laser);
        Laser.SetCenter(-65,71);
        Laser.SetPosition(Gun.GetPosition().x,Gun.GetPosition().y);
        ShowIPTextEditor = false;

        Gun.SetRotation(9);
        Laser.SetRotation(56);
        Csiga_l.SetRotation(31);

        NewGame=new Button();
        NewGame->Setup(Window,this,Window->GetWidth()-250,30,200,20,"New Game");
        NewGame->SetTextPosition(50,-3);
        Connect=new Button();
        Connect->Setup(Window,this,Window->GetWidth()-250,70,200,20,"Connect");
        Connect->SetTextPosition(55,-3);
        HighScores=new Button();
        HighScores->Setup(Window,this,Window->GetWidth()-250,110,200,20,"High Scores");
        HighScores->SetTextPosition(35,-3);
        Description=new Button();
        Description->Setup(Window,this,Window->GetWidth()-250,150,200,20,"Description");
        Description->SetTextPosition(33,-3);
        Exit=new Button();
        Exit->Setup(Window,this,Window->GetWidth()-250,190,200,20,"Exit");
        Exit->SetTextPosition(77,-3);

        MenuFont.LoadFromFile("contents/Army.ttf");
//ANDIKA RÉSZ:
        ConnectionText= new String("Network setting\n\n Create server or join", MenuFont,20);
        ConnectionText->SetPosition(40, 40);
        ShowConnection=false;
        ServerButton = new Button();
        ServerButton->Setup(Window, this, Window->GetWidth()-760,150,200, 30, "Create server");
        ServerButton->SetTextPosition(20, 0);
        ClientButton = new Button();
        ClientButton->Setup(Window, this, Window->GetWidth()-500,150,200, 30, "Join server");
        ClientButton->SetTextPosition(40, 0);
        ServerText = new InputTextField();
        ServerText->Setup(Window, this, Window->GetWidth()-700,100,300, 30, "IP:");

//ANDIKA RÉSZ END
        players=new vector<player>();
        player p;
        ifstream file("contents/Scores.txt");
        while(!file.eof()){
            file >> p.name;
            file >> p.score;
            players->push_back(p);
        }
        ScoresText= new String("...",MenuFont,20);
        ScoresText->SetPosition(150, 40);
        ShowHighScores=false;

        DescriptionText= new String("A játék célja hogy kellemes hangulatban\naranyos kis erdei állatkák bõrébe bújva\n       halomragyilkolásszuk egymást a\n     barátokkal vagy a családtagokkal.\n\n                              fegyverbe!!!",MenuFont,20);
        DescriptionText->SetPosition(40, 40);
        ShowDescription=false;

        Window2=new RenderWindow(VideoMode(200,100,32), "Exit???...",Style::Close);
        Window2->Show(false);
        ShowExitWindow=false;
        ExitText= new String("     Are you sure,\nyou want to quit?",MenuFont,20);
        ExitText->SetPosition(5, 10);
        yes=new Button();
        yes->Setup(Window2,this,20,65,60,20,"yes");
        yes->SetTextPosition(10,-3);
        yes->SetStandardColor(Color(0,0,200));
        //yes->SetInFocusColor(Color(0,0,255));
        no=new Button();
        no->Setup(Window2,this,120,65,60,20,"no");
        no->SetTextPosition(15,-3);
        no->SetStandardColor(Color(0,0,200));
        no->SetInFocusColor(Color(0,0,255));

        Buffer.LoadFromFile("contents/290673_03___Redemption.wav");
        MenuSound.SetBuffer(Buffer);
        MenuSound.SetVolume(100);
        MenuSound.Play();

	}

	void Menu::Show(){
        Window->Draw(Csiga_b);
        Window->Draw(Gun);
        Window->Draw(Csiga_l);
        Window->Draw(Csiga_r);
        Window->Draw(*NewGame);
        Window->Draw(*NewGame->Text);
        Window->Draw(*Connect);
        Window->Draw(*Connect->Text);
        Window->Draw(*HighScores);
        Window->Draw(*HighScores->Text);
        Window->Draw(*Description);
        Window->Draw(*Description->Text);
        Window->Draw(*Exit);
        Window->Draw(*Exit->Text);
        Window->Draw(Laser);
//ANDIKA RÉSZ:
        if(ShowConnection){
            Window->Draw(*ConnectionText);
            Window->Draw(*ServerButton);
            Window->Draw(*ServerButton->Text);
            Window->Draw(*ClientButton);
            Window->Draw(*ClientButton->Text);

        }
        if(ShowIPTextEditor){
            ConnectionText= new String("\n   Type the IP of the server: \n\n  You can write a dot useing the D character", MenuFont,20);
            Window->Draw(*ConnectionText);
            Window->Draw(*ClientButton);
            Window->Draw(*ClientButton->Text);
            Window->Draw(*ServerText);
            Window->Draw(*ServerText->Text);
        }
//ANDIKA END
        if(ShowHighScores){
            Window->Draw(*ScoresText);
        }
        if(ShowDescription){
            Window->Draw(*DescriptionText);
        }
        if(ShowExitWindow){
            Event Event;
            while (Window2->GetEvent(Event)){
                yes->EventHandle(Event);
                no->EventHandle(Event);
                if (Event.Type == Event::Closed){
                    ShowExitWindow=false;
                    Window2->Show(false);
                }

                if (Event.Type == Event::KeyPressed){

                    if (Event.Key.Code == Key::Escape){
                        ShowExitWindow=false;
                        Window2->Show(false);
                    }
                }
            }

            Window2->Clear();
            Window2->Draw(*ExitText);
            Window2->Draw(*yes);
            Window2->Draw(*yes->Text);
            Window2->Draw(*no);
            Window2->Draw(*no->Text);
            Window2->Display();
        }
    }

	void Menu::EventHandle(Event ev){

	    NewGame->EventHandle(ev);
	    Connect->EventHandle(ev);
        HighScores->EventHandle(ev);
        Description->EventHandle(ev);
        Exit->EventHandle(ev);

//ANDIKA RÉSZ:

    ServerButton->EventHandle(ev);

    ClientButton->EventHandle(ev);
    ServerText->EventHandle(ev);

//ANDIKA RÉSZ END

        if(Window->GetInput().GetMouseX() > Window->GetWidth()-260 && Window->GetInput().GetMouseY() < 230){
            float tav_x=Window->GetInput().GetMouseX()-Gun.GetPosition().x;
            float tav_y=Window->GetInput().GetMouseY()-Gun.GetPosition().y+33;
            if(tav_x<0){
                Gun.FlipX(true);
            }else{
                Gun.FlipX(false);
            }
            float lim=((-atan(tav_y/tav_x))*56);
            if(lim>38 && lim<72){
                Gun.SetRotation((-atan(tav_y/tav_x)*55.215)-47);
                Laser.SetRotation((-atan(tav_y/tav_x)*55.215));
                Csiga_l.SetRotation((-atan(tav_y/tav_x)*170)-140);
                float tav=pow(pow(Window->GetInput().GetMouseX()-Laser.GetPosition().x,2)+pow(Window->GetInput().GetMouseY()-Laser.GetPosition().y,2),(float)0.5);
                Laser.Resize((tav/1.001)-30,Laser.GetSize().y);
            }
        }
	}
    void Menu::SetIP(string from){
      ip = from.substr(3,from.size());
    }
    string Menu::GetIP(){
        return ip;
    }
	void Menu::Action(string& from){

        if(ShowConnection)ShowConnection=false;
        if(ShowHighScores)ShowHighScores=false;
        if(ShowDescription)ShowDescription=false;
        if(ShowExitWindow){
            ShowExitWindow=false;
            Window2->Show(false);
        }
        if(from=="New Game"){
            MenuSound.Pause();
            MyGame=new Game(Window);
            MyGame->InGame=true;
            MyGame->GameLoop();
            MenuSound.Play();
        }
        if(from=="Connect"){
            ShowConnection=true;
        }
        if(from=="High Scores"){
            string highscores="   * high scores *\n\n";
            player p;
            for(unsigned int i=0;i<players->size();i++){
                p=players->at(i);
                highscores.append(p.name);
                highscores.append("..............");
                stringstream ss;
                ss << p.score;
                string c_string(ss.str());
                highscores.append(c_string);
                highscores.append("\n");
            }
            //cout<<highscores<<endl;
            ScoresText->SetText(highscores);
            ShowHighScores=true;
        }
        if(from=="Description"){
            ShowDescription=true;
        }
        if(from=="Exit"){
            Window2->Show(true);
            ShowExitWindow=true;
        }
        if(from=="yes"){
            Window->Close();
        }
        if(from=="no"){
            Window2->Show(false);
            ShowExitWindow=false;
        }

//ANDIKA RÉSZ:
        if(from=="Join server"){
           if(AmIServer||AmIServer){
            cout<<"Error: you are already server or client is running!";
            return;
           }
            ShowIPTextEditor = true;
            cout<<"join server";
            if(ShowIPTextEditor&&IpIsSet){

               p = &ip;
               Thread* ThreadCreateClient = new Thread(&ThreadCreateClientFunc, p);
               ThreadCreateClient->Launch();
               AmIClient = true;
            }
        }

        if(from =="Create server"){
            if(AmIClient||AmIServer){
                cout<<"Error: you are already client or server is already running!";
                return;
            }
            cout<<"create server";

           Thread* ThreadCreateServer = new Thread(&ThreadCreateServerFunc);
           ThreadCreateServer->Launch();
           AmIServer = true;

            }
//ANDIKA RÉSZ END
}
//Andika szálkezel:

void Menu::ThreadCreateServerFunc(void* UserData){
     ServerTCP Server = ServerTCP();
     Server.Run();
}

void Menu::ThreadCreateClientFunc(void* UserData){
    string* Object = static_cast<string*>(UserData);
    string s = *Object;
    ClientTCP Client = ClientTCP(s);
    Client.Run();
}
