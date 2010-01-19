#ifndef GAMESURFACE_HPP
#define GAMESURFACE_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;
using namespace sf;

class GameSurface{
	public:
        RenderWindow* Window;

        Image barImg;
        Image baroutlineImg;
        Sprite LifebarSp;
        Sprite LifebarOutlineSp;
        Sprite StaminabarSp;
        Sprite StaminabarOutlineSp;

        Font SurfaceFont;
        String* HealthText;
        String* StaminaText;
        String* AmmoText;
        String* ClipText;

        Vector2f koord;

        GameSurface(RenderWindow* window);

        void Show();
        void InputHandling();
        void SetHealth(int health);
        void SetStamina(int stamina);
        void SetAmmo(int ammo);
        void SetClip(int clip);
};

#endif
