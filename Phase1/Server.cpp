#include <iostream>
#include <cmath>
#include "Server.h"
#include "Event.h"
using namespace std;

//function prototypes
double service_time(const double&); 

//Server member functions
Server::Server(double m, int maxBuffer)
{
    utilization_time    = 0.0;
    mean_buffer_length  = 0.0;
    dropped_packets     = 0.0;
    transmitting        = false;
    length              = 0;
    maxBufferSize       = maxBuffer;
    mu                  = m;
}

void Server::printStatistics(const double& total_time) const
{
    cout<<"Utilization time:\t"<<utilization_time/total_time<<endl;
    cout<<"Mean Buffer Length:\t"<<mean_buffer_length/total_time<<endl;
    cout<<"Dropped Packets:\t"<<dropped_packets<<endl;
}

Event Server::arrivalEvent(const double& currentTime,const double& oldTime)
{
    //generate the packet that arrived
    Packet packet;
    packet.serviceTime = service_time(mu);
    
    //not transmitting and nothing in buffer
    if(length == 0)
    {
        //we start transmitting the packet
        transmitting = true;
        length+=1; //since we are transmitting
        return Event(currentTime + service_time(mu),EventType::Departure);
    }
    else //server must be transmitting
    {
        //if maxbuffsize < 0 buffer is infinite in size
        //otherwise buffer is finite and we make sure its not full
        //buf.size() = length-1 since length = buff.size() + 1 if transmitting
        if((maxBufferSize < 0) || (buff.size() < maxBufferSize))
        {
            buff.addPacket(packet);
            length+=1;
        }
        //packet will be dropped
        else
        {
            dropped_packets+=1;
        }
        //calculate the utilization time and mean buffer length
        mean_buffer_length+=(length * (currentTime-oldTime));
        utilization_time+=(currentTime-oldTime);
    }
    
    //caller does not have to do anything
    return Event(0,EventType::Nothing);
}

Event Server::departureEvent(const double& currentTime, const double& oldTime)
{
    //packet is done transmitting
    length         -= 1; //transmitter is done with current packet
    transmitting    = false;

    //we transmit the next packet in the buffer if there is one
    if(length == 0)
    {
        //we do nothing
    }
    else //there must be a packet in the buffer
    {
        Packet nextPacket = buff.nextPacket();
        //we return the departure event and start transmitting
        transmitting = true;
        
        //update utilization time and mean buffer length
        mean_buffer_length+=(length * (currentTime-oldTime));
        utilization_time+=(currentTime-oldTime);
        /*
         dont have to worry about changing length. see below
        length+=1; //transmitter has new packet
        length-=1; //buffer moves packet from itself to transmitter
        
        */
        // return a departure event
        return Event(currentTime + nextPacket.serviceTime,EventType::Departure);
    }
    
    //returns an event that lets the coller know that 
    //nothing needs to be done. 
    return Event(0,EventType::Nothing);
}

//negative exponential distributed, rate = mu
double service_time(const double& rate) 
{
    double u;
    u = drand48();
    return ((-1/rate)*log(1-u));
}
