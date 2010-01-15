#include "TargetPointChangeEvent.hpp"

    TargetPointChangeEvent::TargetPointChangeEvent(int xPos, int yPos){
        EventName = "#TargetPointChangeEvent";
        x = xPos;
        y = yPos;
    }

   TargetPointChangeEvent::TargetPointChangeEvent(string s){
        EventName = s.substr(1, 22);
        string param = "";
        int pos = 0;
        for(int i = 24; i<s.size(); i++){
            if(s[i] == ';') {
                pos = i;
                break;
            }
            param+=s[i];
        }
         x = atoi(param.c_str());
         param = "";
         pos++;
         for(int i = pos; i<s.size(); i++){
            if(s[i] =='!'){
                break;
            }
            param += s[i];
         }
         y = atoi(param.c_str());

    }

    string TargetPointChangeEvent::EventToString(){
        string s = EventName+";"+Convert(x)+";"+Convert(y)+"!";
        return s;
    }
