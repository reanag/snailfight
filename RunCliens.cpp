
#include <iostream>
#include <cstdlib>
#include "Cliens.cpp"


using namespace std;

void ThreadSendFunc(void* UserData)
{

   ClientTCP* Object = static_cast<ClientTCP*>(UserData);

    //GlobalMutex.Lock();
    while(true){
    Object->SendMess("cliens");
    Sleep(1000.0f);
    }
  //  GlobalMutex.Unlock();
}

void ThreadReceiveFunc(void* UserData)
{

    ClientTCP* Object = static_cast<ClientTCP*>(UserData);

   // GlobalMutex.Lock();
   while(true){
    cout << Object->ReceiveMess();
;   }
  //  GlobalMutex.Unlock();
}

int RunClient() {

    string sa = "192.168.1.2";
    unsigned short p = 12435;
    ClientTCP Client = ClientTCP(sa , p);

    sf::Thread ThreadSend(&ThreadSendFunc, &Client);
    sf::Thread ThreadReceive(&ThreadReceiveFunc, &Client);
    ThreadSend.Launch();
    ThreadReceive.Launch();

    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');
    std::cin.ignore(10000, '\n');

    return 0;
}
