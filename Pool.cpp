#include <iostream>
#include <vector>
#include "Event.hpp"
using namespace std;

class Pool{
private:
    vector<Event> Messages;

public:

Pool (){
}

void AddMess(Event ev){
    Messages.push_back(ev);
}

vector<Event> GeMessages(){
    return Messages;
}

};
