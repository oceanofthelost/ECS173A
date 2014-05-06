#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include "Event.h"
#include "GlobalEventList.h"
#include "Server.h"
using namespace std;

/**
 * Determine the inter arrival time for a packet
 * @param  rate: rate parameter for the random variable
 * @param  Pareto: determines if we are going to use Pareto distribution 
 *                 or exponential distribution
 * @return: Value for the next inter arrival rate
 */
double inter_arrival(const double& rate,const bool& pareto) 
{
    if(pareto)
    {

        //uses the formula pareto = x_m/(U^(1/a));
        //where U is randomly distibuted over [o,1] and 
        //a = k/(k-x_m). K is the mean of pareto which is the 
        //interarrival rate of the negative exponential distrabution. 
        //x_m = 10% of k
        double u  = drand48();
        double xm = rate*.1;
        double a  = rate/(rate-xm);
        return xm/(pow(u,(double)1/a));
    }
    else
    {
        double u;
        u = drand48();
        return ((-1/rate)*log(1-u));
    }
}

/**
 * Runs the simulation
 * @param  argc:    argv[0] = executable, this is default
                    arcv[1] = lambda
                    argv[2] = mu
                    argv[3] = buffer-size
                    argv[4] = 0: exponential, 1: Pareto
 * @param  argv
 * @return
 */
int main(int argc, char* argv[])
{
    //if buffer size >= 0 then this is the buffer size limit
    //if buffer size < 0 then this means the buffer has infinite size

    if(argc == 6 and ((string)argv[4]=="Pareto" or (string)argv[4]=="Exponential"))
    {
        
        //initialize variables
        double  time    = 0.0;
        double  lambda  = atof(argv[1]);
        bool    pareto  = (string)argv[4]=="Pareto"?true:false;
        bool    file    = (string)argv[5]=="File"?true:false;
        //mu, maxBuffer
        Server server(atof(argv[2]),atoi(argv[3]));
        GlobalEventList GEL;
        
        //generate the fist event and put it in the GEL
        GEL.addEvent(Event(time+inter_arrival(lambda,pareto),EventType::Arrival)); 

        for(int i = 0; i<100000;i++)
        {
            Event event = GEL.nextEvent();
            
            //arrival event
            if(event.getEventType() == EventType::Arrival)
            {
                double oldTime = time;
                time = event.getTime();
                //schedule next arrival event and put it in the GEL
                GEL.addEvent(Event(time + inter_arrival(lambda,pareto),EventType::Arrival));
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
        server.printStatistics(time,lambda,file);
    }
    else
    {
        cout<<"Usage is ./main lambda mu buffer-size [Exponential,Pareto] File"<<endl;
    }
}
