#ifndef BUFFER_SDA
#define BUFFER_SDA

#include<queue>
#include "Packet.h"
using namespace std;

//simple struct wrapper for a packet. using this so 
//if more attributes are added later it is a simple process


class Buffer
{
    private:
        //data structre that models the buffer
        queue<Packet> Buff;
    public:
        //default constructor for the Buffer
        Buffer();
        //find out if the buffer is empty
        unsigned size() const;
        //add a packet to the buffer
        void addPacket(const Packet&);
        //return the next packet in the buffer
        Packet nextPacket();
};

#endif
