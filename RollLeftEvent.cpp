#include "RollLeftEvent.hpp"

RollLeftEvent::RollLeftEvent(){
    EventName = "7RollLeftEvent";
}

RollLeftEvent::RollLeftEvent(string s){
    for(int i = 0; i<s.size(); i++){
        if(s.at(i)=='!'){
            break;
        }
        EventName +=s.at(i);
    }
}

string RollLeftEvent::EventToString(){
    return EventName+"!";
}



