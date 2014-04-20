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
    unsigned    length  = 0;
    double      time    = 0.0;
    double      lambda  = 0.1; //inter-arrival rate
    double      mu      = 1;   //transmission rate
    GlobalEventList GEL;
    queue<Packet> Buffer;
    Event firstEvent(time+inter_arrival(lambda),EventType::Arrival); //generate the first arrival event
    
    for(int i = 0; i<100000;i++)
    {
        //get event from the GEL
        Event currentEvent = GEL.nextEvent();

        //if event is arrival process arrival event
        if(currentEvent.getEventType() == EventType::Arrival)
        {

            //take into account length also counts the packet that is currently 
            //being sent. I have not done this yes. 
            time=currentEvent.getTime();
            GEL.pushEvent(Event(time+inter_arrival(lambda),EventType::Arrival));
            Packet newPacket;
            newPacket.serviceTime = service_time(mu);
            
            if(Buffer.empty())
            {
                GEL.pushEvent(Event(time+newPacket.serviceTime,EventType::Departure));
            }
            else
            {
                Buffer.push(newPacket);
                length+=1;
            }
        }
        else
        {
            time=currentEvent.getTime();
            length-=1;

        }
        //else process departure event
    }

}
