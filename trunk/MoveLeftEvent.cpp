#include "MoveLeftEvent.hpp"

MoveLeftEvent::MoveLeftEvent(){
    EventName = "2MoveLeftEvent";
}

MoveLeftEvent::MoveLeftEvent(string s){
    EventName = "2"+s;
}

string MoveLeftEvent::EventToString(){
    return EventName;
}
