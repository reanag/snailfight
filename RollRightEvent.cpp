#include "RollRightEvent.hpp"

RollRightEvent::RollRightEvent(){
    EventName = "8RollRightEvent";
}

RollRightEvent::RollRightEvent(string s){
     for(int i = 0; i<s.size(); i++){
        if(s.at(i)=='!'){
            break;
        }
        EventName +=s.at(i);
    }
}

string RollRightEvent::EventToString(){
    return EventName+"!";
}




