#include "WeaponChangeEvent.hpp"

WeaponChangeEvent::WeaponChangeEvent(int i):GameEvent(){
    EventName = "#WeaponChangeEvent";
    WeaponNumber = i;
}
WeaponChangeEvent::WeaponChangeEvent(string s):GameEvent(){
    EventName = s.substr(1,17);
    string param = "";
    for(int i = 19; i < s.size(); i++){
        if(s[i] == '!'){
            break;
        }
        param+=s[i];
    }
    WeaponNumber = atoi(param.c_str());

}

string WeaponChangeEvent::EventToString() {
    string s = EventName +Convert(WeaponNumber)+"!";
    return s;
}
