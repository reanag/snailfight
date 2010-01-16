#ifndef POOL
#define POOL

#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Event.hpp"
#include "TargetPointChangeEvent.hpp"
#include "Menu.hpp"


using namespace std;
using namespace sf;

static SocketTCP mSocket;
static vector<GameEvent*> Messages;
static vector<GameEvent*> MessagesToSend;
static int messageIndex;


class Pool {



public:

    Pool() {
        cout<<"\nPOOL created\n";
    }

    void static start() {
        SocketTCP* pSocket;
        Thread* ThreadHandle = new Thread(&ThreadHandleFunc, pSocket);
        ThreadHandle-> Launch();
    }

//Létrehoz egy üzenet küldő és üzenet fogadó szálat és elindítja őket
    void static ThreadHandleFunc(void* UserData) {
        cout<<"\n\tThreadHandle START\n";
        SocketTCP* Object = static_cast<SocketTCP*>(UserData);
        Thread* ThreadSendMess = new Thread(&ThreadSendMessFunc, Object);
        Thread* ThreadReceiveMess = new Thread(&ThreadReceiveMessFunc, Object);
        ThreadSendMess -> Launch();
        ThreadReceiveMess -> Launch();
        cout<<"\n\tThreadHandle END\n";
    }

//Figyeli a socket-et, ha stringet kap cast-olja a megfelelő típusú üzenetté, és a Messages vektorba teszi.
    void static ThreadReceiveMessFunc(void* UserData) {
        cout << "\nReceiveThread START\n";
        while (true) {
            string s = ReceiveMess(mSocket);
            if(s.at(0) == '1'){
                TargetPointChangeEvent* ge = new TargetPointChangeEvent(s);
                Messages.push_back(ge);
            } else {
                GameEvent* ge = new GameEvent(s);
                Messages.push_back(ge);
            }
            Sleep(1.0f);
        }
    }

    void static ThreadSendMessFunc(void* UserData) {
        cout << "\nSendThread Start\n";
        while(true){
               GameEvent* ev;
               ev = GetActEvent(MessagesToSend);
               string s;
               s = ev->EventToString();
               SendMess(mSocket, s);
               Sleep(1.0f);
        }
        cout << "\nSendThread End\n";
    }

//Üzenet küldés, ezzel nem kell foglalkozni, jó úgy ahogy van!!!
    void static SendMess(SocketTCP mSock, string s) {
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

//Üzenet fogadás, ezzel nem kell foglalkozni, jó úgy ahogy van!!!
    string static ReceiveMess(SocketTCP mSock) {
        string s="";
        char Message[1024];
        std::size_t Received;
        if (mSock.Receive(Message, sizeof(Message), Received) != sf::Socket::Done)
            return "-";

        for (int i = 0; i<40; i++) {
            s+= Message[i];
        }
        cout<<"Received message: " <<s;
        return s;
    }


  //  vector<GameEvent*> GetMessages() {
    //    return Messages;
   // }

//Visszatér a legutóbb beletett elemmel
    static GameEvent* GetActEvent(vector<GameEvent*> vec) {
        GameEvent* p;
        p = vec.at(messageIndex);
        return p;
    }

};
#endif
