#ifndef WEAPON_CHANGE
#define WEAPON_CHANGE

#include "Event.hpp"

class WeaponChangeEvent: public GameEvent{
private:
    int WeaponNumber;

public:
    WeaponChangeEvent(int i);
    WeaponChangeEvent(string s);
    virtual string EventToString();



};
#endif
