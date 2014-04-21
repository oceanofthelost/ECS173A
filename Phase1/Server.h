#ifndef SERVER_SDA
#define SERVER_SDA

#include "Buffer.h"
#include "Event.h"

class Server
{
    private:
        //statistics for the server
        double utilization_time;
        double mean_buffer_length;
        double dropped_packets;
        //servers buffer
        Buffer buff;
        //transmitter
        bool transmitting; //true: transmitting, false: not transmitting
        
        //server parameters
        int maxBufferSize;
        double lambda;
        double mu;
        //length includes the packet that is being transmitted
        //if there is a transmission otherwise length is just the 
        //size of the buffer.
        int length;
        

    public:
        //default constructor
        Server(double,int);
        //we display the statistics for the server
        void printStatistics(const double&) const;
        //process an arrival event
        Event arrivalEvent(const double&,const double&);
        //process a departure event;
        Event departureEvent(const double&,const double&);
};

#endif
