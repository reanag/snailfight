#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include <sstream>
#include "Button.hpp"
#include "Game.hpp"
#include "Server.cpp"
#include "Cliens.cpp"
#include "InputTextField.hpp"

class InputTextField;
class Button;
using namespace std;
using namespace sf;

class Menu{

	public:
        struct player{
            string name;
            int score;
        };

        RenderWindow* Window;
        Image csiga_b;
        Sprite Csiga_b;
        Image csiga_l;
        Sprite Csiga_l;
        Image csiga_r;
        Sprite Csiga_r;
        Image gun;
        Sprite Gun;
        Image laser;
        Sprite Laser;

        Button* NewGame;
        Button* Connect;
        Button* HighScores;
        Button* Description;
        Button* Exit;

        Button* ServerButton;
        Button* ClientButton;
        InputTextField* ServerText;

        Font MenuFont;

        bool ShowConnection;
        String* ConnectionText;

        bool ShowHighScores;
        vector<player>* players;
        String* ScoresText;

        bool ShowDescription;
        String* DescriptionText;

        bool ShowExitWindow;
        RenderWindow* Window2;
        String* ExitText;
        Button* yes;
        Button* no;

        SoundBuffer Buffer;
        Sound MenuSound;

        Game* MyGame;
        String* LoadingText;

        //vector<Shape> snow;

        Menu(RenderWindow* window);

        bool ShowIPTextEditor;
        bool IpIsSet;
        bool AmIServer;
        bool AmIClient;

        string ip;
        string* p;
        void Show();
        void EventHandle(Event ev);
        void Action(string& from);
        void SetIP(string from);
        string GetIP();
        void static ThreadCreateServerFunc(void* UserData);
        void static ThreadCreateClientFunc(void* UserData);
        //void GenerateSnow();
        //void SnowUpdate();

};

#endif
