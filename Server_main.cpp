//
// Created by matteo on 22/01/20.
//
#include <iostream>
#include <thread>
#include "raknet/RakPeerInterface.h"
#include "raknet/RakSleep.h"
#include "Common.h"

using std::cout;
using std::endl;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main()
{
    cout << "Starting Server"<<endl;
    RakNet::RakPeerInterface * rakpeer=RakNet::RakPeerInterface::GetInstance();

    RakNet::SocketDescriptor socketDescriptor(MYPORT, nullptr);
    auto res=rakpeer->Startup(10,&socketDescriptor,1);
    rakpeer->SetMaximumIncomingConnections(10);
    rakpeer->SetTimeoutTime(5000,RakNet::UNASSIGNED_SYSTEM_ADDRESS);

    if(res==RakNet::RAKNET_STARTED)
        cout << "good"<<endl;

    while(true)
    {
        static int count=0;
        RakSleep(1000);

        if(!count)
            cout << "Connected clients: "<<rakpeer->NumberOfConnections()<<endl;

        RakNet::Packet * p=rakpeer->Receive();
        if(p)
        {
            cout <<"received "<<p->bitSize<<" bits -> \""<<p->data<<"\""<<endl;
        }

        rakpeer->DeallocatePacket(p);
        count++;
        count%=5;
    }
    rakpeer->Shutdown(300);
    RakNet::RakPeerInterface::DestroyInstance(rakpeer);
    return 0;
}
#pragma clang diagnostic pop
