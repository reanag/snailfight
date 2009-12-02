
#include <SFML/Network.hpp>
#include <iostream>
#include <string>


using namespace std;

class ServerTCP {

protected:

    unsigned short Port;
    sf::SocketTCP Server;
    sf::IPAddress ServerAddress;
    sf::IPAddress ClientAddress;
    sf::SocketTCP Client;
    string messTo;
    string messFrom;


public:
    ServerTCP() {

        //ServerAddress = sa;
        Port = 12435;
        if (!Server.Listen(Port)) {
            cout<<"egy";
            return;
        }

        std::cout << "Server is listening to port " << Port << ", waiting for connections... " << std::endl;
    }

public:
    void Run() {
        WaitForConnection();
    }

public:
    ~ServerTCP() {
        Client.Close();
        Server.Close();
    }


public:
    void WaitForConnection() {
        if (Server.Accept(Client, &ClientAddress) != sf::Socket::Done) {
            cout<<"ajjajj";
            return;
        }
        cout<<"Client connected: "<<ClientAddress;
        cout << "\nvegtelen ciklus indul\n";
        while(true) {
            Sleep(1.0f);
            cout << "\nsleep\n";
        }

    }


public:
    void SendMess(string s) {
        char ToSend[s.size()];
        for (int i =0; i<s.size(); i++) {
            ToSend[i] = s[i];
        }


        if (Client.Send(ToSend, sizeof(ToSend)) != sf::Socket::Done) {
            cout<< "\n\nServer.SendMess";
            return;
        }

        //   std::cout << "Message sent to the client : \"" << ToSend << "\"" << std::endl;
    }

public:
    string ReceiveMess() {
        string s="";
        char Message[1024];
        std::size_t Received;
        if (Client.Receive(Message, sizeof(Message), Received) != sf::Socket::Done)
            return "-";

        for (int i = 0; i<10; i++) {
            s+= Message[i];
        }
        return s;
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
