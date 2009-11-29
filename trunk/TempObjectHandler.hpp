#ifndef TEMPOBJECTHANDLER_HPP
#define TEMPOBJECTHANDLER_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Grenade.hpp"
#include "Bullet.hpp"

using namespace std;
using namespace sf;

class Grenade;
class Bullet;

class TempObjectHandler{

	public:
        vector<Grenade* > Grenades;
        vector<Bullet* > Bullets;

        Image grenadeImg;
        Image detonation[3];
        SoundBuffer GranadeSoundBuffer;

        TempObjectHandler();

        void ShowBullets();
        void ShowGrenades();
        void InputHandling(Event ev);
        void Add(Grenade* grenade);
        void Remove(Grenade* grenade);
        void Add(Bullet* bullet);
        void Remove(Bullet* bullet);

};

#endif
