#ifndef MOVEEVENT_HPP
#define MOVEEVENT_HPP
#include "Event.hpp"
#include <string>

using namespace std;

class MoveEvent: public GameEvent{

private:
float xVelocity;
float yVelocity;
float angVelocity;

public:
MoveEvent(float xVel, float yVel, float angVel);
MoveEvent(string s);
//~MoveEvent();
virtual string EventToString();

};

#endif
