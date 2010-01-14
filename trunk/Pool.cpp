#ifndef POOL
#define POOL

#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Event.hpp"


using namespace std;
using namespace sf;

class Pool {
private:
    static vector<GameEvent> Messages;
    static vector<GameEvent> MessagesToSend;
    SocketTCP mSocket;

public:

    Pool (SocketTCP sock) {
        mSocket = sock;
        cout<<"\nPOOL created\n";
        SocketTCP* pSocket = &mSocket;
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
        SocketTCP* Object = static_cast<SocketTCP*>(UserData);
        SocketTCP sock= *Object;
        cout << "\nReceiveThread START\n";
        while (true) {
            string s = ReceiveMess(sock);
            cout << s;
            Sleep(1.0f);
            //if(s!="-")
            //   Messages.push_back(GameEvent(s));
        }
    }

    void static ThreadSendMessFunc(void* UserData) {
        cout << "\nSendThread IN\n";
        SocketTCP* Object = static_cast<SocketTCP*>(UserData);
        SocketTCP sock= *Object;
        cout << "\nSendThread Start\n";
        //     if(MessagesToSend.size()>0){
        //       string s = GetFirstEvent(MessagesToSend).EventToString();
        SendMess(sock, "uzenet");
        cout << "\nSendThread End\n";
    }


    void static SendMess(SocketTCP mSock, string s) {
        char ToSend[s.size()];
        for (int i =0; i<s.size(); i++) {
            ToSend[i] = s[i];
        }


        if (mSock.Send(ToSend, sizeof(ToSend)) != sf::Socket::Done) {
            cout<< "\n\nError in SendMess";
        }
    }


    string static ReceiveMess(SocketTCP mSock) {
        string s="";
        char Message[1024];
        std::size_t Received;
        if (mSock.Receive(Message, sizeof(Message), Received) != sf::Socket::Done)
            return "-";

        for (int i = 0; i<10; i++) {
            s+= Message[i];
        }
        cout<<"Received message: " <<s;
        return s;
    }


    void AddMess(GameEvent ev) {
        Messages.push_back(ev);
    }

    int MessSize() {
        return Messages.size();
    }

    vector<GameEvent> GeMessages() {
        return Messages;
    }

    GameEvent GetFirstEvent(vector<GameEvent> vec) {
        GameEvent p = vec.at(0);
        vector<GameEvent>::iterator i = vec.begin();
        vec.erase(i);
        return p;
    }

};
#endif
