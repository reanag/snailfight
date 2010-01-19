#include "MoveUpEvent.hpp"

MoveUpEvent::MoveUpEvent(){
    EventName = "4MoveUpEvent";
}

MoveUpEvent::MoveUpEvent(string s){
    for(int i = 0; i<s.size(); i++){
        if(s.at(i)=='!'){
            break;
        }
        EventName +=s.at(i);
    }
}

string MoveUpEvent::EventToString(){
    return EventName+"!";
}


