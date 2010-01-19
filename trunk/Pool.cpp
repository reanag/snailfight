#ifndef POOL
#define POOL

#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Event.hpp"
#include "TargetPointChangeEvent.hpp"
#include "MoveLeftEvent.hpp"
#include "MoveRightEvent.hpp"
#include "MoveUpEvent.hpp"
#include "RollLeftEvent.hpp"
#include "RollRightEvent.hpp"
#include "ShotEvent.hpp"
#include "Menu.hpp"


using namespace std;
using namespace sf;

static SocketTCP mSocket;
static vector<GameEvent*>* Messages;
static vector<GameEvent*>* MessagesToSend;

class Pool {

public:
    int id;
    Pool() {
        Messages = new vector<GameEvent*>();
        MessagesToSend = new vector<GameEvent*>();
        cout<<"\nPOOL created\n";
    }

    void start() {
        cout<<"\n\tSTART\n";
        SocketTCP* pSocket;
        GameEvent* ev = new GameEvent("INIT");
        GameEvent* iv = new GameEvent("INIT");
        MessagesToSend->push_back(ev);
        Messages->push_back(iv);
        Thread* ThreadSendMess = new Thread(&ThreadSendMessFunc);
        Thread* ThreadReceiveMess = new Thread(&ThreadReceiveMessFunc, this);
        ThreadSendMess -> Launch();
        ThreadReceiveMess -> Launch();
        cout<<"\n\tstart END\n";
    }

//Figyeli a socket-et, ha stringet kap cast-olja a megfelelő típusú üzenetté, és a Messages vektorba teszi.
     void static ThreadReceiveMessFunc(void* UserData) {
        cout << "\nReceiveThread START\n";
        while (true) {
            string s = ReceiveMess(mSocket);
            cout<<"ezt kaptam: "<<s;
            if(s.at(0) == '1'){
                TargetPointChangeEvent* ge = new TargetPointChangeEvent(s);
                Messages->push_back(ge);
            }
            if(s.at(0) == '2'){
                MoveLeftEvent* mle = new MoveLeftEvent();
                Messages->push_back(mle);
            }
            if(s.at(0) =='3'){
                MoveRightEvent* mre = new MoveRightEvent();
                Messages->push_back(mre);
            }
            if(s.at(0) =='4'){
                MoveUpEvent* mue = new MoveUpEvent();
                Messages->push_back(mue);
            }
              if(s.at(0) =='5'){
                MoveDownEvent* mde = new MoveDownEvent();
                Messages->push_back(mde);
            }
            if(s.at(0) =='7'){
                RollLeftEvent* rle = new RollLeftEvent();
                Messages->push_back(rle);
            }
            if(s.at(0) =='8'){
                RollRightEvent* rre = new RollRightEvent();
                Messages->push_back(rre);
            }
            if(s.at(0) =='9'){
                GranadeThrowedEvent* gte = new GranadeThrowedEvent();
                Messages->push_back(gte);
            }

            if(s.at(0)=='#'){//"#ShotEvent"){
                cout<<"Loves van";
                ShotEvent* se = new ShotEvent();
                Messages->push_back(se);
            }
             else {
                GameEvent* ge = new GameEvent(s);
                Messages->push_back(ge);

            }
        }
    }

//visszatér a Messages vektor méretével
    int GetMessSize(){
        return Messages->size();
    }
    void static ThreadSendMessFunc(void* UserData) {
        cout << "\nSendThread Start\n";
        while(true){
            if(MessagesToSend->size() > 0){
               GameEvent* ev;
               if(MessagesToSend->size()>0){
                    ev = MessagesToSend->at(0);
                } else {
                    ev = new GameEvent("NULL");
                }
               string s;
               s = ev->EventToString();
            //   cout<<"ezt kuldom: "<<s;
               if(s.at(0)!='N'){
                  SendMess(mSocket, s);
                  vector<GameEvent*>::iterator i = MessagesToSend->begin();
                  MessagesToSend->erase(i);
               }
            }
          //Sleep(1.0f);
        }
    }

//MessagesToSend vektorba beletesz egy eventet
    static void  AddMess(GameEvent* ev){
          MessagesToSend->push_back(ev);
         // cout<<ev->EventToString()<<" lett hozzaadva\n\n";
    }
//Messages vektorba beletesz egy eventet
    static void AddMess2(GameEvent* ev){
        Messages->push_back(ev);
    }



//Visszatér a Messages vektor első elemével, majd kitörli azt
   static GameEvent* GetMess(){
        GameEvent* tp;
        if(Messages->size()>0){
            tp = Messages->at(0);
        } else {
            tp = new GameEvent("NULL");
        }

        if(tp->EventToString().at(1) == 'N'){
        } else {
            vector<GameEvent*>::iterator i = Messages->begin();
            Messages->erase(i);
        }
        return tp;
    }

    static void SendMess(SocketTCP mSock, string s) {

        char ToSend[s.size()];

        for (int i =0; i<s.size(); i++) {
            ToSend[i] = s[i];
        }
        if (mSock.Send(ToSend, sizeof(ToSend)) != sf::Socket::Done) {
            cout<< "\n\nError in SendMess";
        } else {
     //       cout<< "Message sent";
        }
    }

    static string  ReceiveMess(SocketTCP mSock) {
        string s="";
        char Message[50];
        std::size_t Received;
        if (mSock.Receive(Message, sizeof(Message), Received) != sf::Socket::Done)
            return "-";

        for (int i = 0; i<40; i++) {
            s+= Message[i];
        }
        return s;
    }

};
#endif
