#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.hpp"

using namespace std;
using namespace sf;

class Application{

	public:
        RenderWindow* Window;
        Menu* menu;

        Application(int width, int height);

        void EventHandle();

};

#endif

