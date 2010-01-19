#include "MoveDownEvent.hpp"

MoveDownEvent::MoveDownEvent(){
    EventName = "5MoveRightEvent";
}

MoveDownEvent::MoveDownEvent(string s){
      for(int i = 0; i<s.size(); i++){
        if(s.at(i)=='!'){
            break;
        }
        EventName +=s.at(i);
    }
}

string MoveDownEvent::EventToString(){
    return EventName+"!";
}


