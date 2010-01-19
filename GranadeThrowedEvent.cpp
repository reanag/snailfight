#include "GranadeThrowedEvent.hpp"

GranadeThrowedEvent::GranadeThrowedEvent(){
    EventName = "9GranadeThrowedEvent";
}

GranadeThrowedEvent::GranadeThrowedEvent(string s){
    for(int i = 0; i<s.size(); i++){
        if(s.at(i)=='!'){
            break;
        }
        EventName +=s.at(i);
    }

}

string GranadeThrowedEvent::EventToString(){
    return EventName+"!";
}




