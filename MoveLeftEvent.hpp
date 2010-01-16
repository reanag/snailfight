#ifndef MOVELEFTEVENT_HPP
#define MOVELEFTEVENT_HPP
#include "Event.hpp"
#include <string>

using namespace std;

class MoveLeftEvent: public GameEvent{

private:
float xVelocity;
float yVelocity;
float angVelocity;

public:
MoveLeftEvent();
MoveLeftEvent(string s);
string EventToString();

};

#endif

