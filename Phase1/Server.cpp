#include <iostream>
#include <cmath>
#include "Server.h"
#include "Event.h"
using namespace std;

//function prototypes
double service_time(const double&); 

/**
 * Default constructor for the server
 * @parem m: mu rate 
 * @parem maxBuffer: the maximum size of the buffer
 */
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

/**
 * Will display the server stats to the terminal window
 * @param total_time: total time the server ran
 * @param lambda: the lambda that is used for the simulation
 * @param toFile: Determines how i am going to print the data
 */
void Server::printStatistics(const double& total_time,const double& lambda, const bool& toFile) const
{
    if(!toFile)
    {
        if(maxBufferSize < 0)
        {
            cout<<"Buffersize:\t\t"<<"Infinite"<<endl;
        }
        else
        {
            cout<<"Buffersize:\t\t\t"<<maxBufferSize<<endl;
        }
        cout<<"Lambda:\t\t\t\t"<<lambda<<endl;
        cout<<"Mu:\t\t\t\t"<<mu<<endl;
        cout<<"Utilization time:\t\t"<<utilization_time/total_time<<endl;
        cout<<"Mathmatical Utilization:\t"<<lambda/mu<<endl;
        cout<<"Mean Buffer Length:\t\t"<<mean_buffer_length/total_time<<endl;
        cout<<"Mathmatical Buffer length:\t"<<(lambda/mu)/(1-(lambda/mu))<<endl;
        cout<<"Dropped Packets:\t\t"<<dropped_packets<<endl;
        cout<<"% Dropped Packets:\t\t"<<(dropped_packets/100000)*100<<endl;
        cout<<endl;
    }
    else
    {
        //prints data to a comma deliminated file. used so that data can be parsed and be 
        //put into a table easly
        cout<<lambda<<",";
        if(maxBufferSize < 0)
        {
            cout<<"Infinite,";
            cout<<utilization_time/total_time<<",";
            cout<<mean_buffer_length/total_time<<",";
            cout<<dropped_packets<<",";
            cout<<endl;

        }
        else
        {
            cout<<maxBufferSize<<",";
            cout<<utilization_time/total_time<<",";
            cout<<mean_buffer_length/total_time<<",";
            cout<<dropped_packets<<",";
            cout<<endl;

        }
    }
}

/**
 * Server has an an arrival event occurring
 * @param  currentTime: current time that the event id occurring. 
 * @param  oldTime: time the last event occurred
 * @return: Event that will determine the next step of the simulation.
 */
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
        if((maxBufferSize < 0) or (buff.size() < maxBufferSize))
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

/**
 * Departure event for the server
 * @param  currentTime: current time the event is occurring 
 * @param  oldTime: time last event occurred
 * @return : Event that determines the next step in the simulation 
 */
Event Server::departureEvent(const double& currentTime, const double& oldTime)
{
    //packet is done transmitting
    
    transmitting    = false;
    //update utilization time and mean buffer length
    mean_buffer_length+=(length * (currentTime-oldTime));
    utilization_time+=(currentTime-oldTime); 
    length         -= 1; //transmitter is done with current packet

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
