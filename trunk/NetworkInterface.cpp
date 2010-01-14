#include <SFML/Network.hpp>
#include <iostream>
#include <string>


using namespace std;
using namespace sf;

class NetworkInterface {

protected:
    unsigned short Port;
    SocketTCP Server;
    SocketTCP Client;
    IPAddress ServerAddress;
    IPAddress ClientAddress;

public:
    SocketTCP RunAsServer() {
        return WaitForConnection();
    }

public:
    SocketTCP RunAsClient(string ip) {
        return Connect(ip);
    }

public:
    void Close() {
        Client.Close();
        Server.Close();
    }


public:
    SocketTCP WaitForConnection() {
        Port = 12435;
        if (!Server.Listen(Port)) {
            cout<<"Error in WaitForConnection 1";
//            return NULL;
        }

        std::cout << "Server is listening to port " << Port << ", waiting for connections... " << std::endl;
        if (Server.Accept(Client, &ClientAddress) != sf::Socket::Done) {
            cout<<"Error in WaitForConnection 2";
            //return NULL;
        }

        cout<<"Client connected: "<<ClientAddress;
        return Client;
    }

    SocketTCP Connect(string sa) {

    //    while (!ServerAddress.IsValid()) {
            ServerAddress=sa;
            Port = 12435;
      //  }

        if (Client.Connect(Port, ServerAddress) != Socket::Done) {
            cout<<"Error in Connect 1";
        } else {
            cout << "Connected to server " << ServerAddress << std::endl;
        }


        return Client;
    }


};


