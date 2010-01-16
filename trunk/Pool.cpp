#ifndef POOL
#define POOL

#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Event.hpp"
#include "TargetPointChangeEvent.hpp"
#include "MoveLeftEvent.hpp"
#include "Menu.hpp"


using namespace std;
using namespace sf;

static SocketTCP mSocket;
static vector<GameEvent*>* Messages = new vector<GameEvent*>();
static vector<GameEvent*>* MessagesToSend = new vector<GameEvent*>();
static int messageIndex;


class Pool {

public:

    Pool() {
        cout<<"\nPOOL created\n";
    }

    void start() {
        cout<<"\n\tSTART\n";
        SocketTCP* pSocket;
        GameEvent* ev = new GameEvent("INIT");
        MessagesToSend->push_back(ev);
        Thread* ThreadSendMess = new Thread(&ThreadSendMessFunc);
        Thread* ThreadReceiveMess = new Thread(&ThreadReceiveMessFunc);
        ThreadSendMess -> Launch();
        ThreadReceiveMess -> Launch();
        cout<<"\n\tstart END\n";
    }

//Figyeli a socket-et, ha stringet kap cast-olja a megfelelő típusú üzenetté, és a Messages vektorba teszi.
    static void ThreadReceiveMessFunc(void* UserData) {
        cout << "\nReceiveThread START\n";
        while (true) {
            string s = ReceiveMess(mSocket);
            cout << "\nReceiveThread IN\n";
            if(s.at(0) == '1'){
                TargetPointChangeEvent* ge = new TargetPointChangeEvent(s);
                Messages->push_back(ge);
            }
            if(s.at(0) == '2'){
                MoveLeftEvent* mle = new MoveLeftEvent();
                Messages->push_back(mle);
            } else {
                GameEvent* ge = new GameEvent(s);
                Messages->push_back(ge);
          //      cout<<ge->EventToString();
            }
           Sleep(1.0f);
        }
    }

    void static ThreadSendMessFunc(void* UserData) {
  //     vector<GameEvent*>* Object = static_cast<vector<GameEvent*>*>(UserData) ;
  //      MessagesToSend = Object;
        cout << "\nSendThread Start\n";
        while(true){
       //     cout<<"\n\nPoolban ekkora a vektor merete: "<<MessagesToSend->size();
            if(MessagesToSend->size() > 0){
               GameEvent* ev;
               ev = GetFirstFromMessagesToSend();
               string s;
               s = ev->EventToString();
               if(s.at(0)!='N'){
                  SendMess(mSocket, s);
                  DelFirstFromMessagesToSend();
               }

            }
           Sleep(1.0f);
        }
        cout << "\nSendThread End\n";
    }

    static void  AddMess(GameEvent* ev){
   //     cout<<endl<<"Ezt adom hozza: "<<ev->EventToString()<<" - ";
        MessagesToSend->push_back(ev);
   //     cout<<"az uj meret: "<<MessagesToSend->size()<<endl;

    }

    static GameEvent*  GetFirstFromMessagesToSend(){
        GameEvent* p;
        if(MessagesToSend->size()>0){
            p = MessagesToSend->at(0);
        } else {
            p = new GameEvent("NULL");
        }
        return p;
    }

    static void DelFirstFromMessagesToSend(){
        vector<GameEvent*>::iterator i = MessagesToSend->begin();
        MessagesToSend->erase(i);

    }

    static void SendMess(SocketTCP mSock, string s) {

        char ToSend[s.size()];

        for (int i =0; i<s.size(); i++) {
            ToSend[i] = s[i];
        }
        if (mSock.Send(ToSend, sizeof(ToSend)) != sf::Socket::Done) {
            cout<< "\n\nError in SendMess";
        } else {
            cout<< "Message sent";
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
    //    cout<<"\t\tReceived message: " <<s;
        return s;
    }

};
#endif
