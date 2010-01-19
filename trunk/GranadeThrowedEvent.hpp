#ifndef GRANADETHROWEDEVENT_HPP
#define GRANADETHROWEDEVENT_HPP
#include "Event.hpp"
#include <string>

using namespace std;

class GranadeThrowedEvent: public GameEvent{

public:
GranadeThrowedEvent();
GranadeThrowedEvent(string s);
string EventToString();

};

#endif




