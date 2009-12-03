#include <SFML/Network.hpp>
#include <iostream>
#include <string>
using namespace std;


class ClientTCP {

protected:
    sf::SocketTCP Client;
    sf::IPAddress ServerAddress;
    unsigned short Port;
    string messFrom;
    string messTo;




public:
    ClientTCP() {
    }

public:
    ClientTCP(string sa) {

        while (!ServerAddress.IsValid()) {
            ServerAddress=sa;
            Port = 12435;
        }


        if (Client.Connect(Port, ServerAddress) != sf::Socket::Done) {
            cout<<"Error";
        }
        //cout<<"konst: "<<Client.IsValid();
        std::cout << "Connected to server " << ServerAddress << std::endl;
   }

    void Run(){
        cout<<"Kliens indul";
        while(true){
            cout<<"kliens";
            Sleep(1000.0f);

        }
        cout<<"Not run";
    }

    ~ClientTCP() {
        Client.Close();
    }


public:
    string ReceiveMess() {
        string s="";
        char Message[1024];
        std::size_t Received;
        if (Client.Receive(Message, sizeof(Message), Received) != sf::Socket::Done)
            return "\nerror in sending\n";

        for (int i = 0; i<10; i++) {
            s+= Message[i];
        }

        return s;
    }

public:
    void SendMess(string s) {
        char ToSend[s.size()];
        for (int i = 0; i<s.size(); i++) {
            ToSend[i] = s[i];
        }


        if (Client.Send(ToSend, sizeof(ToSend)) != sf::Socket::Done) {
        //    cout<<Client.IsValid();
            cout<< "error : " <<ToSend <<"-"<<sf::Socket::Done;
        }

    }


public:
    void setMessTo(string s) {
        messTo = s;
    }
public:
    string getMessFrom() {
        return messFrom;
    }


};

