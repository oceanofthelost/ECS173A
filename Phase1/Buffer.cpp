#include<queue>
#include "Buffer.h"
using namespace std;

Buffer::Buffer()
{
    Buff = queue<Packet>();
}

unsigned Buffer::size() const
{
    return Buff.size();
}

void Buffer::addPacket(const Packet& packet)
{
    Buff.push(packet);
}

Packet Buffer::nextPacket()
{
    Packet packet = Buff.front();
    Buff.pop();
    return packet;
}
