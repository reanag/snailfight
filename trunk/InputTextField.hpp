#ifndef INPUTTEXTFIELD_HPP
#define INPUTTEXTFIELD_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class sf::Sprite;
#include "SFML/Graphics/Sprite.hpp"
class Menu;
#include "Menu.hpp"

class InputTextField : public sf::Sprite{

	public:
        RenderWindow* Window;
        Menu* Parent;
        string label;
        bool infocus;
        Color* StandardColor;
        Color* InFocusColor;
        Font ButtonFont;
        String *Text;
        Image btnimage;
        float PosX;
        float PosY;
        int ipSize;

        void Setup(RenderWindow* window, Menu* parent, float PositionX, float PositionY, float SizeX, float SizeY, string Label);
        void SetTextPosition(float RelativePositionX, float RelativePositionY);
        void SetStandardColor(Color color);
        void SetInFocusColor(Color color);
        void EventHandle(Event ev);
        void SetLabel(string s);
        string GetLabel();

};

#endif
