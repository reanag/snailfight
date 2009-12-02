
#include <iostream>
#include <cstdlib>
//#include <SFML/System.hpp>
#include "Server.cpp"

using namespace std;

sf::Mutex GlobalMutex;







int RunServer() {


    string sa = "192.168.1.2";
    unsigned short port = 12435;
    ServerTCP Server = ServerTCP(sa, port);


    sf::Thread ThreadSendS(&ThreadSendSFunc, &Server);
    sf::Thread ThreadReceiveS(&ThreadReceiveSFunc, &Server);
    ThreadSendS.Launch();
    ThreadReceiveS.Launch();


    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');
    std::cin.ignore(10000, '\n');

    return 0;
}
