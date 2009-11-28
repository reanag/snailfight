#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class sf::Sprite;
#include "SFML/Graphics/Sprite.hpp"
class Menu;
#include "Menu.hpp"

class Button : public sf::Sprite{

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

        void Setup(RenderWindow* window, Menu* parent, float PositionX, float PositionY, float SizeX, float SizeY, string Label);
        void SetTextPosition(float RelativePositionX, float RelativePositionY);
        void SetStandardColor(Color color);
        void SetInFocusColor(Color color);
        void EventHandle(Event ev);

};

#endif
