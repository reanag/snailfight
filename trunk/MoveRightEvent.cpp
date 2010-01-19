#include "MoveRightEvent.hpp"

MoveRightEvent::MoveRightEvent(){
    EventName = "3MoveRightEvent";
}

MoveRightEvent::MoveRightEvent(string s){
    for(int i = 0; i<s.size(); i++){
        if(s.at(i)=='!'){
            break;
        }
        EventName +=s.at(i);
    }
}

string MoveRightEvent::EventToString(){
    return EventName+"!";
}

