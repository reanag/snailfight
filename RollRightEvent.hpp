#ifndef ROLLRIGHTEVENT_HPP
#define ROLLRIGHTEVENT_HPP
#include "Event.hpp"
#include <string>

using namespace std;

class RollRightEvent: public GameEvent{

public:
RollRightEvent();
RollRightEvent(string s);
string EventToString();

};

#endif




