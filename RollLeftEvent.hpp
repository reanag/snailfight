#ifndef ROLLLEFTEVENT_HPP
#define ROLLLEFTEVENT_HPP
#include "Event.hpp"
#include <string>

using namespace std;

class RollLeftEvent: public GameEvent{

public:
RollLeftEvent();
RollLeftEvent(string s);
string EventToString();

};

#endif



