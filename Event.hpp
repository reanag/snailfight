#ifndef GAMEEVENT_HPP
#define GAMEEVENT_HPP
#include <string>
#include<iostream>
using namespace std;

class GameEvent{

protected:
    string EventName;

public:
    GameEvent();
    GameEvent(string s);

    virtual string EventToString();

};

#endif
