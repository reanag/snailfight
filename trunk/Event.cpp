#include "Event.hpp"


GameEvent::GameEvent(){
   EventName = "#";
}

GameEvent::GameEvent(string s) {
    EventName = "#"+s;
}

string GameEvent::EventToString(){
    return EventName;
}


