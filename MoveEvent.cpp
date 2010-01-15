#include "MoveEvent.hpp"

MoveEvent::MoveEvent(float xVel, float yVel, float angVel):GameEvent() {
    xVelocity = xVel;
    yVelocity = yVel;
    angVelocity = angVel;
    EventName = "#MoveEvent";
}

MoveEvent::MoveEvent(string s) {
    EventName = s.substr(1,9);
    int pos = 0;
    string param = "";
    for (int i = 11; i<s.size(); i++) {
        if (s[i] == ';') {
            pos = i;
            break;
        }
        param += s[i];
    }
    xVelocity = atof(param.c_str());
    pos++;
    param = "";
    for (int i = pos; i<s.size(); i++) {
        if (s[i] == ';') {
            pos = i;
            break;
        }
        param+=s[i];
    }
    yVelocity = atof(param.c_str());
    pos++;
    param = "";
    for (int i = pos; i<s.size(); i++) {
        if (s[i] == '!') {
            pos = i;
            break;
        }
        param+=s[i];
    }
    angVelocity = atof(param.c_str());
}

string MoveEvent::EventToString() {
    string s = EventName +Convert(xVelocity)+";"+Convert(yVelocity)+";"+Convert(angVelocity)+"!";
    return s;
}


