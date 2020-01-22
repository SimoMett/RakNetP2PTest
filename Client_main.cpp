#include <iostream>
#include <thread>
#include "raknet/RakPeerInterface.h"
#include "raknet/RakSleep.h"
#include "raknet/MessageIdentifiers.h"
#include "raknet/RakNetTypes.h"
#include "raknet/BitStream.h"
#include "Common.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
using std::cout;
using std::endl;

void SendSomething(RakNet::RakPeerInterface * client);

int main()
{
    std::cout << "Starting Client" << std::endl;
    RakNet::RakPeerInterface * rakpeer=RakNet::RakPeerInterface::GetInstance();

    RakNet::SocketDescriptor socketDescriptor;
    rakpeer->Startup(8,&socketDescriptor,1);
    RakNet::ConnectionAttemptResult res=rakpeer->Connect("localhost",MYPORT, nullptr,0);

    std::thread sender(SendSomething,rakpeer);
    sender.join();
    return 0;
}

void SendSomething(RakNet::RakPeerInterface * client)
{
    while(true)
    {
        RakSleep(3000);
        int res=client->Send("hi",3,HIGH_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);

    }
}

#pragma clang diagnostic pop