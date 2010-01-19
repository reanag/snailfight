#ifndef SHOTEVENT_HPP
#define SHOTEVENT_HPP
#include "Event.hpp"
#include <string>

using namespace std;

class ShotEvent: public GameEvent{

public:
ShotEvent();
ShotEvent(string s);
string EventToString();

};

#endif




