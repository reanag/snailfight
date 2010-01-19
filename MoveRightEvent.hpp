#ifndef MOVERIGHTEVENT_HPP
#define MOVERIGHTEVENT_HPP
#include "Event.hpp"
#include <string>

using namespace std;

class MoveRightEvent: public GameEvent{


public:
MoveRightEvent();
MoveRightEvent(string s);
string EventToString();

};

#endif


