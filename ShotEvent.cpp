#include "ShotEvent.hpp"

ShotEvent::ShotEvent(){
    EventName = "#ShotEvent";
}

ShotEvent::ShotEvent(string s){
    for(int i = 0; i<s.size(); i++){
        if(s.at(i)=='!'){
            break;
        }
        EventName +=s.at(i);
    }
}

string ShotEvent::EventToString(){
    return EventName+"!";
}



