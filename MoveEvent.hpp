#ifndef MOVEEVENT_HPP
#define MOVEEVENT_HPP
//#include "Event.hpp"
#include <string>

using namespace std;

class MoveEvent{

private:
float vVel;
float fVel;
float angVel;

public:
MoveEvent(float vVel, float fVel, float angVel);
//~MoveEvent();
virtual string EventToString();

};

#endif
