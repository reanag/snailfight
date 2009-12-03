#ifndef EVENT_HPP
#define EVENT_HPP
#include <string>
using namespace std;

class Event{

protected:
    string EventName;

public:
    Event();
    virtual string EventToString();

};
#endif
