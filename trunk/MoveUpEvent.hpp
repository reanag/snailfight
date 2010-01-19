#ifndef MOVEUPEVENT_HPP
#define MOVEUPEVENT_HPP
#include "Event.hpp"
#include <string>

using namespace std;

class MoveUpEvent: public GameEvent{


public:
MoveUpEvent();
MoveUpEvent(string s);
string EventToString();

};

#endif



