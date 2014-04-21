#include <cstdlib>
#include <iostream>
#include <cmath>
#include "Event.h"
#include "GlobalEventList.h"
#include "Server.h"
using namespace std;

//negative exponential distributed, rate = lambda
double inter_arrival(double rate) 
{
    double u;
    u = drand48();
    return ((-1/rate)*log(1-u));
}

//using argc and argv makes testing a lot easier to run 
//multiple tests, that way we dont have to recompile affer
//changing the parameters
int main(int argc, char* argv[])
{
    //argc needs to be 4
    //argv[0] = executable, this is default
    //arcv[1] = lambda
    //argv[2] = mu
    //argv[3] = buffersize
    //
    //if buffer size >= 0 then this is the buffer size limit
    //if buffer size < 0 then this means the buffer has infinite size

    if(argc == 4)
    {
        
        //initilaze variables
        double  time    = 0.0;
        double  lambda  = atof(argv[1]);    
        //mu, maxBuffer
        Server server(atof(argv[2]),atoi(argv[3]));
        GlobalEventList GEL;

        //generate the fist event and put it in the GEL
        GEL.addEvent(Event(time+inter_arrival(lambda),EventType::Arrival)); 

        for(int i = 0; i<100000;i++)
        {
            Event event = GEL.nextEvent();

            //arrival event
            if(event.getEventType() == EventType::Arrival)
            {
                double oldTime = time;
                time = event.getTime();
                //schedule next arrival event and put it in the GEL
                GEL.addEvent(Event(time + inter_arrival(lambda),EventType::Arrival));
                //process current event
                Event returned = server.arrivalEvent(time,oldTime);
                
                //if we receive an event that is not Nothing then we need to add it to the GEL
                if(returned.getEventType() != EventType::Nothing)
                {
                    GEL.addEvent(returned);
                }
            }
            //departure event
            else 
            {
                double oldTime = time;
                time = event.getTime();
                Event returned = server.departureEvent(time,oldTime);
                
                //if we receive an event that is not Nothing then we need to add it to the GEL
                if(returned.getEventType() != EventType::Nothing)
                {
                    GEL.addEvent(returned);
                }
            }
        }
        cout<<"Server Statistics"<<endl;
        server.printStatistics(time);
    }
    else
    {
        cout<<"Usage is ./main lambda mu buffersize"<<endl;
    }
}
