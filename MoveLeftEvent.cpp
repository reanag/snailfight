#include "MoveLeftEvent.hpp"

MoveLeftEvent::MoveLeftEvent(){
    EventName = "2MoveLeftEvent";
}

MoveLeftEvent::MoveLeftEvent(string s){
    for(int i = 0; i<s.size(); i++){
        if(s.at(i)=='!'){
            break;
        }
        EventName +=s.at(i);
    }
}

string MoveLeftEvent::EventToString(){
    return EventName+"!";
}
