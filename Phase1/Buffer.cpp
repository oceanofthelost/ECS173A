#include <queue>
#include "Buffer.h"
using namespace std;

/**
 * Default constructor 
 */
Buffer::Buffer()
{
    Buff = queue<Packet>();
}

/**
 * Determines the size of the buffer
 * unsigned: value containing the size of the buffer
 */
unsigned Buffer::size() const
{
    return Buff.size();
}

/**
 * Adds a packet to the buffer
 * @param packet: Packet that will be added to the buffer
 */
void Buffer::addPacket(const Packet& packet)
{
    Buff.push(packet);
}

/**
 * Returns the next packet in the buffer
 * @return: a packet
 */
Packet Buffer::nextPacket()
{
    Packet packet = Buff.front();
    Buff.pop();
    return packet;
}
