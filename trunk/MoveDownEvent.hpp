#ifndef MOVEDOWNEVENT_HPP
#define MOVEDOWNEVENT_HPP
#include "Event.hpp"
#include <string>

using namespace std;

class MoveDownEvent: public GameEvent{

public:
MoveDownEvent();
MoveDownEvent(string s);
string EventToString();

};

#endif


