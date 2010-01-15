#ifndef TARGETPOINT_CHANGE
#define TARGETPOINT_CHANGE
#include<string>
#include"Event.hpp"
using namespace std;

class TargetPointChangeEvent: public GameEvent{

public:
    int x, y;

public:
    TargetPointChangeEvent(int x, int y);
    TargetPointChangeEvent(string s);
    string EventToString();
};
#endif
