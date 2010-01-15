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
       // mSocket = sock;
        cout<<"\nPOOL created\n";

    }

    void static start() {
        SocketTCP* pSocket;

        Thread* ThreadHandle = new Thread(&ThreadHandleFunc, pSocket);
        ThreadHandle-> Launch();
    }

//Létrehoz egy üzenet küldő és üzenet fogadó szálat
    void static ThreadHandleFunc(void* UserData) {
        cout<<"\n\tThreadHandle START\n";
        SocketTCP* Object = static_cast<SocketTCP*>(UserData);
        Thread* ThreadSendMess = new Thread(&ThreadSendMessFunc, Object);
        Thread* ThreadReceiveMess = new Thread(&ThreadReceiveMessFunc, Object);
        ThreadSendMess -> Launch();
        ThreadReceiveMess -> Launch();


        cout<<"\n\tThreadHandle END\n";

    }


    void static ThreadReceiveMessFunc(void* UserData) {
        cout <<"\nReceiveThread IN\n";
   //     SocketTCP* Object = static_cast<SocketTCP*>(UserData);
    //    SocketTCP sock= *Object;
        cout << "\nReceiveThread START\n";
        while (true) {
            string s = ReceiveMess(mSocket);
            Messages.push_back(&GameEvent(s));
            cout<<"\nsize: "<<Messages.size();
            cout << s;
            Sleep(1.0f);
            //if(s!="-")
            //   Messages.push_back(GameEvent(s));
        }
    }

    void static ThreadSendMessFunc(void* UserData) {
        cout << "\nSendThread IN\n";
     //   SocketTCP* Object = static_cast<SocketTCP*>(UserData);
     //   SocketTCP sock= *Object;
          cout << "\nSendThread Start\n";
        while(true){

            if(MessagesToSend.size()>0){
               GameEvent ev;
               ev = GetFirstEvent(MessagesToSend);

               string s;
               if(ev.EventName == "#TargetPointChangeEvent"){

                    ev = GetFirstEvent(MessagesToSend);
                    s = ev.EventToString();
               }

               SendMess(mSocket, s);

            }
        }
        cout << "\nSendThread End\n";
    }


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

//ez még jó: eventet megkapja, vector mérete szépen nő
  //  static void AddMess(GameEvent ev) {
  //      MessagesToSend.push_back(ev);
       // cout<<MessagesToSend.size();
        //GameEvent ge = GetFirstEvent(MessagesToSend);
       // cout<<"-"<< ge.EventToString();
///}

    static int MessSize() {
        int i = MessagesToSend.size();
        cout<<i;
        return i;
    }

    vector<GameEvent*> GetMessages() {
        return Messages;
    }
//ez szintén működik
    static GameEvent GetFirstEvent(vector<GameEvent*> vec) {
       // if(!vec.size()>0){
       //     GameEvent ev("Null");
       //     return ev;
       // }
        cout<<endl<<vec.size()<<"-";
        GameEvent* p = vec.at(messageIndex);
        vector<GameEvent*>::iterator i = vec.begin();
        vec.erase(i);
        //cout<<endl<<"Ezt vettem ki: "<<p.EventToString();
        cout<<vec.size();
        return *p;
    }

};
#endif
