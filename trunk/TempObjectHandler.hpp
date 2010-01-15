#ifndef TEMPOBJECTHANDLER_HPP
#define TEMPOBJECTHANDLER_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Grenade.hpp"
#include "Bullet.hpp"
#include "Rocket.hpp"
#include "DestroyableBody.hpp"

using namespace std;
using namespace sf;

class Grenade;
class Bullet;
class Rocket;
class DestroyableBody;

class TempObjectHandler{

	public:
        vector<Grenade* > Grenades;
        vector<Bullet* > Bullets;
        vector<Rocket* > Rockets;
        vector<DestroyableBody* > DBodyes;

        Image grenadeImg;
        Image detonation[3];
        SoundBuffer GranadeSoundBuffer;
        SoundBuffer GranadeThrowSoundBuffer;
        Image rocketImg;
        SoundBuffer RocketFlightSoundBuffer;

        TempObjectHandler();

        void ShowGrenades();
        void ShowBullets();
        void ShowRockets();
        void ShowRocketsDetonation();
        void ShowDBodyes();

        void InputHandling();

        void Add(Grenade* grenade);
        void Remove(Grenade* grenade);
        void Add(Bullet* bullet);
        void Remove(Bullet* bullet);
        void Add(Rocket* bullet);
        void Remove(Rocket* bullet);
        void Add(DestroyableBody* dbody);
        void Remove(DestroyableBody* dbody);

};

#endif
