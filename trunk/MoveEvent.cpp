#include "MoveEvent.hpp"

MoveEvent::MoveEvent(float vVel, float fVel, float angVel) {
   EventName = "#MoveEvent";
   vVel = vVel;
   fVel = fVel;
   angVel = angVel;
}

string MoveEvent::EventToString(){
    string s = "#";
    return s;
}
