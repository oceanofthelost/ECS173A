#include<cstdlib>
#include<iostream>
#include<cmath>
#include<queue>
using namespace std;

//used to distiguish between events types
enum class EventType {Arrival,Departure};

//describes an Event 
class Event
{
    private:
        //all events have a time and event type 
        //assoiated with them
        double      time;
        EventType   event_type;
    public:
        //we create an event by hiving it its time and 
        //telling it what type of event it will be
        Event(double t,EventType type)
        {
            time = t;
            event_type = type;
        }
        //used to compare 2 events. This is implemented the way it 
        //is so that i can use a priority queue. I want event sorted by 
        //smallest time to largest so that is why the operation insde operator<
        //is a >
        bool operator<(const Event& E) const
        {
            return time > E.time;
        }
        //we want to find out why type of event the 
        //event is
        EventType getEventType()
        {
            return event_type;
        }
        //we get the time the event occures at
        double getTime()
        {
            return time;
        }
};

//holds all of the events in increasing time 
class GlobalEventList
{
    private:
        //we require only inserting and removing elements form our sata 
        //structure. We also require that the elemenet that is removed is 
        //the event with the smallest time. Because of this i chose 
        //a priority queue of events keyed to time. By deffinition a priority
        //queue implements our requirments
        priority_queue<Event> GEL;
    public:
        //we make the GEL an empty priority queue
        GlobalEventList()
        {
           GEL = priority_queue<Event>(); 
        }
        //we add an event to the GEL
        void pushEvent(Event passed)
        {
            GEL.push(passed);
        }
        //we get the next event and we also remove 
        //the top element of the priority queue
        Event nextEvent()
        {
            Event returned = GEL.top();
            GEL.pop();
            return returned;
        }
};

//simple struct wrapper for a packet. using this so 
//if more attributes are added later it is a simple process
struct Packet
{
    double serviceTime;
};


double inter_arrival(double rate) //negative exponential distributed, rate = lambda
{
    double u;
    u = drand48();
    return ((-1/rate)*log(1-u));
}

double service_time(double rate) //negative exponential distributed, rate = mu
{
    double u;
    u = drand48();
    return ((-1/rate)*log(1-u));
}


int main()
{
    //initilaze variables
    unsigned    length  = 0;   //hold the current length of the queue
    double      time    = 0.0; //current time during the simulation
    double      lambda  = 1; //inter-arrival rate
    double      mu      = 1;   //transmission rate
    GlobalEventList GEL;       //Holds all of the events for the simulation

    double total_time = 0.0;


    //this needs to be wrapped in a class. Will make the code later on better
    queue<Packet> Buffer;      //buffer for the server
    
    //generate the fist event and put it in the GEL
    GEL.pushEvent(Event(time+inter_arrival(lambda),EventType::Arrival)); 
    
    for(int i = 0; i<100000;i++)
    {
        //get the next event from the GEL
        Event currentEvent = GEL.nextEvent();

        //if event is arrival process arrival event
        if(currentEvent.getEventType() == EventType::Arrival)
        {
            //take into account length also counts the packet that is currently 
            //being sent. I have not done this yes. 
            time=currentEvent.getTime();
            //we now schedule the next arrival event since we only set up one 
            //arrival event at a time. 
            GEL.pushEvent(Event(time+inter_arrival(lambda),EventType::Arrival));
            //we are processing an arrival so we generate the packet that we will 
            //be processing. we determin what the servoce time will be. 
            Packet newPacket;
            double serviceTime = service_time(mu);
            newPacket.serviceTime = serviceTime;
            
            //if the buffer is empty we immeditly start processing the packet
            if(Buffer.empty())
            {
                total_time+=newPacket.serviceTime;
                //generate a departure event and insert it into the GEL
                GEL.pushEvent(Event(time+newPacket.serviceTime,EventType::Departure));
            }
            //if the buffer is not empty we need to put the packet into the buffer
            else
            {
                //inserts the packet into the buffer
                Buffer.push(newPacket);
                //increase the length by 1
                length+=1;
            }
        }
        //else process departure event
        else
        {
            //set the current time for the simulation as the time the 
            //departure occured. 
            time=currentEvent.getTime();
            //decrease length by 1
            length-=1;
            //if buffer is not empty we will start transmitting the next packet. 
            if(!Buffer.empty())
            {
                //we pop the next packet from the queue
                
                //the following functions should be put into the buffer class
                //so that that it makes this look better
                Packet nextPacket = Buffer.front();
                Buffer.pop();
                total_time+=nextPacket.serviceTime;
                //we generate the next departure and put it into the GEL
                GEL.pushEvent(Event(time+nextPacket.serviceTime,EventType::Departure));
            }

        }
    }
    cout<<total_time<<"\t"<<time<<"\t"<<total_time/time<<endl;
}
