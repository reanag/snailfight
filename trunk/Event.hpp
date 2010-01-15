#ifndef GAMEEVENT_HPP
#define GAMEEVENT_HPP
#include <string>
#include <sstream>
#include<iostream>
using namespace std;

class GameEvent{

public:
    string EventName;

public:
    GameEvent();
    GameEvent(string s);
    string Convert (float number);
    virtual string EventToString();

};

#endif
